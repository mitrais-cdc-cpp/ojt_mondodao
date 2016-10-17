/*
 * TestConnector.cpp
 *
 *  Created on: Jul 1, 2016
 *      Author: Ari Suarkadipa
 */

#include "TestConnector.h"
#include "../inc/DoaImpl/SpiderBite/Connector.h"

using namespace DB;

void TestConnector::testInsertWebsite()
{
	Connector connector(_host, _port, _dbName);
	Website website;
	string content = "<html><head>Hello</head><body>World</body></html>";

	website.content = content;
	website.protocolType = "http";
	website.url = "mitrais.com";
	connector.Insert(website);

	bool actual = true;
	bool result = connector.checkIsExist(content);
	CPPUNIT_ASSERT(result == actual);
}


void TestConnector::testUpdateWebsite()
{
	Connector connector(_host, _port, _dbName);
	string whereColumn = "content";
	string whereValue = "<html><head>Hello</head><body>World</body></html>";
	string newValue = "<html><head>Hello</head><body>New World</body></html>";

	connector.Update(whereColumn, whereValue, newValue);
	bool actual = true;
	bool result = connector.checkIsExist(newValue);
	CPPUNIT_ASSERT(result == actual);
}

void TestConnector::testShowAllWebsite()
{
	Connector connector(_host, _port, _dbName);
	string content = "<html><head>Hello</head><body>World</body></html>";

	connector.showAll();

	bool actual = true;
	bool result = connector.checkIsExist(content);
	CPPUNIT_ASSERT(result == actual);
}

void TestConnector::testDeleteWebsite()
{
	Connector connector(_host, _port, _dbName);
	string content = "http";

	DB::Common::Filter filter = connector.createFilter(2,1, content);

	vector<DB::Common::Filter> filters;
	filters.push_back(filter);

	connector.Delete(filters);

	bool actual = false;
	bool result = connector.checkIsExist(content);
	CPPUNIT_ASSERT(result == actual);
}
