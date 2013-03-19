/*
 * =====================================================================================
 *
 *       Filename:  PbFileHandler.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/13 13:37:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#ifndef __PBFILEHANDLER_H__
#define __PBFILEHANDLER_H__
#include "FileHandler.h"

class PbFileHandler: public FileHandler {
	public:
		PbFileHandler();
		virtual ~PbFileHandler();
		bool init(const Config &config);
		bool getItems(std::vector<Item *> &items);
	private:
		int m_fd;
		ssize_t m_fsize;
		void *start_addr;
};

#endif  /* --- __PBFILEHANDLER_H__--- */

