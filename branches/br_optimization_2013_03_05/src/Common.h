/*
 * =====================================================================================
 *
 *       Filename:  Common.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/12 15:54:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#ifndef __COMMON_H__
#define __COMMON_H__
#include <vector>
#include <string>

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

struct Item {
    Item() {
    }
    ~Item() {
        key.clear();
        val.clear();
    }
    std::string key;
    std::string val;
};

enum {
    E_OK  = 0,
    E_PUT = -1,
};

enum {
    SLEEP_INTERVAL = 50000,
    PRINT_THRESHOLD = 10000,
    ITEM_THRESHOLD =  10000,
    BUF_SIZE = BUFSIZ * 1024 + 10,
    READ_SIZE = 6 * 1024 * 1024,
    DATA_SIZE = 2 * 1024 * 1024 + 4,
    COMMON_SIZE = 1024 * 1024,
    LESS_SIZE = BUF_SIZE - DATA_SIZE, 
};


#endif  /* --- __COMMON_H__--- */

