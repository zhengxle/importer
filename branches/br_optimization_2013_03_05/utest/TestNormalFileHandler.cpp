/*
 * =====================================================================================
 *
 *       Filename:  TestNormalFileHandler.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/05/13 09:14:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */
#include "NormalFileHandler.h"
#include <gtest/gtest.h>
#include "TestCommon.h"

ANONYMOUS_NAMESPACE_BEGIN

class TestNormalFileHandler: public ::testing::Test {
	protected:
		TestNormalFileHandler() {
		}
		virtual ~TestNormalFileHandler() {
		}
		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
	private:
};

TEST(TestNormalFileHandler, init) {
	NormalFileHandler *pHandler = new NormalFileHandler();
	EXPECT_NE((NormalFileHandler *)NULL, pHandler);
	EXPECT_EQ(-1, pHandler->m_fd);
	EXPECT_EQ(0, pHandler->m_fsize);
	Config config;
	config.fileName = "test.input2";
	pHandler->init(config);
	EXPECT_NE(-1, pHandler->m_fd);
	EXPECT_NE(0, pHandler->m_fsize);
	EXPECT_EQ(10, pHandler->m_itemSep);
	EXPECT_EQ(4, pHandler->m_kvSep);
    delete pHandler;

}
#if 0
TEST(TestNormalFileHandler, getItems) {
    NormalFileHandler *pHandler = new NormalFileHandler();
    Config config;
    config.fileName = "test.input2";
    pHandler->init(config);
    std::vector<Item *> items;
    bool ret = pHandler->getItems(items);
    EXPECT_EQ(true, ret);
    EXPECT_NE((size_t)0, items.size());
    close(pHandler->m_fd);
    delete pHandler;
}
#endif
ANONYMOUS_NAMESPACE_END
