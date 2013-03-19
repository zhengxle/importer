/*
 * =====================================================================================
 *
 *       Filename:  Importer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/25/12 09:40:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include "Importer.h"
#include <unistd.h>
#include <pthread.h>
#include <tools/TairAgent.h>
#include <tools/Log.h>
#include <sys/types.h>

#include "PbFileHandler.h"
#include "NormalFileHandler.h"

using namespace std;
Importer::Importer(): m_file(NULL) {
}

Importer::~Importer() {
    delete m_file;
    pthread_mutex_destroy(&m_lock);
}

bool Importer::init(Config &config) {
    m_config = config;
    if (config.pbFileName != NULL) {
        m_file = new PbFileHandler();
    }
    else {
        m_file = new NormalFileHandler(); 
    }
    if (!m_file->init(config)) {
        return false;
    }
    
    int ret = -1;
    for (int i = 0; i < config.threadNum; i++) {
        TUnionTools::TairAgent *pTairAgent = new TUnionTools::TairAgent();
        for (int j = 0; j < 3; j++) {
            ret = pTairAgent->init(config.master, config.slave, config.group);
            if (ret == TUnionTools::E_OK) {
                m_pTairAgents.push_back(pTairAgent);
                break;
            }
            sleep(2);
        }

        if (ret != TUnionTools::E_OK) {
            LOGFMT_WARN("thread [%d] cannot init tair[%s, %s, %d]", i, config.master, config.slave, config.tairArea);
        }
    }

    if (m_pTairAgents.size() == 0) {
        LOGFMT_ERROR("cannot connect to tair[%s, %s, %d]", config.master, config.slave, config.tairArea);
        return false;
    }
    config.threadNum = (int) m_pTairAgents.size();
    pthread_mutex_init(&m_lock, NULL);
    return true;
}

int Importer::process(Config &config) {
    int threadNum = config.threadNum;
    pthread_t *pThreads = (pthread_t *)malloc(threadNum * sizeof(pthread_t));
    if (pThreads == NULL) {
        LOGFMT_ERROR("cannot init %d thread", threadNum);
        return -1;
    }

    int failed = 0;
    size_t success = 0;

    vector<ImporterWithNum *> importVec;
    for (int i = 0; i < threadNum; i++) {
        ImporterWithNum  *importerWithNum = new ImporterWithNum();
        importerWithNum->pImporter = this;
        importerWithNum->num = i;
        importVec.push_back(importerWithNum);
    }

    if (config.pbFileName != NULL) {
        for (int i = 0; i < threadNum; i++) {
            pthread_create(pThreads + i, NULL, Importer::importPb, (void *) (importVec[i]));
        }
    } else {
        for (int i = 0; i < threadNum; i++) {
            pthread_create(pThreads + i, NULL, Importer::importNormal, (void *) (importVec[i]));
        }
    }
    
    struct ImportResult *result = NULL;
    int ret = -1;
    for (int i = 0; i < threadNum; i++) {
        pthread_join(pThreads[i], (void **)&result);
        if (result->error == -1) {
            ret = -1;
        } else {
            failed += result->failedNum;
            success += result->successNum;
        }
        free(result);
        delete importVec[i];
    }

    LOGFMT_NOTICE("finish import, total success %zu items, failed %d items", success, failed);
    free(pThreads);
    return failed;

}

void* Importer::importPb(void *arg) {
    ImportResult *pResult = (ImportResult *)malloc(sizeof(ImportResult));
    memset(pResult, 0, sizeof(ImportResult));
    ImporterWithNum *importerWithNum = (ImporterWithNum *) arg;
    if (unlikely(!importerWithNum)) {
        LOGFMT_ERROR("import work thread arg error");
        pResult->error = -1;
        return (void *)pResult;
    }
    Importer *pImporter = importerWithNum->pImporter;
    int num = importerWithNum->num;
    TUnionTools::TairInterface *pTairAgent = pImporter->m_pTairAgents[num];
    int tairArea = pImporter->m_config.tairArea;
    int expire = pImporter->m_config.expireTime;
    int ret = -1;

    LOGFMT_NOTICE("thread [%d] start import work thread", num);

    for (vector <Item *> items; pImporter->getItems(items); items.clear()) {
        size_t s = items.size();
        LOGFMT_NOTICE("thread [%d] get [%zu] items", num, s);
        for (size_t i = 0; i < s; i++) {
            for (int j = 0; j < pImporter->m_config.repeatNum; j++) {
                ret = pTairAgent->put(tairArea, items[i]->key, items[i]->val, expire);
                if (likely(ret == TUnionTools::E_OK)) {
                    if (unlikely(++(pResult->successNum) % PRINT_THRESHOLD == 0)) {
                        LOGFMT_NOTICE("thread [%d] success import %d items", num, pResult->successNum);
                    }
                    if (pResult->successNum % pImporter->m_config.maxNumSleep == 0) {
                        usleep(1000);
                    }
                    break;
                }
            }

            if (unlikely(ret != E_OK)) {
                LOGFMT_ERROR("thread [%d] put[key=[%s], value=[%s]] to tair failed, errorMsg=[%s]",
                        num, items[i]->key.c_str(), items[i]->val.c_str(), pTairAgent->getErrorMsg(ret));
                pResult->failedNum++;
            }
            items[i]->key.clear();
            items[i]->val.clear();
            delete items[i];
        }
    }
    LOGFMT_NOTICE("thread[%d] end thread import, success %zu items, failed %d items",
            num, pResult->successNum, pResult->failedNum);
    return pResult;
}

bool Importer::getItems(vector<Item *> &items) {
    pthread_mutex_lock(&m_lock);
    bool result;
    bool ret = m_file->getItems(items);
    result = (ret == true && items.size() > 0); 
    pthread_mutex_unlock(&m_lock);
    return result;
}

void* Importer::importNormal(void *arg) {
    ImportResult *pResult = (ImportResult *)malloc(sizeof(ImportResult));
    memset(pResult, 0, sizeof(ImportResult));
    ImporterWithNum *importerWithNum = (ImporterWithNum *) arg;
    if (unlikely(!importerWithNum)) {
        LOGFMT_ERROR("import work thread arg error");
        pResult->error = -1;
        return (void *)pResult;
    }
    Importer *pImporter = importerWithNum->pImporter;
    int num = importerWithNum->num;
    TUnionTools::TairInterface *pTairAgent = pImporter->m_pTairAgents[num];
    int tairArea = pImporter->m_config.tairArea;
    int expire   = pImporter->m_config.expireTime;
    int kv_sep   = pImporter->m_config.kvSep;
    int item_sep = pImporter->m_config.itemSep;
    
    LOGFMT_NOTICE("thread [%d] start import work thread", num);
    char *key_pos, *val_pos, *cur_pos;
    char content[BUF_SIZE];
    for (; pImporter->getContent(content); memset(&content, 0, BUF_SIZE), key_pos = val_pos = NULL) {
        //LOGFMT_DEBUG("get content [%s]", content + strlen(content)-5);
        for (cur_pos = content; cur_pos; ) {
            key_pos = strchr(cur_pos, kv_sep);
            if (unlikely(key_pos == NULL)) {
                break; 
            }
            val_pos = strchr(key_pos, item_sep);
            
            string key(cur_pos, (size_t)(key_pos - cur_pos));
            ++key_pos;
            string value;
            if (val_pos == NULL) {
                value = string(key_pos);
                LOGFMT_DEBUG("key_pos=[%d], key=[%s], value=[%s]", (size_t)(key_pos - cur_pos), key.c_str(), value.c_str());
                cur_pos = NULL; 
            } else {
                value = string(key_pos, (size_t)(val_pos - key_pos));
                cur_pos = ++val_pos;
            }
            //LOGFMT_DEBUG("key_pos=[%d], val_pos=[%d], key=[%s], value=[%s]", (size_t)(key_pos - cur_pos), (size_t)(val_pos - cur_pos), key.c_str(), value.c_str());
            int ret    = -1;
            for (int i = 0; i < pImporter->m_config.repeatNum; i++) {
                ret = pTairAgent->put(tairArea, key, value, expire);
                if (ret == TUnionTools::E_OK) {
                    if (unlikely(++(pResult->successNum) % PRINT_THRESHOLD == 0)) {
                        LOGFMT_NOTICE("thread [%d] success import %d items", num, pResult->successNum);
                    }
                    if (pResult->successNum % pImporter->m_config.maxNumSleep == 0) {
                        usleep(1000);
                    }
                    break;
                }
            }
            if (unlikely(ret != E_OK)) {
                LOGFMT_ERROR("thread [%d] put[key=[%s], value=[%s]] to tair failed, errorMsg=[%s]",
                        num, key.c_str(), value.c_str(), pTairAgent->getErrorMsg(ret));
                pResult->failedNum++;
            }
            key.clear();
            value.clear();
        }
    }
    delete pTairAgent;
    LOGFMT_NOTICE("thread[%d] end thread import, success %zu items, failed %d items",
            num, pResult->successNum, pResult->failedNum);
    return pResult;
}

bool Importer::getContent(char *content) {
    pthread_mutex_lock(&m_lock);
    bool ret = m_file->getContent(content);
    pthread_mutex_unlock(&m_lock);
    return ret;
}
