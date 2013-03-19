/*
 * =====================================================================================
 *
 *       Filename:  NormalFileHandler.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/24/12 15:55:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#ifndef __NORMALFILEHANDLER_H__
#define __NORMALFILEHANDLER_H__
#include <vector>
#include "Common.h"
#include "FileHandler.h"

struct ExtraContent {
    char buf[DATA_SIZE];
    size_t pos;
};

class NormalFileHandler: public FileHandler {
    public:
        NormalFileHandler();
        virtual ~NormalFileHandler();
        bool init(const Config &config);
        bool getItems(std::vector<Item *> &items);
    private:
        int findPrefix(char *buf, ssize_t &pos);
        int findPost(char *buf, ssize_t &pos);
        int m_fd;
        char *contentBuf;
        ExtraContent extraContent; 
        ssize_t m_fsize;
        size_t m_readSize;
        int m_itemSep;
        int m_kvSep;
};

#endif  /* --- __NORMALFILEHANDLER_H__--- */

