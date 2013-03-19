/*
 * =====================================================================================
 *
 *       Filename:  FileHandler.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/13 12:58:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include "FileHandler.h"
FileHandler::FileHandler() {
}

FileHandler::~FileHandler() {
}

bool FileHandler::init(const Config &config) {
	return true;
}

bool FileHandler::getItems(std::vector <Item *> &items) {
	return true;
}

bool FileHandler::getContent(char *content) {
    return true;
}
