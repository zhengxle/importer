/*
 * =====================================================================================
 *
 *       Filename:  sys_nerr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/08/2011 11:49:08 PM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ke Jie (kejie), jinxi.kj@taobao.com
 *        Company:  taobao.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <errno.h>

int main() {
    printf("%d\n", sys_nerr);
    return 0;
}
