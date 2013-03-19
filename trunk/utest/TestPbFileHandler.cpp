/*
 * =====================================================================================
 *
 *       Filename:  TestPbFileHandler.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/05/13 16:00:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include "PbFileHandler.h"
#include <gtest/gtest.h>
#include "TestCommon.h"

ANONYMOUS_NAMESPACE_BEGIN
class TestPbFileHandler: public ::testing::Test {
	protected:
		TestPbFileHandler() {
		}
		virtual ~TestPbFileHandler() {
		}
		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
	private:
};

TEST(TestPbFileHandler, init) {
    PbFileHandler *pHandler = new PbFileHandler();
    EXPECT_NE((PbFileHandler *)NULL, pHandler);
    EXPECT_EQ(-1, pHandler->m_fd);
    EXPECT_EQ(0, pHandler->m_fsize);
    EXPECT_EQ(NULL, pHandler->start_addr);
}
ANONYMOUS_NAMESPACE_END


