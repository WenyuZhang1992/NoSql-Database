/////////////////////////////////////////////////////////////////////
// TestExecutive.cpp - Test code for project #1                    //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

#include "TestExecutive.h"
#include "..\NoSqlDatabase\NoSqlDatabase.h"
#include "..\Query\Query.h"
#include "..\Persist\Persist.h"

#ifdef TEST_EXECUTIVE

using namespace NoSqlDatabase;
using Str = std::string;
using ChildCollection = std::unordered_set<std::string>;
using Key = std::string;
using Keys = std::unordered_set<Key>;
using Vector = std::vector<int>;
using sPtr = std::shared_ptr<XmlProcessing::AbstractXmlElement>;

///////////////////////////////////////////////////////////////////////////
// Test Functions

///////////////////////////////////////////////////////////////////////////
// buildIntElem():
// - create integer-type element instance
EntryValue<int> buildIntElem(const Str& name, const Str& cate, const Str& des, const NoSqlDatabase::ChildCollection children, int value) {
	EntryValue<int> entry;
	entry.name = name;
	entry.categoryName = cate;
	entry.txtDescription = des;
	entry.childCollection = children;
	entry.value = value;
	return entry;
}

///////////////////////////////////////////////////////////////////////////
// buildStrElem():
// - create string-type element instance
EntryValue<std::string> buildStrElem(const Str& name, const Str& cate, const Str& des, const NoSqlDatabase::ChildCollection children, const Str& value) {
	EntryValue<std::string> entry;
	entry.name = name;
	entry.categoryName = cate;
	entry.txtDescription = des;
	entry.childCollection = children;
	entry.value = value;
	return entry;
}

///////////////////////////////////////////////////////////////////////////
// buildWidgetElem():
// - create Widget-type element instance
EntryValue<Widget> buildWidgetElem(const Str& name, const Str& cate, const Str& des, const NoSqlDatabase::ChildCollection children, const Widget& value) {
	EntryValue<Widget> entry;
	entry.name = name;
	entry.categoryName = cate;
	entry.txtDescription = des;
	entry.childCollection = children;
	entry.value = value;
	return entry;
}

///////////////////////////////////////////////////////////////////////////
// buildIntDB():
// - create integer-type database for testing
NoSqlDB<int> buildIntDB() {
	NoSqlDB<int> db;
	EntryValue<std::string>::ChildCollection childCollection1({});
	EntryValue<int> intElem1 = buildIntElem("First Int Element", "INT", "Integer-type Element", childCollection1, 11111);
	db.addEntry("elem#1", intElem1);
	EntryValue<std::string>::ChildCollection childCollection2({ "elem#1" });
	EntryValue<int> intElem2 = buildIntElem("Second Int Element", "INT", "Another Integer-type Element", childCollection2, 22222);
	db.addEntry("elem#2", intElem2);
	return db;
}

///////////////////////////////////////////////////////////////////////////
// buildStrDB():
// - create string-type database for testing
NoSqlDB<Str> buildStrDB() {
	NoSqlDB<Str> db;
	EntryValue<std::string>::ChildCollection childCollection1({ "elem#4" });
	EntryValue<Str> strElem1 = buildStrElem("First String Element", "STRING", "String-type Element", childCollection1, "string value 1");
	db.addEntry("elem#3", strElem1);
	EntryValue<std::string>::ChildCollection childCollection2({ "elem#5" });
	EntryValue<Str> strElem2 = buildStrElem("Second String Element", "STRING", "Another STRING-type Element", childCollection2, "string value 2");
	db.addEntry("elem#4", strElem2);
	return db;
}

///////////////////////////////////////////////////////////////////////////
// buildWidgetDB():
// - create Widget-type database for testing
NoSqlDB<Widget> buildWidgetDB() {
	NoSqlDB<Widget> db;
	EntryValue<std::string>::ChildCollection childCollection1({});
	Widget w1;
	w1.intData = 1;
	w1.doubleData = 1.11;
	EntryValue<Widget> widgetElem1 = buildWidgetElem("First Widget Element", "WIDGET", "Widget-type Element", childCollection1, w1);
	db.addEntry("elem#5", widgetElem1);
	EntryValue<std::string>::ChildCollection childCollection2({ "elem#5" });
	Widget w2;
	w2.intData = 2;
	w2.doubleData = 2.22;
	EntryValue<Widget> widgetElem2 = buildWidgetElem("Second Widget Element", "WIDGET", "Another Widget-type Element", childCollection2, w2);
	db.addEntry("elem#6", widgetElem2);
	return db;
}

///////////////////////////////////////////////////////////////////////////
// testRequirement2():
// - Provide test code for Requirement #2
void testRequirement2() {
	makeTitle("Test Requirement #2: Integer-type Database");
	NoSqlDB<int> intDB = buildIntDB();
	std::cout << intDB.showDatabase();
	makeTitle("Test Requirement #2: String-type Database");
	NoSqlDB<Str> strDB = buildStrDB();
	std::cout << strDB.showDatabase();
	makeTitle("Test Requirement #2: Widget-type Database");
	NoSqlDB<Widget> widgetDB = buildWidgetDB();
	std::cout << widgetDB.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testAddStr():
// - Provide test code for Requirement #3
// - Use string-type database to demonstrate
void testAddStr() {
	makeTitle("Test Resuqirement #3: Add pairs using string-type DB");
	makeSubTitle("Contents of an initially empty string-type database", '-');
	NoSqlDB<Str> db;
	std::cout << db.showDatabase();
	EntryValue<std::string>::ChildCollection childCollection1({ "elem#2" });
	EntryValue<Str> strElem1 = buildStrElem("First String Element", "STRING", "String-type Element", childCollection1, "string value 1");
	makeComment("Succefully Insert an element with key=elem#1");
	db.addEntry("elem#1", strElem1);
	makeComment("Failed to intert another element with key=elem#1: no duplicate key");
	EntryValue<std::string>::ChildCollection childCollection2({ "elem#1" });
	EntryValue<Str> strElem2 = buildStrElem("Second String Element", "STRING", "Another String-type Element", childCollection2, "string value 2");
	makeComment("Succefully Insert an element with key=elem#2");
	db.addEntry("elem#2", strElem2);
	makeSubTitle("Database contents after adding two pairs");
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testDeleteStr():
// - Provide test code for Requirement #3
// - Use string-type database to demonstrate
void testDeleteStr() {
	makeTitle("Test Resuqirement #3: Delete pairs using string-type DB");
	NoSqlDB<Str> db;
	EntryValue<std::string>::ChildCollection childCollection1({ "elem#2" });
	EntryValue<Str> strElem1 = buildStrElem("First String Element", "STRING", "String-type Element", childCollection1, "string value 1");
	db.addEntry("elem#1", strElem1);
	EntryValue<std::string>::ChildCollection childCollection2({ "elem#1" });
	EntryValue<Str> strElem2 = buildStrElem("Second String Element", "INT", "Another Integer-type Element", childCollection2, "string value 2");
	db.addEntry("elem#2", strElem2);
	makeSubTitle("Initial contents of string-type database", '-');
	std::cout << db.showDatabase() << std::endl;
	makeComment("Delete element with key=elem#1, Child Collection of elem#2 also erase key=elem#1");
	db.deleteEntry("elem#1");
	makeSubTitle("Database contents after deletinging elem#1", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testAddWidget():
// - Provide test code for Requirement #3
// - Use Widget-type database to demonstrate
void testAddWidget() {
	makeTitle("Test Resuqirement #3: Add and Delete using Widget-type database");
	std::cout << std::endl;
	makeSubTitle("Contents of an initially empty Widget-type database", '-');
	NoSqlDB<Widget> db;
	std::cout << db.showDatabase()<<std::endl;
	// Add first pair
	EntryValue<std::string>::ChildCollection childCollection1({ "elem#2" });
	Widget w;
	w.doubleData = 1.11;
	w.intData = 1;
	makeComment("Succefully Insert a Widget element with key=elem#1");
	db.addEntry("elem#1", buildWidgetElem("First Widget", "WIDGET", "Widget-type Element", childCollection1, w));
	EntryValue<std::string>::ChildCollection childCollection2({ "elem#1" });
	Widget w2;
	w2.doubleData = 2.22;
	w2.intData = 2;
	makeComment("Succefully Insert a Widget element with key=elem#2");
	db.addEntry("elem#2", buildWidgetElem("Second Widget", "WIDGET", "Widget-type Element", childCollection2, w2));
	makeSubTitle("Database contents after adding two pairs:", '-');
	std::cout << db.showDatabase() << std::endl;
	makeComment("Succefully Delete Widget element with key=elem#2");
	db.deleteEntry("elem#2");
	makeSubTitle("Database contents after deleting one pair:", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testRequirement3():
// - Provide test code for Requirement #3
void testRequirement3() {
	testAddStr();
	testDeleteStr();
	testAddWidget();
}

///////////////////////////////////////////////////////////////////////////
// testAddChild():
// - demonstrate adding child relationship
void testAddChild(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #4: Add Child Relationship");
	db.addChild("elem#3", "elem#4");
	makeComment("Succefully Add elem#4 as child of elem#3");
	db.addChild("elem#10", "elem#4");
	makeComment("Failed to add elem#4 as child of elem#10: Parent key not exist");
	db.addChild("elem#3", "elem#10");
	makeComment("Failed to add elem#10 as child of elem#3: Child key not exist");
	makeSubTitle("Database contents after adding child relationship:", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testDeleteChild():
// - demonstrate deleting child relationship
void testDeleteChild(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #4: Delete Child Relationship");
	db.deleteChild("elem#3", "elem#4");
	makeComment("Succefully Delete elem#4 from Child Collection of elem#3");
	db.deleteChild("elem#10", "elem#4");
	makeComment("Failed to delete elem#4 from elem#10: Parent key not exist");
	db.addChild("elem#3", "elem#10");
	makeComment("Failed to delete elem#10 from elem#3: Child key not exist");
	makeSubTitle("Database contents after deleting child relationship:", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testEditMetadata():
// - demonstrate edit text metadata
void testEditMetadata(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #4: Edit Text Metadata");
	std::string key = "elem#3";
	std::string newKey = "elem#10";
	db.editStrMetaData(name, key, "NEW NAME");
	makeComment("Succefully Edit Item Name of " + key + " to \"NEW NAME\"");
	db.editStrMetaData(category, key, "NEW CATEGORY");
	makeComment("Succefully Edit Category Name of " + key + " to \"NEW CATEGORY\"");
	db.editStrMetaData(description, key, "NEW DESCRIPTION");
	makeComment("Succefully Edit Description of " + key + " to \"NEW DESCRIPTION\"");
	db.editStrMetaData(addtime, key, "00:00:00 2017/01/01");
	makeComment("Succefully Edit Add Time of " + key + " to \"00:00:00 2017/01/01\"");
	db.editStrMetaData(name, newKey, "NEW NAME");
	makeComment("Failed to edit Item Name of " + newKey + " to \"NEW NAME\": input key not exist");
	makeSubTitle("Database contents after editing text metadata:", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testEditValue():
// - demonstrate editing template value
void testEditValue(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #4: Edit Template Value");
	std::string key = "elem#3";
	std::string newKey = "elem#10";
	db.editValue(key, "NEW STRING VALUE");
	makeComment("Succefully Edit Template Value of " + key + " to \"NEW STRING VALUE\"");
	db.editValue(newKey, "NEW STRING VALUE");
	makeComment("Failed to edit Template Value of " + newKey + ": input key not exist");
	makeSubTitle("Database contents after editing template value:", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testReplaceValue():
// - demonstrate replacing existing value instance with a new instance
void testReplaceValue(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #4: Replace existing instance with new one");
	std::string key = "elem#4";
	std::string newKey = "elem#10";
	EntryValue<std::string>::ChildCollection childCollection({"elem#3"});
	EntryValue<Str> newElem = buildStrElem("REPLACED ELEMENT", "STRING", "REPLACED STRING-TYPE ELEMENT", childCollection, "REPLACED STRING VALUE");
	db.editEntryValue(key, newElem);
	makeComment("Succefully Replace value instance of " + key + " with new instance");
	db.editEntryValue(newKey, newElem);
	makeComment("Failed to replace value instance of " + newKey + ": input key not exist");
	makeSubTitle("Database contents after replacing value instance:", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testRequirement4():
// - Provide test code for Requirement #4
void testRequirement4() {
	makeTitle("Test Resuqirement #4");
	NoSqlDB<Str> db = buildStrDB();
	makeSubTitle("Initial contents of database for Demo", '-');
	std::cout << db.showDatabase() << std::endl;
	// Test adding child relationship
	testAddChild(db);
	// Test deleting child relationship
	testDeleteChild(db);
	// Test editing text metadata
	testEditMetadata(db);
	// Test editing template value
	testEditValue(db);
	// Test replacing existing value instance with a new instance
	testReplaceValue(db);
	makeTitle("Test Resuqirement #4: Edit Key is forbidden!");
	makeComment("No providing any public interface to edit key");
	std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testStrSave():
// - Provide test code for Requirement #5
void testStrSave() {
	makeTitle("Test Resuqirement #5: Save to Xml using string-type DB");
	NoSqlDB<Str> strDB = buildStrDB();
	makeSubTitle("Contents of string-type database", '-');
	std::cout << strDB.showDatabase() << std::endl;
	makeSubTitle("Contents of generated Xml file", '-');
	std::cout << strDB.buildXmlDocument() << "\n\n";
	std::string out = "./XmlFiles/Requirement5_strDemo.xml";
	strDB.save(out);
	makeComment("Save to \"./XmlFiles/Requirement5_strDemo.xml\"");
	std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testStrRestore():
// - Provide test code for Requirement #5
void testStrRestore() {
	makeTitle("Test Resuqirement #5: Restore string-type DB");
	std::cout << std::endl;
	NoSqlDB<Str> db;
	makeSubTitle("Initial Contents of an empty string-type database", '-');
	std::cout << db.showDatabase() << std::endl;
	std::string in = "./XmlFiles/Requirement5_strDemo.xml";
	db.restore(in);
	makeComment("Restore from \"./XmlFiles/Requirement5_strDemo.xml\"");
	makeSubTitle("Database contents after restoring", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testStrAugment():
// - Provide test code for Requirement #5
void testStrAugment() {
	makeTitle("Test Resuqirement #5: Augment string-type DB");
	std::cout << std::endl;
	NoSqlDB<Str> db;
	NoSqlDatabase::ChildCollection childCollection1({});
	db.addEntry("elem#2", buildStrElem("Existing String Element", "STRING", "Existing String-type Element", childCollection1, "existing string value"));
	makeSubTitle("Initial Contents of an empty string-type database", '-');
	std::cout << db.showDatabase() << std::endl;
	std::string in = "./XmlFiles/Requirement5_strDemo.xml";
	db.restore(in);
	makeComment("Augment from \"./XmlFiles/Requirement5_strDemo.xml\"");
	makeSubTitle("Database contents after augmenting", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testWidgetSave():
// - Provide test code for Requirement #5
void testWidgetSave() {
	makeTitle("Test Resuqirement #5: Save to Xml using Widget-type DB");
	NoSqlDB<Widget> widgetDB = buildWidgetDB();
	makeSubTitle("Contents of Widget-type database", '-');
	std::cout << widgetDB.showDatabase() << std::endl;
	makeSubTitle("Contents of generated Xml file", '-');
	std::cout << widgetDB.buildXmlDocument() << "\n\n";
	std::string out = "./XmlFiles/Requirement5_widgetDemo.xml";
	widgetDB.save(out);
	makeComment("Save to \"./XmlFiles/Requirement5_widgetDemo.xml\"");
	std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testWidgetRestore():
// - Provide test code for Requirement #5
void testWidgetRestore() {
	makeTitle("Test Resuqirement #5: Restore Widget-type DB");
	NoSqlDB<Widget> db;
	makeSubTitle("Initial Contents of Widget-type database", '-');
	std::cout << db.showDatabase() << std::endl;
	std::string in = "./XmlFiles/Requirement5_widgetDemo.xml";
	db.restore(in);
	makeComment("Restore from \"./XmlFiles/Requirement5_widgetDemo.xml\"");
	makeSubTitle("Database contents after restoring", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testWidgetAugment():
// - Provide test code for Requirement #5
void testWidgetAugment() {
	makeTitle("Test Resuqirement #5: Augment Widget-type DB");
	NoSqlDB<Widget> db;
	EntryValue<std::string>::ChildCollection childCollection1({});
	Widget w1;
	w1.intData = 3;
	w1.doubleData = 3.33;
	EntryValue<Widget> widgetElem1 = buildWidgetElem("Existing Widget Element", "WIDGET", "Existing Widget-type Element", childCollection1, w1);
	db.addEntry("elem#4", widgetElem1);
	makeSubTitle("Initial Contents of Widget-type database", '-');
	std::cout << db.showDatabase() << std::endl;
	std::string in = "./XmlFiles/Requirement5_widgetDemo.xml";
	db.restore(in);
	makeComment("Augment from \"./XmlFiles/Requirement5_widgetDemo.xml\"");
	makeSubTitle("Database contents after augmenting", '-');
	std::cout << db.showDatabase() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testRequirement5():
// - Provide test code for Requirement #5
void testRequirement5() {
	// Test using string-type database
	testStrSave();
	testStrRestore();
	testStrAugment();
	// Test using Widget-type database
	testWidgetSave();
	testWidgetRestore();
	testWidgetAugment();
}

//////////////////////////////////////////////////////////////////////////
// testOffPersist():
// - Provide test code for Requirement #6
void testOffPersist(NoSqlDB<Str>& db) {
	std::cout << "\n\n";
	makeTitle("Test Requirement #6: By default, timed saving is turned off");
	NoSqlDatabase::ChildCollection childCollection1({});
	db.addEntry("elem#1", buildStrElem("First String Element", "STRING", "String-type Element", childCollection1, "string value 1"));
	makeComment("Succefully Insert an element with key=elem#1");
	NoSqlDatabase::ChildCollection childCollection2({ "elem#1" });
	db.addEntry("elem#2", buildStrElem("Second String Element", "STRING", "Another String-type Element", childCollection2, "string value 2"));
	makeComment("Succefully Insert an element with key=elem#2");
	db.addChild("elem#1", "elem#2");
	makeComment("Succefully Add elem#2 as child of elem#1");
	Persist persist;
	persist.setInPath("./XmlFiles/demoTimedSave.xml");
	makeSubTitle("After 3 write operations, try to read the persisted file");
	std::cout << persist.restore() << std::endl;
	makeComment("After 3 write operations, no persisting is performed");
}

//////////////////////////////////////////////////////////////////////////
// testOnPersist():
// - Provide test code for Requirement #6
void testOnPersist(NoSqlDB<Str>& db) {
	std::cout << "\n\n";
	makeTitle("Test Requirement #6: Timed saving turns ON");
	db.turnOn();
	makeComment("Succefully turn on timed persisting");
	std::string key = "elem#1";
	db.editStrMetaData(name, key, "NEW NAME");
	makeComment("Succefully Edit Item Name of " + key + " to \"NEW NAME\"");
	db.editStrMetaData(category, key, "NEW CATEGORY");
	makeComment("Succefully Edit Category Name of " + key + " to \"NEW CATEGORY\"");	
	db.editValue(key, "NEW STRING VALUE");
	makeComment("Succefully Edit Template Value of " + key + " to \"NEW STRING VALUE\"");
	Persist persist;
	persist.setInPath("./XmlFiles/demoTimedSave.xml");
	makeComment("After 3 write operations, database persisted to \"./XmlFiles/demoTimedSave.xml\"");
	makeSubTitle("Contents of generated Xml file");
	std::cout << persist.restore() << std::endl;
	remove("./XmlFiles/demoTimedSave.xml");
	makeComment("Remove generated Xml file");
}

//////////////////////////////////////////////////////////////////////////
// testOffAgain():
// - Provide test code for Requirement #6
void testOffAgain(NoSqlDB<Str>& db) {
	std::cout << "\n\n";
	makeTitle("Test Requirement #6: Cancel timed saving");
	db.turnOff();
	makeComment("Succefully turn off timed persisting");
	std::string key = "elem#1";
	db.editStrMetaData(name, key, "NEW NEW NAME");
	makeComment("Succefully Edit Item Name of " + key + " to \"NEW NEW NAME\"");
	db.editStrMetaData(category, key, "NEW NEW CATEGORY");
	makeComment("Succefully Edit Category Name of " + key + " to \"NEW NEW CATEGORY\"");
	db.editValue(key, "NEW NEW STRING VALUE");
	makeComment("Succefully Edit Template Value of " + key + " to \"NEW NEW STRING VALUE\"");
	Persist persist;
	persist.setInPath("./XmlFiles/demoTimedSave.xml");
	makeSubTitle("After 3 write operations, try to read the persisted file");
	std::cout << persist.restore() << std::endl;
	makeComment("Again, No persisting is performed cause timed persisting is cancelled");
	std::cout << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testRequirement6():
// - Provide test code for Requirement #6
void testRequirement6() {
	makeTitle("Test Requirement #6: Persist after 3 write operations");
	makeComment("Contruct a string-type DB for Demo");
	NoSqlDB<Str> db;
	testOffPersist(db);
	testOnPersist(db);
	testOffAgain(db);
}

///////////////////////////////////////////////////////////////////////////
// testQueryValue():
// - demonstrate query for value of specified key
void testQueryValue(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #7: Query for value of specified key");
	Query<Str> query(db);
	makeComment("Query for value with key=\"elem#1\" using indexing operator");
	std::cout << "\n  -----< Query Result >-----";
	std::cout << query["elem#1"].showEntryValue() << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testQueryChildren():
// - demonstrate query for children of specified key
void testQueryChildren(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #7: Query for children of specified key");
	Query<Str> query(db);
	makeComment("Query for children with key=\"elem#1\" using indexing operator");
	NoSqlDatabase::ChildCollection children = query["elem#1"][child];
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << show(children) << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testKeyPattern():
// - demonstrate query for key set matching specified key pattern
void testKeyPattern(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #7: Query for keys matching key pattern");
	Query<Str> query(db);
	makeComment("Query for key pattern by default(Should contain all keys)");
	query.matchPattern();
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
	Str keyPattern = "elem#";
	makeComment("Query for keys begin with \"" + keyPattern + "\" in string-type key");
	query.matchPattern(keyPattern);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testQueryName():
// - demonstrate query for keys containing specified string in item name
void testQueryName(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #7: Contain string in Item Name");
	Query<Str> query(db);
	Str queryString = "ea";
	makeComment("Query for keys containing \""+ queryString + "\" in item name");
	query.queryName(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testQueryCategory():
// - demonstrate query for keys containing specified string in category name
void testQueryCategory(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #7: Contain string in Category Name");
	Query<Str> query(db);
	Str queryString = "ea";
	makeComment("Query for keys containing \"" + queryString + "\" in category name");
	query.queryCategory(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testQueryValue():
// - demonstrate query for keys containing specified string in template 
//   value when valid
void testQueryTemplateValue(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #7: Contain string in string-type template value");
	Query<Str> query(db);
	Str queryString = "tity";
	makeComment("Query for keys containing \"" + queryString + "\" in string-type template value");
	query.queryValue(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testQueryTime():
// - demonstrate query for keys written in specified time intervals
void testQueryTime(NoSqlDB<Str>& db) {
	makeTitle("Test Resuqirement #7: Contain value written in certain time-interval");
	Query<Str> query(db);
	std::string start = "22:33:35 2017/02/04";
	std::string end = "22:33:45 2017/02/04";
	makeComment("Query with both ends provided: from " + start + " to " + end);
	query.queryTime(start, end);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
	Query<Str> query1(db);
	makeComment("Query with only one end provided: from " + start + " to current time ", '-');
	query1.queryTime(start);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testRequirement7():
// - Provide test code for Requirement #7
void testRequirement7() {
	makeTitle("Test Requirement #7");
	NoSqlDB<Str> db;
	std::string in = "./XmlFiles/StrDB.xml";
	db.restore(in);
	makeSubTitle("Database contents for query operations", '-');
	std::cout << db.showDatabase() << std::endl;
	// Test query operation for value of specified key
	testQueryValue(db);
	// Test query operation for children of specified key
	testQueryChildren(db);
	// Test query for key set containing key pattern in key
	testKeyPattern(db);
	// Test query for keys containing specified string in item name
	testQueryName(db);
	// Test query for keys containing specified string in category name
	testQueryCategory(db);
	// Test query for keys containing specified string in template value
	testQueryTemplateValue(db);
	// Test query for keys written in specified time intervals
	testQueryTime(db);
}

///////////////////////////////////////////////////////////////////////////
// testDemo1():
// - Provide test code for Requirement #8
void testDemo1() {
	makeTitle("Test Requirement #8: Demo 1");
	NoSqlDB<Str> db;
	std::string in = "./XmlFiles/StrDB.xml";
	db.restore(in);
	Query<Str> query1(db);
	// Conduct first query
	Str queryString = "at";
	makeComment("Independent Query for keys containing \"" + queryString + "\" in Category Name");
	query1.queryCategory(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
	// Conduct second query
	std::string queryString1 = "ea";
	makeComment("Independent Query for keys containing \"" + queryString1 + "\" in Item Name");
	Query<Str> query2(db);
	query2.queryName(queryString1);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query2.showResult() << "\n\n";
	// Conduct compound query
	makeComment("Query for keys containing \"" + queryString1 + "\" in Item Name based on the result");
	makeComment("from previous query for keys containing \"" + queryString + "\" in Category Name");
	query1.queryName(queryString1);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testDemo2():
// - Provide test code for Requirement #8
void testDemo2() {
	makeTitle("Test Requirement #8: Demo 2");
	NoSqlDB<Str> db;
	std::string in = "./XmlFiles/StrDB.xml";
	db.restore(in);
	Query<Str> query1(db);
	// Conduct first query
	std::string start = "22:33:35 2017/02/04";
	std::string end = "22:33:55 2017/02/04";
	makeComment("Independent Query for keys added from " + start + " to " + end);
	query1.queryTime(start, end);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
	// Conduct second query
	Query<Str> query(db);
	Str queryString = "lb";
	makeComment("Independent Query for keys containing \"" + queryString + "\" in string-type template value");
	query.queryValue(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
	// Conduct compound query
	makeComment("Query for keys containing \"" + queryString + "\" in string-type template value on the result of");
	makeComment("previous query for keys added from \"" + start + " to " + end);
	query1.queryValue(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testRequirement8():
// - Provide test code for Requirement #8
void testRequirement8() {
	testDemo1();
	testDemo2();
}

///////////////////////////////////////////////////////////////////////////
// testDemo1(&db):
// - Provide test code for Requirement #9
void testDemo1(NoSqlDB<Str>& db) {
	makeTitle("Test Requirement #9: Demo 1");
	Query<Str> query1(db);
	// Conduct first query
	Str queryString1 = "ea";
	makeComment("Independent Query for keys containing \"" + queryString1 + "\" in Item Name");
	query1.queryName(queryString1);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
	// Conduct second query
	std::string queryString2 = "rui";
	makeComment("Independent Query for keys containing \"" + queryString2 + "\" in Category Name");
	Query<Str> query2(db);
	query2.queryCategory(queryString1);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query2.showResult() << "\n\n";
	// Conduct compound query
	makeComment("Form a union of keys from previous 2 query results");
	query2.unionQuery(query1);
	std::cout << "\n  -----< Key Union >-----";
	std::cout << "\n  " << query2.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testDemo2(&db):
// - Provide test code for Requirement #9
void testDemo2(NoSqlDB<Str>& db) {
	makeTitle("Test Requirement #9: Demo 2");
	Query<Str> query1(db);
	// Conduct first query
	Str queryString1 = "lb";
	makeComment("Independent Query for keys containing \"" + queryString1 + "\" in string-type value");
	query1.queryValue(queryString1);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
	// Conduct second query
	std::string queryString2 = "#5";
	makeComment("Independent Query for keys end with \"" + queryString2 + "\" in string-type key");
	Query<Str> query2(db);
	query2.matchPattern(queryString2);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query2.showResult() << "\n\n";
	// Conduct third query
	std::string start = "22:33:45 2017/02/04";
	std::string end = "22:33:52 2017/02/04";
	makeComment("Query with both ends provided: from " + start + " to " + end);
	Query<Str> query3(db);
	query3.queryTime(start, end);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query3.showResult() << "\n\n";
	// Conduct compound query
	makeComment("Form a union of keys from previous 3 query results");
	query1.unionQuery(query3);
	query1.unionQuery(query2);
	std::cout << "\n  -----< Key Union >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testRequirement9():
// - Provide test code for Requirement #9
void testRequirement9() {
	NoSqlDB<Str> db;
	std::string in = "./XmlFiles/StrDB.xml";
	db.restore(in);
	testDemo1(db);
	testDemo2(db);
}

///////////////////////////////////////////////////////////////////////////
// buildPackageName():
// - build packages-name element
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildPackageName(const std::string& name) {
	NoSqlDatabase::sPtr pTag = makeTaggedElement("package-name");
	NoSqlDatabase::sPtr pText = makeTextElement(name);
	pTag->addChild(pText);
	return pTag;
}

///////////////////////////////////////////////////////////////////////////
// buildPackageElement():
// - build xml element for packages
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildPackageElement(const std::string& name, NoSqlDatabase::sPtr dependency) {
	NoSqlDatabase::sPtr pTag = makeTaggedElement("package");
	pTag->addChild(buildPackageName(name));
	pTag->addChild(dependency);
	return pTag;
}

///////////////////////////////////////////////////////////////////////////
// buildDependency():
// - build empty dependency child
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildDependency() {
	NoSqlDatabase::sPtr pDenp = makeTaggedElement("dependencies");
	NoSqlDatabase::sPtr pChild = makeTextElement("None");
	pDenp->addChild(pChild);
	return pDenp;
}

///////////////////////////////////////////////////////////////////////////
// buildChild():
// - build child dependency sPtr
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildChild(const std::string& text) {
	NoSqlDatabase::sPtr pDenp = makeTaggedElement("dependency");
	NoSqlDatabase::sPtr pText = makeTextElement(text);
	pDenp->addChild(pText);
	return pDenp;
}

///////////////////////////////////////////////////////////////////////////
// buildEntry():
// - build DBEntry dependency child
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildEntry() {
	NoSqlDatabase::sPtr pDenp = makeTaggedElement("dependencies");
	pDenp->addChild(buildChild("CppProperties"));
	pDenp->addChild(buildChild("DBUtilities"));
	return pDenp;
}

///////////////////////////////////////////////////////////////////////////
// buildPersist():
// - build Persist dependency child
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildPersist() {
	NoSqlDatabase::sPtr pDenp = makeTaggedElement("dependencies");
	pDenp->addChild(buildChild("XmlDocument"));
	return pDenp;
}

///////////////////////////////////////////////////////////////////////////
// buildDB():
// - build NoSqlDatabase dependency child
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildDB() {
	NoSqlDatabase::sPtr pDenp = makeTaggedElement("dependencies");
	pDenp->addChild(buildChild("Convert"));
	pDenp->addChild(buildChild("DBUtilities"));
	pDenp->addChild(buildChild("DBEntry"));
	pDenp->addChild(buildChild("XmlDocument"));
	pDenp->addChild(buildChild("Persist"));
	return pDenp;
}

///////////////////////////////////////////////////////////////////////////
// buildQuery():
// - build Query dependency child
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildQuery() {
	NoSqlDatabase::sPtr pDenp = makeTaggedElement("dependencies");
	pDenp->addChild(buildChild("DBUtilities"));
	pDenp->addChild(buildChild("DBEntry"));
	pDenp->addChild(buildChild("NoSqlDatabase"));
	return pDenp;
}

///////////////////////////////////////////////////////////////////////////
// buildTest():
// - build TestExecutive dependency child
using namespace XmlProcessing;
NoSqlDatabase::sPtr buildTest() {
	NoSqlDatabase::sPtr pDenp = makeTaggedElement("dependencies");
	pDenp->addChild(buildChild("CppProperties"));
	pDenp->addChild(buildChild("Persist"));
	pDenp->addChild(buildChild("DBEntry"));
	pDenp->addChild(buildChild("NoSqlDatabase"));
	pDenp->addChild(buildChild("Query"));
	return pDenp;
}

///////////////////////////////////////////////////////////////////////////
// buildPackageDependency():
// - build xml string demonstrating package dependency
using namespace XmlProcessing;
std::string buildPackageDependency(){
	XmlProcessing::XmlDocument doc;
	NoSqlDatabase::sPtr pRoot = makeTaggedElement("package-structure");
	doc.docElement() = pRoot;
	// Add Convert package
	pRoot->addChild(buildPackageElement("Convert", buildDependency()));
	// Add CppProperties package
	pRoot->addChild(buildPackageElement("CppProperties", buildDependency()));
	// Add DBUtilities package
	pRoot->addChild(buildPackageElement("DBUtilities", buildDependency()));
	// Add XmlDocument package
	pRoot->addChild(buildPackageElement("XmlDocument", buildDependency()));
	// Add DBEntry package
	pRoot->addChild(buildPackageElement("DBEntry", buildEntry()));
	// Add Persist package
	pRoot->addChild(buildPackageElement("Persist", buildPersist()));
	// Add NoSqlDatabase package
	pRoot->addChild(buildPackageElement("NoSqlDB", buildDB()));
	// Add Query package
	pRoot->addChild(buildPackageElement("Query", buildQuery()));
	// Add TestExecutive package
	pRoot->addChild(buildPackageElement("TestExecutive", buildTest()));
	return doc.toString();
}

///////////////////////////////////////////////////////////////////////////
// testRequirement10():
// - Provide test code for Requirement #10
void testRequirement10() {
	makeTitle("Test Requirement #10");
	makeComment("Genarate Xml file for package structure");
	std::string xml = buildPackageDependency();
	std::cout << xml << std::endl;
	Persist persist;
	persist.setOutPath("./package_structure.xml");
	persist.save(xml);
	makeComment("Xml File for package structure saved to \"./package_structure.xml\"");
}

///////////////////////////////////////////////////////////////////////////
// testRegexValue():
// - Provide test code for Requirement #12
void testRegexValue(NoSqlDB<Str>& db) {
	makeTitle("Bonus: Query values of specified keys using Regex");
	makeComment("Query values of Keys begin with \"elem#\"");
	Query<Str> query(db);
	std::regex queryString = std::regex("elem#.*");
	std::vector<EntryValue<std::string>> value_set = query[queryString];
	std::cout << "\n  -----< Query Result >-----";
	for (auto entry : value_set) {
		std::cout << entry.showEntryValue();
	}
	std::cout << "\n\n";
	makeComment("Query values of Keys end with \"#3\"");
	Query<Str> query2(db);
	std::regex queryString2 = std::regex(".*#3$");
	std::vector<EntryValue<std::string>> value_set1 = query2[queryString2];
	std::cout << "\n  -----< Query Result >-----";
	for (auto entry : value_set1) {
		std::cout << entry.showEntryValue();
	}
	std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testRegexChild():
// - Provide test code for Requirement #12
void testRegexChild(NoSqlDB<Str>& db) {
	makeTitle("Bonus: Query child collections of specified keys using Regex");
	makeComment("Query children of Keys contains \"lem\"");
	Query<Str> query(db);
	std::regex queryString = std::regex(".*lem.*");
	std::vector<std::unordered_set<std::string>> value_set = query.queryChildrenRE(queryString);
	std::cout << "\n  -----< Query Result: Child Collections of matched K/V pair >-----\n";
	for (auto entry : value_set) {
		std::cout << "  " << show(entry) << std::endl;
	}

	makeComment("Query children of Keys end with \"#1\"");
	Query<Str> query2(db);
	std::regex queryString2 = std::regex(".*#1$");
	std::vector<std::unordered_set<std::string>> value_set1 = query2.queryChildrenRE(queryString2);
	std::cout << "\n  -----< Query Result: Child Collections of matched K/V pair >-----\n";
	for (auto entry : value_set1) {
		std::cout << "  " << show(entry) << std::endl;
	}
	std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////
// testRegexKeyPattern():
// - Provide test code for Requirement #12
void testRegexKeyPattern(NoSqlDB<Str>& db) {
	makeTitle("Bonus: Query keys matching key pattern using Regex");
	makeComment("Query for Keys not end with \"5\" or \"6\"");
	Query<Str> query(db);
	std::regex queryString = std::regex(".*[^56]$");
	query.matchPatternRE(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";

	makeComment("Query children of Keys end with \"#5\"");
	Query<Str> query2(db);
	std::regex queryString2 = std::regex(".*#5$");
	query2.matchPatternRE(queryString2);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query2.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testRegexItem():
// - Provide test code for Requirement #12
void testRegexItem(NoSqlDB<Str>& db) {
	makeTitle("Bonus: Query keys matching Regular Expression in Item Name");
	Query<Str> query(db);
	makeComment("Query for keys whose Item name begin with \"Or\"");
	std::regex queryString = std::regex("Or.*");
	query.queryNameRE(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";

	makeComment("Query for keys whose Item name not contain \"ge\"");
	Query<std::string> query1(db);
	std::regex queryString1 = std::regex(".*[^g][^e]");
	query1.queryNameRE(queryString1);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query1.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testRegexCate():
// - Provide test code for Requirement #12
void testRegexCate(NoSqlDB<Str>& db) {
	makeTitle("Bonus: Query keys matching Regular Expression in Category Name");
	Query<Str> query(db);
	makeComment("Query for keys whose Category Name begin with M or A");
	std::regex queryString = std::regex("[AM].*");
	query.queryCategoryRE(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testRegexTemplateValue():
// - Provide test code for Requirement #12
void testRegexTemplateValue(NoSqlDB<Str>& db) {
	makeTitle("Bonus: Query keys matching Regex in string-type Value");
	Query<Str> query(db);
	makeComment("Query for keys whose Value contains \"ML\" or \"lb\"");
	std::regex queryString = std::regex(".*[l][b]|.*[M][L]");
	query.queryValueRE(queryString);
	std::cout << "\n  -----< Query Result >-----";
	std::cout << "\n  " << query.showResult() << "\n\n";
}

///////////////////////////////////////////////////////////////////////////
// testRequirement12():
// - Provide test code for Requirement #12
void testRequirement12() {
	makeTitle("Test Requirement #12: Bonus");
	NoSqlDB<Str> db;
	std::string in = "./XmlFiles/StrDB.xml";
	db.restore(in);
	makeSubTitle("Database contents for regular expression query", '-');
	std::cout << db.showDatabase() << std::endl;
	testRegexValue(db);
	testRegexChild(db);
	testRegexKeyPattern(db);
	testRegexItem(db);
	testRegexCate(db);
	testRegexTemplateValue(db);
}

int main() {
	testRequirement2();
	testRequirement3();
	testRequirement4();
	testRequirement5();
	testRequirement6();
	testRequirement7();
	testRequirement8();
	testRequirement9();
	testRequirement10();
	testRequirement12();
}

#endif // !TEST_EXECUTIVE