/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年08月04日 20时32分48秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  柯杰(金喜) (kejie), jinxi.kj@taobao.com
 *        Company:  taobao.com
 *
 * =====================================================================================
 */

#include "TestCommon.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <tbsys.h>  // include tbsys.h to setLogLevel for tair

#include <tools/Log.h>

int main(int argc, char **argv)
{
    TBSYS_LOGGER.setLogLevel("ERROR");
    LOG_INIT("log4cpp_unittest.conf");

    //testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

