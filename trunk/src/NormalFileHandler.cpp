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
NormalFileHandler::NormalFileHandler(): m_fd(-1), contentBuf(NULL), m_fsize(0) {
    extraContent.pos = 0;
}

NormalFileHandler::~NormalFileHandler() {
    close(m_fd);
    free(contentBuf);
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
    contentBuf = (char *) malloc(m_readSize * sizeof (char));
    if (contentBuf == NULL) {
        LOGFMT_ERROR("cannot malloc space for [%d] chars", m_readSize);
        return false;
    }

    memset(contentBuf, 0, m_readSize);
    return true;
}

bool NormalFileHandler::getItems(std::vector<Item *> &items)
{
    static ssize_t file_pos = 0;
    for (items.clear(); items.size() < ITEM_THRESHOLD; ) {
        if (file_pos >= m_fsize) {
            LOGFMT_NOTICE("finish import file");
            return true;
        }
        ssize_t read_size = read(m_fd, contentBuf, m_readSize);
        ssize_t prefix_pos = 0;
        if (read_size < 0) {
            LOGFMT_ERROR("read from file error");
            return false;
        }
        file_pos += read_size;
        findPrefix(contentBuf, prefix_pos);
        memcpy(extraContent.buf + extraContent.pos, contentBuf, prefix_pos);
        extraContent.pos += prefix_pos;
        LOGFMT_DEBUG("extra_content=[%s], exptra_pos=[%d]", extraContent.buf, extraContent.pos);
        extraContent.buf[extraContent.pos] = '\0';
        string prefix(extraContent.buf, extraContent.pos);
        size_t sep_pos = prefix.find(m_kvSep);
        LOGFMT_DEBUG("prefix content[%s], pos = [%d]", prefix.c_str(), sep_pos);
        if (sep_pos == string::npos) {
            continue;
        }

        Item *pItem  = new Item();
        pItem->key   = prefix.substr(0, sep_pos);
        pItem->val = prefix.substr(sep_pos + KV_SEP_SIZE);
        LOGFMT_DEBUG("prefix, key=[%s], value=[%s]", pItem->key.c_str(), pItem->val.c_str());
        items.push_back(pItem);
        memset(extraContent.buf, 0, DATA_SIZE);
        extraContent.pos = 0;
        LOGFMT_DEBUG("prefix_pos=[%zu], read_size=[%d]", prefix_pos, read_size);

        ssize_t post_pos = read_size;
        findPost(contentBuf, post_pos);
        LOGFMT_DEBUG("readsize = [%d], post_pos = %zu", read_size, post_pos + 1);
        if (post_pos == (ssize_t) -1 ) {
            LOGFMT_ERROR("cannot find itemSep[%c] in content[%s]", m_itemSep, contentBuf);
            return false;
        }
        if (post_pos < read_size - 1) {
            memcpy(extraContent.buf, contentBuf + post_pos + 1, read_size - post_pos - 1);
            extraContent.pos = read_size - post_pos - 1;
            LOGFMT_DEBUG("postfix extra_content=[%s], extra_pos=[%d], strlen=[%d]", extraContent.buf,
                    extraContent.pos, strlen(extraContent.buf));
        }
        if (post_pos <= prefix_pos) {
            LOGFMT_ERROR("there not item sep character [%d] in content [%s]", m_itemSep, contentBuf);
            return false;
        }
        LOGFMT_DEBUG("post_pos=[%zu], prefix_pos=[%zu]", post_pos, prefix_pos);

        string content(contentBuf + prefix_pos + ITEM_SEP_SIZE, post_pos - prefix_pos - ITEM_SEP_SIZE);
        // LOGFMT_DEBUG("interal content=[%s]", content.c_str());
        memset(contentBuf, 0, m_readSize);
        size_t start_pos, pos;
        for (start_pos = 0, pos = content.find(m_itemSep, start_pos);
                pos != string::npos;
                start_pos = pos + 1, pos = content.find(m_itemSep, start_pos)) {
            string kvItem = content.substr(start_pos, pos - start_pos);
            sep_pos       = kvItem.find(m_kvSep);
            if (sep_pos == string::npos) {
                LOGFMT_ERROR("item content [%s] is not split by %c", kvItem.c_str(), m_kvSep);
                continue;
            }
            pItem = new Item();
            pItem->key = kvItem.substr(0, sep_pos);
            pItem->val = kvItem.substr(sep_pos + 1, pos - sep_pos);
            // LOGFMT_DEBUG("interal item-key[%s], item-value[%s]",
            //         pItem->key.c_str(), pItem->val.c_str());
            items.push_back(pItem);
        }
        //process the last one 
        size_t content_size = content.size();
        if (start_pos < content_size) {
            sep_pos = content.find(m_kvSep, start_pos);
            if (sep_pos != string::npos) {
                pItem = new Item();
                pItem->key = content.substr(start_pos, sep_pos - start_pos);
                pItem->val = content.substr(sep_pos + 1);
                //           LOGFMT_DEBUG("after \"for\" interal item-key[%s], item-value[%s]",
                //                   pItem->key.c_str(), pItem->val.c_str());
                items.push_back(pItem);
            }
        }
        content.clear();
    }
    return true;
}

int NormalFileHandler::findPrefix(char *buf, ssize_t &pos)
{
    ssize_t len = strlen(buf);
    for (; pos >= 0 && pos < len && buf[pos] != m_itemSep; pos++) {
    }
    return pos;
}

int NormalFileHandler::findPost(char *buf, ssize_t &pos)
{
    ssize_t len = strlen(buf);
    for (; pos >= 0 && pos <= len && buf[pos] != m_itemSep; pos--)
        ;
    return pos;
}
