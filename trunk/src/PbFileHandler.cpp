/*
 * =====================================================================================
 *
 *       Filename:  PbFileHandler.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/13 13:41:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include "PbFileHandler.h"
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <tools/Log.h>

using namespace std;

PbFileHandler::PbFileHandler(): m_fd(-1), m_fsize(0), start_addr(NULL) {

}
PbFileHandler::~PbFileHandler() {
    munmap(start_addr, m_fsize);
    close(m_fd);
}

bool PbFileHandler::init(const Config &config) {
    Config &cfg = const_cast<Config &> (config);
    if ((m_fd = open(cfg.pbFileName, O_RDONLY)) < 0) {
        LOGFMT_ERROR("open pb file %s failed", cfg.pbFileName);
        return false;
    }
    struct stat statbuf;
    if (fstat(m_fd, &statbuf) < 0) {
        LOGFMT_ERROR("fstat pb file %s failed", cfg.pbFileName);
        return false;
    }
    m_fsize     = statbuf.st_size;
    start_addr = mmap(NULL, m_fsize, PROT_READ, MAP_PRIVATE, m_fd, 0);
    if (start_addr == MAP_FAILED) {
        LOGFMT_ERROR("cannot mmap %s to process space", cfg.pbFileName);
        return false;
    }
    return true; 
}

bool PbFileHandler::getItems(std::vector<Item *> &items) {
    static ssize_t file_pos = 0;
    int len = 0;
    char *buf   = NULL;
    char *start = (char *)start_addr;
    for (items.clear(); items.size() < ITEM_THRESHOLD; ) {
        if (file_pos >= m_fsize) {
            LOGFMT_NOTICE("finish import file");
            return true;
        }
        memcpy(&len, start + file_pos, sizeof(len));
        if (len <= 0 || len > 1024 * 1024) {
            LOGFMT_ERROR("the %zuth items-key's size [%d] is not in (0, 1M]", items.size(), len);
            return false;
        }
        file_pos += sizeof(len);
        LOGFMT_DEBUG("parse size=[%d] for %zuth's items key", len, items.size());
        buf = (char *)malloc(len * sizeof(char));
        if (buf == NULL) {
            LOG_ERROR("cannot malloc buffer space to parse items key");
            return false;
        }
        memcpy(buf, start + file_pos, len);
        Item *pItem = new Item();
        pItem->key = string(buf, len);
        free(buf);
        buf = NULL;
        file_pos += len; 
        memcpy(&len, start + file_pos, sizeof(len));
        if (len < 0 || len > 1024 * 1024) {
            LOGFMT_ERROR("the %zuth items-value's size [%d] is not in [0, 1M]", items.size(), len);
            return false;
        }
        file_pos += sizeof(len);
        if (len == 0) {
            pItem->val = "";
            items.push_back(pItem);
            continue;
        }
        buf = (char *)malloc(len * sizeof(char));
        if (buf == NULL) {
            LOG_ERROR("cannot malloc buffer space to parse items value");
            return false;
        }
        memcpy(buf, start + file_pos, len);
        pItem->val = string(buf, len);
        file_pos += len;
        items.push_back(pItem);
        delete buf;
        buf = NULL;
        len = 0;
    }
    return true;
}
