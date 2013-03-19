/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/05/13 16:08:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */
#include "Person.pb.h"
#include <string>
#include <sys/fcntl.h>
using namespace std;

int toFile(int fd) {
    Person person[4];
    string val[4];
    int val_size[4];
    char buf[1024] = {0};
    int pos = 0;

    person[0].set_id(123);
    person[0].set_name("Bob");
    person[0].set_email("bob@example.com");
    person[0].SerializeToString( &val[0]);
    int key_size = 3;
    val_size[0]   = val[0].size();
    memcpy(buf + pos, &key_size, sizeof(key_size));
    pos += sizeof(key_size);
    memcpy(buf + pos, "123", strlen("123"));
    pos += strlen("123");
    memcpy(buf + pos, &val_size[0], sizeof(val_size[0]));
    pos += sizeof(val_size[0]);
    memcpy(buf + pos, val[0].c_str(), val_size[0]);
    pos += val_size[0];

    person[1].set_id(124);
    person[1].set_name("Tom");
    person[1].set_email("Tom@example.com");
    person[1].SerializeToString( &val[1]);
    
    val_size[1]   = val[1].size();
    memcpy(buf + pos, &key_size, sizeof(key_size));
    pos += sizeof(key_size);
    memcpy(buf + pos, "124", strlen("124"));
    pos += strlen("124");
    memcpy(buf + pos, &val_size[1], sizeof(val_size[1]));
    pos += sizeof(val_size[1]);
    memcpy(buf + pos, val[1].c_str(), val_size[1]);
    pos += val_size[1];

    person[2].set_id(125);
    person[2].set_name("Jim");
    person[2].set_email("Jim@example.com");
    person[2].SerializeToString( &val[2]);
    
    val_size[2]   = val[2].size();
    memcpy(buf + pos, &key_size, sizeof(key_size));
    pos += sizeof(key_size);
    memcpy(buf + pos, "125", strlen("125"));
    pos += strlen("125");
    memcpy(buf + pos, &val_size[2], sizeof(val_size[2]));
    pos += sizeof(val_size[2]);
    memcpy(buf + pos, val[2].c_str(), val_size[2]);
    pos += val_size[2];

    person[3].set_id(126);
    person[3].set_name("jake");
    person[3].set_email("Jake@example.com");
    person[3].SerializeToString( &val[3]);
    
    val_size[3]   = val[3].size();
    memcpy(buf + pos, &key_size, sizeof(key_size));
    pos += sizeof(key_size);
    memcpy(buf + pos, "126", strlen("126"));
    pos += strlen("126");
    memcpy(buf + pos, &val_size[3], sizeof(val_size[3]));
    pos += sizeof(val_size[3]);
    memcpy(buf + pos, val[3].c_str(), val_size[3]);
    pos += val_size[3];

    write(fd, buf, pos);
    return 0;
}

int main() {
    int fd = open("pbtest.input", O_CREAT | O_RDWR, 0666);
    toFile(fd);
    return 0;
}

