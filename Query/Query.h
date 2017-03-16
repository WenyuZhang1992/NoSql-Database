#ifndef QUERY_H
#define QUERY_H
/////////////////////////////////////////////////////////////////////
// Query.h - Query Operations for database                         //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
/////////////////////////////////////////////////////////////////////
/*
*  Class Operations
* ===================
*  - Query: provide query operations for NoSqlDB instance;
*  - Support indexing operator to query specified value or children
*  - Provide union of queries of same database; 
*  - Provide query on previous query results;
*
*  Public Interface
* ==================
*  Query<std::string> query1(NoSqlDB<std::string> db)       construct a string-type query instance
*  Query<std::string> query2(query2)                        copy constructor for query instance
*  Query<std::string> query3 = query1                       construct query3 as copy of query1
*  query1[key]                                              query value of specified key
*  query1[key][child]                                       query children of specified key
*  query1.matchPattern(std::string)                         query keys contain specifed key pattern
*  query1.queryName(std::string)                            query keys contain string in item name
*  query1.queryCategory(std::string)                        query keys contain string in category name
*  query1.queryvalue(std::string)                           query keys contain string in string-type value
*  query1.queryTime(std::string, std::string)               query keys written in certain time interval
*  query1.unionQuery(query2)                                make union of query results
*  query1[std::regex]                                       query for value of specified keys using regular expression
*  query1.queryChildrenRE(std::regex)                       query for children of specified keys using regular expresion
*  query1.matchKeyPatternRE(std::regex)                     query key pattern using regular expression
*  query1.queryNameRE(std::regex)                           query item name using regular expression
*  query1.queryCategoryRE(std::regex)                       query category name using regular expression
*  query1.queryValueRE(std::regex)                          query string-type value using regular expression
*
/////////////////////////////////////////////////////////////////////
// Build Process                                                   //
/////////////////////////////////////////////////////////////////////
//  Required Files:                                                //
//  - Query.h, NoSqlDB.h, DBEntry.h, DBUtilities.h, Query.cpp      //
//                                                                 //
//  Build Process:                                                 //
//    Set preprocessor definition TEST_QUERY in properties.        //
//    Set HashTable as the startup project.                        //
//    Compile and run in Visual Studio.                            //
//                                                                 //
/////////////////////////////////////////////////////////////////////
*
*  Build Command
* ===============
*    devenv Query.sln /rebuild debug
*
*  Maintenance History
* =====================
*  ver 1.0 : 07 Feb 17
*  - first release
* 
*/
#include <iostream>
#include <unordered_set>
#include <string>
#include <regex>

#include "..\DBUtilities\DBUtilities.h"
#include "..\DBEntry\DBEntry.h"
#include "..\NoSqlDatabase\NoSqlDatabase.h"

namespace NoSqlDatabase {

	///////////////////////////////////////////////////////////////////////////
	// Query:
	// - Provide string query operations needed by NoSqlDB
	// - Provide union of queries of same database 
	// - Provide query on previous query results
	template<class _Value>
	class Query 
	{

	public:

		using Key = std::string;
		using Keys = std::unordered_set<Key>;
		using Database = NoSqlDB<_Value>;
		using Elements = std::vector<EntryValue<_Value>>;
		using Children = std::vector<Keys>;

		Query(Database& db);                                  // promotion constructor
		Query(const Query& query);                            // copy constructor
		Query& operator=(const Query& query);                 // copy assignment operator
		EntryValue<_Value> operator[](const Key& key);        // indexing operator
		EntryValue<_Value> operator[](const Key& key) const;  // indexing operator for const instance
		Elements operator[](const std::regex key);            // indexing operator for regular expression

		// public interfaces
		void matchPattern(const std::string& keyPattern="");     // query for key set that match specified pattern
		void queryName(const std::string& queryString);          // query for key set that contains queryString in their item name
		void queryCategory(const std::string& queryString);      // query for key set that contain queryString in their category name
		void queryValue(const std::string& queryString);         // query for key set that contain queryString in value when valid 
		void queryTime(const std::string& start,                 // query for key set that added between the time interval
			const std::string& end = "");
		void unionQuery(const Query query);                      // union operation for previous queries

		void matchPatternRE(const std::regex keyPattern);        // query for key set that match specified pattern
		void queryNameRE(const std::regex query);                // query for item name using regular expression
		void queryCategoryRE(const std::regex query);            // query forcategory name using regular expression
		void queryValueRE(const std::regex query);               // query for string-type value using regular expression
		Children queryChildrenRE(const std::regex query);        // query for children using regular expression
		std::string showResult();                                // display contents of queryResult_

	private:

		// private member for query instances
		Database& database_;
		Keys queryResult_;

		// private helper functions
		Keys getter();                                           // getter function for member variable result_
		Keys getter() const;                                     // getter function for constant instance
		void setter(const Keys& newResult);                      // setter function for member variable result_
	};

	//----< promotion constructor for Query class >--------------------------------------

	template<class _Value>
	Query<_Value>::Query(Database& db)
		:database_(db)
	{
		setter(db.keySet());
	}

	//----< copy constructor for Query class >-------------------------------------------

	template<class _Value>
	Query<_Value>::Query(const Query& query)
		:database_(query.database_),
		 queryResult_(query.queryResult_)
	{}

	//----< assignment operator for Query class >----------------------------------------

	template<class _Value>
	Query<_Value>& Query<_Value>::operator=(const Query<_Value>& query) {
		if (this != &query) {
			this->database_ = query.database_;
			this->queryResult_ = query.queryResult_;
		}
		return *this;
	}

	//----< indexing operator for Query class >------------------------------------------

	template<class _Value>
	EntryValue<_Value> Query<_Value>::operator[](const Key& key) {
		EntryValue<_Value> temp;
		if (database_.containKey(key))
			temp = database_[key];
		return temp;
	}

	//----< indexing operator for const instance >---------------------------------------

	template<class _Value>
	EntryValue<_Value> Query<_Value>::operator[](const Key& key) const {
		EntryValue<_Value> temp;
		if (database_.containKey(key))
			temp = database_[key];
		return temp;
	}

	//----< indexing operator using regular expression >---------------------------------

	template<class _Value>
	typename Query<_Value>::Elements Query<_Value>::operator[](const std::regex key) {
		// match the key using query for key pattern
		matchPatternRE(key);
		Elements elemSet({});
		for (Key key : queryResult_) {
			elemSet.push_back(database_[key]);
		}
		return elemSet;
	}

	//----< getter function for queryResult_ >-------------------------------------------

	template<class _Value>
	typename Query<_Value>::Keys Query<_Value>::getter() { return queryResult_; }

	//----< getter function for constant instance >--------------------------------------

	template<class _Value>
	typename Query<_Value>::Keys Query<_Value>::getter() const { return queryResult_; }

	//----< setter function for queryResult_ >------------------------------------------

	template<class _Value>
	void Query<_Value>::setter(const Keys& newResult) { queryResult_ = newResult; }

	//----< display contents of queryResult_ >-------------------------------------------

	template<class _Value>
	std::string Query<_Value>::showResult() { return show(queryResult_); }

	//----< query key pattern >----------------------------------------------------------

	template<class _Value>
	void Query<_Value>::matchPattern(const std::string& keyPattern) {
		// By default, resturn whole key set
		if (keyPattern.size() == 0) {
			queryResult_ = database_.keySet();
			return;
		}
		// return the key set beginning with keyPattern string
		Keys keys;
		for (Key key : queryResult_) {
			/*
			if (key.compare(0, keyPattern.size(), keyPattern) == 0) {
				keys.insert(key);
			}*/
			if (key.find(keyPattern) != std::string::npos)
				keys.insert(key);
		}
		queryResult_ = keys;
	}

	//----< query key pattern using regular expression>----------------------------------

	template<class _Value>
	void Query<_Value>::matchPatternRE(const std::regex keyPattern) {
		Keys keys;
		for (Key key : queryResult_) {
			if (std::regex_match(key, keyPattern))
				keys.insert(key);
		}
		queryResult_ = keys;
	}

	//----< return keys containing specified string in item name >-----------------------

	template<class _Value>
	void Query<_Value>::queryName(const std::string& queryString) {
		Keys keys;
		for (Key key : queryResult_) {
			std::string nameStr = database_[key].name.getValue();
			if (nameStr.find(queryString) != std::string::npos)
				keys.insert(key);
		}
		queryResult_ = keys;
	}

	//----< query item name using regular expression>------------------------------------

	template<class _Value>
	void Query<_Value>::queryNameRE(const std::regex query) {
		Keys keys;
		for (Key key : queryResult_) {
			std::string nameStr = database_[key].name.getValue();
			if (std::regex_match(nameStr, query))
				keys.insert(key);
		}
		queryResult_ = keys;
	}

	//----< return keys containing specified string in category name >-------------------

	template<class _Value>
	void Query<_Value>::queryCategory(const std::string& queryString) {
		Keys keys;
		for (Key key : queryResult_) {
			std::string cateStr = database_[key].categoryName.getValue();
			if (cateStr.find(queryString) != std::string::npos)
				keys.insert(key);
		}
		queryResult_ = keys;
	}

	//----< query category name using regular expression >-------------------------------

	template<class _Value>
	void Query<_Value>::queryCategoryRE(const std::regex query) {
		Keys keys;
		for (Key key : queryResult_) {
			std::string cateStr = database_[key].categoryName.getValue();
			if (std::regex_match(cateStr, query))
				keys.insert(key);
		}
		queryResult_ = keys;
	}

	//----< return keys containing specified string in value when valid >----------------

	template<>
	void Query<std::string>::queryValue(const std::string& queryString) {
		Keys keys;
		for (Key key : queryResult_) {
			std::string valueStr = database_[key].value.getValue();
			if (valueStr.find(queryString) != std::string::npos)
				keys.insert(key);
		}
		setter(keys);
	}

	//----< query string-type value using regular expression >---------------------------

	template<>
	void Query<std::string>::queryValueRE(const std::regex query) {
		Keys keys;
		for (Key key : queryResult_) {
			std::string valueStr = database_[key].value.getValue();
			if (std::regex_match(valueStr, query))
				keys.insert(key);
		}
		setter(keys);
	}

	//----< return keys containing specified string in value when valid >----------------

	template<class _Value>
	void Query<_Value>::queryTime(const std::string& start, const std::string& end) {
		// transform start time
		time_t startTime = strToTime(start);
		// transform end time
		time_t endTime;
		// if no specified end time, set as current time
		if (end.size() == 0) { 
			endTime = strToTime(getTime()); 
		}
		else { 
			endTime = strToTime(end); 
		}

		Keys keys;
		for (Key key : queryResult_) {
			std::string timeStr = database_[key].timeDate.getValue();
			time_t addTime = strToTime(timeStr);
			if (difftime(addTime, startTime)>=0 && difftime(endTime, addTime)>=0)
				keys.insert(key);
		}
		setter(keys);
	}

	//----< union operation of previous queries >----------------------------------------

	template<class _Value>
	void Query<_Value>::unionQuery(const Query<_Value> query) {
		Keys keys = query.getter();
		this->queryResult_.insert(keys.begin(), keys.end());
	}

	//----< union operation of previous queries >----------------------------------------

	template<class _Value>
	typename Query<_Value>::Children Query<_Value>::queryChildrenRE(const std::regex query) {
		// match the key using query for key pattern
		matchPatternRE(query);
		Children children({});
		for (Key key : queryResult_) {
			children.push_back(database_[key][child]);
		}
		return children;
	}
}

#endif // !QUERY_H

