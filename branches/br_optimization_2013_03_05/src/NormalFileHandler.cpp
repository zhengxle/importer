/*
 * =====================================================================================
 *
 *       Filename:  NormalFileHandler.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/12 16:29:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include "NormalFileHandler.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <tools/Log.h>

using namespace std;

#define ITEM_SEP_SIZE 1
#define KV_SEP_SIZE 1

NormalFileHandler::NormalFileHandler(): m_fd(-1), m_fsize(0) {
    extraContent.pos = 0;
}

NormalFileHandler::~NormalFileHandler() {
    close(m_fd);
}

bool NormalFileHandler::init(const Config &config)
{
    Config &cfg = const_cast<Config &>(config);
    m_fd = open(cfg.fileName, O_RDONLY);
    if (m_fd == -1) {
        LOGFMT_ERROR("cannot open file [%s]", cfg.fileName);
        return false;
    }
    struct stat buf;
    if (fstat(m_fd, &buf) < 0) {
        LOGFMT_ERROR("cannot get file [%s] state", cfg.fileName);
        return false;
    }
    m_fsize = buf.st_size;
    m_itemSep = cfg.itemSep;
    m_kvSep   = cfg.kvSep;
    m_readSize = cfg.readSize;
    if (m_readSize == 0) {
        m_readSize = BUF_SIZE;
    }

    memset(&extraContent, 0, sizeof (extraContent));
    return true;
}

bool NormalFileHandler::getContent(char *content)
{
    static ssize_t file_pos = 0;
    if (unlikely(file_pos >= m_fsize)) {
            LOGFMT_NOTICE("finish import file");
            return false;
    }

    size_t read_size = 0, length;
    char *pos = 0;
    if (extraContent.pos != 0) {
        memcpy(content, extraContent.buf, extraContent.pos);
    }

    read_size = read(m_fd, content + extraContent.pos, READ_SIZE);

    if (read_size < 0) {
            LOGFMT_ERROR("read from file error");
            return false;
        }
    
    file_pos += read_size;
    if (unlikely(read_size == 0)) {
        LOGFMT_ERROR("read from file zero");
        content[extraContent.pos] = '\0';
        return true;
    }

    pos = strrchr(content, m_itemSep);
    if (unlikely(pos == NULL)) {
        LOGFMT_ERROR("content [%s] format is error, there is not %d in content", content, m_itemSep);
        return false;
    }
    length = (size_t)(content + extraContent.pos + read_size - pos);
    *pos = '\0';
    if (unlikely(pos == &content[extraContent.pos + read_size - 1])) {
        memset(&extraContent, 0, sizeof(extraContent));
        return true;
    }
    extraContent.pos = length - 1;
    LOGFMT_DEBUG("content=[%s], length=[%d], expos=[%d]", pos+1, length, extraContent.pos);
    memcpy(extraContent.buf, pos+1, extraContent.pos);
    LOGFMT_DEBUG("extraContent [%s], pos=[%d]", extraContent.buf, extraContent.pos);
    return true;
}
