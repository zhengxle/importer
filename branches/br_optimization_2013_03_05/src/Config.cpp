/*
 * =====================================================================================
 *
 *       Filename:  Config.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/25/12 09:30:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include "Config.h"
#define DEFAULT_LOG_CONF "./log4cpp.conf"
Config::Config():
    version(0),
    fileName(NULL),
    pbFileName(NULL),
    readSize(BUF_SIZE),
    tairArea(0),
    master(NULL),
    slave(NULL),
    group(NULL),
    configFile(NULL),
    repeatNum(3),
    expireTime(time(NULL)),
    threadNum(1),
    maxNumSleep(1000000),
    itemSep(10),
    kvSep('\004') {

}

Config::~Config() {

}

bool Config::load(const char *file) {
    if (!m_parser.load(file)) {
        printf("cannot load %s config file\n", file);
        return false;
    }
    logFile = m_parser.getString("main", "log_conf", DEFAULT_LOG_CONF);
    readSize = m_parser.getInt("main", "normal_file_read_size", BUF_SIZE);
    return true;
}
