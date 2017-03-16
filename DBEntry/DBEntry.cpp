/////////////////////////////////////////////////////////////////////
// KVEntry.cpp - Entry key/value information for databases         //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
/////////////////////////////////////////////////////////////////////
/*
*  Class Operations
* ====================
*  - EntryValue: provides definition and functions to maintain the entry value
*    associated with each pair of key/value database
*  - Provide method to display information of entry
*  - Provide method to display children of entry
*  - Provide access to child collection
*
*  Public Interface
* ==================
*  EntryValue<std::string> entry()                          default construct a string-type entry instance
*  EntryValue<std::string> entry1 = entry                   construct entry1 as copy of entry
*  entry1[child]                                            obtain child collection by indexing operator
*  entry1.addToChildCollection(key)                         add new child key
*  entry1.deleteFromChildCollection(key)                    delete child key
*  entry1.containChild(key)                                 check if child key contains
*  entry1.showChildCollection()                             display contents of child collection
*  entry1.showEntryValue()                                  display information of entry
*  entry1.showValue()                                       display template value in string
*
/////////////////////////////////////////////////////////////////////
// Build Process                                                   //
/////////////////////////////////////////////////////////////////////
//  Required Files:                                                //
//  - DBEntry.h, DBEntry.cpp, DBUtilities.h, CppProperties.h       //
//                                                                 //
//  Build Process:                                                 //
//    Set preprocessor definition TEST_DBENTRY in properties.      //
//    Set HashTable as the startup project.                        //
//    Compile and run in Visual Studio.                            //
//                                                                 //
/////////////////////////////////////////////////////////////////////
*
*  Build Command
* ===============
*    devenv DBEntry.sln /rebuild debug
*
*  Maintenance History
* =====================
*  ver 1.0 : 07 Feb 17
*  - first release
*
*/
#include "DBEntry.h"
#include "unordered_map"

using namespace NoSqlDatabase;

//----< test stub >-------------------------------------------------------------------


#ifdef TEST_DBENTRY

///////////////////////////////////////////////////////////////////////////
// EntryDemo1():
// - Provide test code
void EntryDemo1() {
	std::cout << "\n  Test Code for EntryValue class";
	std::cout << "\n ================================\n";
	EntryValue<std::string> entry1;
	std::string e1 = "entry1";
	entry1.name = "beef";
	entry1.categoryName = "Meat";
	entry1.txtDescription = "Product of Meat";
	EntryValue<std::string>::ChildCollection childCollection1({ "1", "2" });
	entry1.childCollection = childCollection1;
	entry1.value = "Value of beef";
	std::cout << "\n  Entry Value of entry1<string>";
	std::cout << "\n -------------------------------\n";
	std::cout << entry1.showEntryValue();
}

///////////////////////////////////////////////////////////////////////////
// EntryDemo2():
// - Provide test code
void EntryDemo2() {
	EntryValue<int> *entry2 = new EntryValue<int>();
	entry2->name = "apple";
	entry2->categoryName = "fruit";
	entry2->txtDescription = "Fruit product";
	EntryValue<std::string>::ChildCollection childCollection2({});
	childCollection2.insert("2");
	//entry2->childCollection = childCollection2;
	entry2->value = 15;

	std::cout << "\n  Entry Value of entry2<int>";
	std::cout << "\n ----------------------------\n";
	entry2->addToChildCollection("2");
	entry2->addToChildCollection("1");
	entry2->deleteFromChildCollection("1");
	entry2->deleteFromChildCollection("3");
	std::cout << entry2->showEntryValue();
}

int main() {
	// Test demo 1
	EntryDemo1();
	// Test demo 2
	EntryDemo2();
}

#endif // !TEST_DBENTRY




