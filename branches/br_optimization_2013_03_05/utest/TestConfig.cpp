/*
 * =====================================================================================
 *
 *       Filename:  TestConfig.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/05/13 15:41:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include "Config.h"
#include <gtest/gtest.h>
#include "TestCommon.h"

ANONYMOUS_NAMESPACE_BEGIN

class TestConfig: public ::testing::Test {
	protected:
		TestConfig() {
		}
		virtual ~TestConfig() {
		}

		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
	private:
};

TEST(TestConfig, load) {
	Config config;
	char *name = "importer.conf";
	EXPECT_EQ(true, config.load(name));
}
ANONYMOUS_NAMESPACE_END
