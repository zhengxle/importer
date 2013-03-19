/*
 * =====================================================================================
 *
 *       Filename:  Config.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/12 15:08:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */


#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <string>
#include <common/file/IniConfig.h>
#include "Common.h"
struct Config {
    Config();
    ~Config();
    bool load(const char *file);
    int version;
    char *fileName;
    char *pbFileName;
    size_t readSize;
    int tairArea;
    char *master;
    char *slave;
    char *group;
    char *configFile;
    std::string logFile;
    int repeatNum;
    time_t expireTime;
    int threadNum;
    int errorTheshold;
    int maxNumSleep;
    int itemSep;
    int kvSep;
    TUnionCommon::File::IniConfig m_parser;
};

#endif  /* --- __CONFIG_H__--- */

