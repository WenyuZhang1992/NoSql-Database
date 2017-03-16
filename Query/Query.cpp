/////////////////////////////////////////////////////////////////////
// Query.cpp - Query Operations for database                       //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
/////////////////////////////////////////////////////////////////////


#include "Query.h"

using namespace NoSqlDatabase;

#ifdef TEST_QUERY

//////////////////////////////////////////////////////////////////////////
// testKeyPattern():
// - Provide test code for matching key pattern 
void testKeyPattern() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query1(db);
	std::cout << std::endl;
	makeTitle("Test query of matching specified pattern in key");
	query1.matchPattern();
	makeSubTitle("\n  Matching result with key pattern by default");
	std::cout << "\n  " << query1.showResult();
	std::string keyPattern = "key #";
	query1.matchPattern(keyPattern);
	makeSubTitle("\n  Matching result with key pattern = \"" + keyPattern + "\"");
	std::cout << "\n  " << query1.showResult() << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// testItem():
// - Provide test code for query item name
void testItem() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query1(db);
	std::cout << std::endl;
	// Test query entries containing specified string in item name
	std::cout << std::endl;
	std::string queryString = "be";
	makeTitle("Query for entries containing \"" + queryString + "\" in item name");
	query1.queryName(queryString);
	makeSubTitle("Query Result:");
	std::cout << "\n  " << query1.showResult() << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// testCate():
// - Provide test code for query category name
void testCate() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query1(db);
	std::cout << std::endl;
	// Test query entries containing specified string in category name
	std::cout << std::endl;
	std::string queryString = "rui";
	makeTitle("Query for entries containing \"" + queryString + "\" in category name");
	query1.queryCategory(queryString);
	makeSubTitle("Query result:");
	std::cout << "\n  " << query1.showResult() << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// testValue():
// - Provide test code for query string-type value
void testValue() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query1(db);
	std::cout << std::endl;
	// Test query entries containing specified string in value when valid
	std::cout << std::endl;
	std::string queryString = "11";
	makeTitle("Query for entries containing \"" + queryString + "\" in value");
	query1.queryValue(queryString);
	makeSubTitle("Query result:");
	std::cout << "\n  " << query1.showResult() << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// testTime():
// - Provide test code for query time interval
void testTime() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query1(db);
	std::cout << std::endl;
	// Test query entries added between time interval
	makeTitle("Query for entries added between time interval");
	std::string start = "22:33:36 2017/02/04";
	std::string end = "22:33:50 2017/02/04";
	query1.queryTime(start, end);
	makeSubTitle("Query result:");
	std::cout << "\n  " << query1.showResult() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testKeyPatternRE():
// - Provide test code for matching key pattern using regular expression  
void testKeyPatternRE() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query(db);
	makeTitle("Test keys begin with \"elem\"");
	std::regex keyPattern = std::regex("elem.*");
	query.matchPatternRE(keyPattern);
	std::cout << query.showResult() << std::endl;

	makeTitle("Test keys contain \"#6\"");
	Query<std::string> query1(db);
	std::regex keyPattern1 = std::regex(".*#6.*");
	query1.matchPatternRE(keyPattern1);
	std::cout << query1.showResult() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testItemRE():
// - Provide test code for query item name using regular expression 
void testItemRE() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query(db);
	makeTitle("Test Item name begin with \"Or\"");
	std::regex queryString = std::regex("Or.*");
	query.queryNameRE(queryString);
	std::cout << query.showResult() << std::endl;

	makeTitle("Test Item name ends with \"ge\"");
	Query<std::string> query1(db);
	std::regex queryString1 = std::regex(".*ge$");
	query1.queryNameRE(queryString1);
	std::cout << query1.showResult() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testCateRE():
// - Provide test code for query category name using regular expression 
void testCateRE() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query(db);
	makeTitle("Test Category name begin with M or A");
	std::regex queryString = std::regex("[A,M].*");
	query.queryCategoryRE(queryString);
	std::cout << query.showResult() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testValueRE():
// - Provide test code for query category name using regular expression 
void testValueRE() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query(db);
	makeTitle("Test Value contains ml or lb");
	std::regex queryString = std::regex(".*[ML,lb].*");
	query.queryValueRE(queryString);
	std::cout << query.showResult() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testKeyRE():
// - Provide test code for query value using regular expression 
void testKeyRE() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query(db);
	makeTitle("Query values of Key begin with elem");
	std::regex queryString = std::regex("elem.*");
	std::vector<EntryValue<std::string>> value_set = query[queryString];
	for (auto entry : value_set) {
		std::cout << entry.showEntryValue()<<std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////
// testChildrenRE():
// - Provide test code for query children using regular expression 
void testChildrenRE() {
	NoSqlDB<std::string> db;
	std::string in = "../XmlFiles/StrDB.xml";
	db.restore(in);
	Query<std::string> query(db);
	makeTitle("Query values of Key begin with elem");
	std::regex queryString = std::regex("elem.*");
	std::vector<std::unordered_set<std::string>> value_set = query.queryChildrenRE(queryString);
	for (auto entry : value_set) {
		std::cout << show(entry) << std::endl;
	}
}

int main() {
	testKeyPattern();
	testItem();
	testValue();
	testKeyRE();
	testKeyPatternRE();
	testItemRE();
	testCateRE();
	testValueRE();
	testKeyRE();
	testChildrenRE();
}

#endif // !TEST_QUERY
