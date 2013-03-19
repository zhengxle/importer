/*
 * =====================================================================================
 *
 *       Filename:  TestImporter.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/05/13 14:22:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */
#include "Importer.h"
#include <gtest/gtest.h>
#include <tools/stub/TairAgentStub.h>
#include "TestCommon.h"
#include "NormalFileHandler.h"
#include "PbFileHandler.h"
#include "./tools/Person.pb.h"
ANONYMOUS_NAMESPACE_BEGIN

class TestImporter: public ::testing::Test {
	protected:
		TestImporter() {
		}
		virtual ~TestImporter() {
		}

		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
	private:
};

#if 1 

TEST(TestImporter, init) {
	Importer *pImporter = new Importer();
	EXPECT_NE((Importer *)NULL, pImporter);
	EXPECT_EQ(NULL, pImporter->m_file);
	EXPECT_EQ(0, pImporter->m_pTairAgents.size());
    delete pImporter;
}

TEST(TestImporter, process) {
    Importer *pImporter = new Importer();
    TUnionTools::TairInterface *pTairAgent = new TUnionTools::TairAgentStub(); 
    pImporter->m_pTairAgents.push_back(pTairAgent);
    pImporter->m_file       = new NormalFileHandler();
    Config config;
    config.fileName = "test.input";
    pImporter->m_file->init(config);
    int ret = pImporter->process(config);
    EXPECT_EQ(0, ret);
    //std::string expectVal = "te1stValaaa";
    //std::string val;
    //pTairAgent->get(0, "asa1da123987", val);
    //EXPECT_EQ(expectVal, val);
    delete pImporter;
}

TEST(TestImporter, processPb) {
    Importer *pImporter = new Importer();
    TUnionTools::TairInterface *pTairAgent = new TUnionTools::TairAgentStub();
    pImporter->m_pTairAgents.push_back(pTairAgent);
    pImporter->m_file       = new PbFileHandler();
    Config config;
    config.pbFileName = "pbtest.input";
    pImporter->m_file->init(config);
    int ret = pImporter->process(config);
    EXPECT_EQ(0, ret);
    //std::string val;
    //pTairAgent->get(0, "123", val);
    //EXPECT_NE("", val);
    //Person person;
    //person.ParseFromString(val);
    //EXPECT_EQ("Bob", person.name());
    delete pImporter;
}

#endif
ANONYMOUS_NAMESPACE_END
