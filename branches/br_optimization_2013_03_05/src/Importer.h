/*
 * =====================================================================================
 *
 *       Filename:  Importer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/12 15:43:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include <pthread.h>
#include <tools/TairInterface.h>

#include "FileHandler.h"
#include "Config.h"
#include "Common.h"
class Importer;
struct ImportResult {
    int error;
    int successNum; 
    int failedNum;
};

struct ImporterWithNum {
    Importer *pImporter;
    int num;
};

struct Kv_t {
    char key[COMMON_SIZE];
    char value[COMMON_SIZE];
};

class Importer {
    public:
        Importer();
        ~Importer();
        bool init(Config &config);
        int process(Config &config);
    private:
        int processPb(Config &config);
        int processNormal(Config &config);
        static void* importPb(void *arg);
        static void* importNormal(void *arg);
        bool getContent(char *content);
        bool getItems(std::vector<Item *> &items);
    private:
        pthread_mutex_t m_lock;
        FileHandler *m_file;
        std::vector<TUnionTools::TairInterface * > m_pTairAgents;
        Config m_config;
};
#endif  /* --- __IMPORTER_H__--- */

