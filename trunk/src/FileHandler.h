/*
 * =====================================================================================
 *
 *       Filename:  FileHandler.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/13 12:57:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#ifndef __FILEHANDLER_H__
#define __FILEHANDLER_H__

#include <vector>
#include "Common.h"
#include "Config.h"
class FileHandler {
	public:
		FileHandler();
		virtual ~FileHandler();
		virtual bool init(const Config &config);
        virtual bool getItems(std::vector<Item *> &items);
};

#endif  /* --- __FILEHANDLER_H__--- */

