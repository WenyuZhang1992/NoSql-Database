/////////////////////////////////////////////////////////////////////
// NoSqlDatabase.cpp - NoSql Database                              //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
/////////////////////////////////////////////////////////////////////

#include <iostream>

#include "NoSqlDatabase.h"

using namespace NoSqlDatabase;

#ifdef TEST_NOSQLDATABASE

/////////////////////////////////////////////////////////////////////////////
// Test Functions

//----< build int-type database >--------------------------------------------------

NoSqlDB<int> buildDatabase() {
	// Create first entry
	EntryValue<int> entry1;
	std::string e1 = "entry1";
	entry1.name = "beef";
	entry1.categoryName = "Meat";
	entry1.timeDate = entry1.getTime();
	entry1.txtDescription = "Product of Meat";
	EntryValue<std::string>::ChildCollection childCollection1({ "1" });
	entry1.childCollection = childCollection1;
	entry1.value = 11111;

	// Create second entry
	EntryValue<int> *entry2 = new EntryValue<int>();
	entry2->name = "apple";
	entry2->categoryName = "fruit";
	entry2->txtDescription = "Fruit product";
	EntryValue<std::string>::ChildCollection childCollection2({ "2", "3" });
	entry2->childCollection = childCollection2;
	entry2->value = 22222;

	// Create a new NoSql database
	NoSqlDB<int> db1;
	NoSqlDB<int>::Key key1 = "key #1";
	NoSqlDB<int>::Key key2 = "key #2";
	// add new K/V pairs
	db1.addEntry(key1, entry1);
	db1.addEntry(key2, *entry2);

	std::cout << db1.showDatabase();

	return db1;
}

//----< test requirement 3 >----------------------------------------------------------

void testRequirement3() {
	//makeTitle("Test Requirement #3");
	// Create first entry
	std::cout << std::endl;
	//makeSubTitle("Add Key/Value Pairs");
	EntryValue<int> entry1;
	std::string e1 = "entry1";
	entry1.name = "beef";
	entry1.categoryName = "Meat";
	entry1.timeDate = entry1.getTime();
	entry1.txtDescription = "Product of Meat";
	EntryValue<std::string>::ChildCollection childCollection1({ "1" });
	entry1.childCollection = childCollection1;
	entry1.value = 11111;

	// Create second entry
	EntryValue<int> *entry2 = new EntryValue<int>();
	entry2->name = "apple";
	entry2->categoryName = "fruit";
	entry2->txtDescription = "Fruit product";
	EntryValue<std::string>::ChildCollection childCollection2({});
	entry2->childCollection = childCollection2;
	entry2->value = 22222;

	// Create a new NoSql database
	NoSqlDB<int> *db1 = new NoSqlDB<int>();
	NoSqlDB<int>::Key key1 = "key #1";
	NoSqlDB<int>::Key key2 = "key #2";
	//makeSubTitle("Database content before addition:");
	std::cout << db1->showDatabase();

	// Add new pairs
	db1->addEntry(key1, entry1);
	db1->addEntry(key2, *entry2);
	db1->addEntry(key1, entry1);

	//makeSubTitle("Database content after adding pairs:");
	std::cout << db1->showDatabase();
	
	// Delete pairs
	std::cout << std::endl;
	//makeSubTitle("Delete Key/Value Pairs");
	db1->deleteEntry(key1);
	//makeSubTitle("Database content after deleting pair:");
	std::cout << db1->showDatabase();
}

//----< test requirement 4 >----------------------------------------------------------

template<class _Value>
void testRequirement4(const NoSqlDB<_Value> DB) {
	//makeTitle("Test Requirement #4");
	NoSqlDB<_Value> temp = DB;

	// Test add child relationship
	std::cout << std::endl;
	makeSubTitle("Add Relationships");
	NoSqlDB<_Value>::Key parentKey = "key #1";
	NoSqlDB<_Value>::Key childKey = "key #2";
	temp.addChild(parentKey, childKey);
	temp.addChild(parentKey, childKey);
	std::cout << "\n  Entry with key=\"" << parentKey << "\" after adding child relationship:\n";
	//makeSubTitle("Entry with key=" + parentKey + " after adding child relationship:");
	std::cout << temp.find(parentKey).showEntryValue();

	// Test delete child relationship
	std::cout << std::endl;
	makeSubTitle("Delete Relationships");
	temp.deleteChild(parentKey, childKey);
	std::cout << "\n  Entry with key=\"" << parentKey << "\" after deleting child relationship:\n";
	std::cout << temp.find(parentKey).showEntryValue();

	// Test editing metadata
	std::cout << std::endl;
	makeSubTitle("Edit Metadata");
	// Edit Item Name
	NoSqlDB<_Value>::Key editKey = parentKey;
	std::string newName = "pork";
	temp.editItemName(editKey, newName);
	std::cout << "\n  Entry with key=\"" << editKey << "\" after editing Item Name to \"" << newName << "\":\n";
	std::cout << temp.find(editKey).showEntryValue();
	// Edit
}

//----< test requirement 5 >----------------------------------------------------------

template<class _Value>
void testRequirement5(const NoSqlDB<_Value> DB) {
	//makeTitle("Test Requirement #4");
	NoSqlDB<_Value> temp = DB;
	XmlProcessing::XmlDocument doc = temp.buildXmlDocument();
	std::cout << doc.toString();
}

int main() {

	EntryValue<int> entry1;
	std::string e1 = "entry1";
	entry1.name = "beef";
	entry1.categoryName = "Meat";
	entry1.timeDate = entry1.getTime();
	entry1.txtDescription = "Product of Meat";
	EntryValue<std::string>::ChildCollection childCollection1({ "1" });
	entry1.childCollection = childCollection1;
	entry1.value = 11111;

	// Create second entry
	EntryValue<int> *entry2 = new EntryValue<int>();
	entry2->name = "apple";
	entry2->categoryName = "fruit";
	entry2->txtDescription = "Fruit product";
	EntryValue<std::string>::ChildCollection childCollection2({ "2", "3" });
	entry2->childCollection = childCollection2;
	entry2->value = 22222;

	// Create a new NoSql database
	NoSqlDB<int> *db1 = new NoSqlDB<int>();
	NoSqlDB<int>::Key key1 = "key #1";
	NoSqlDB<int>::Key key2 = "key #2";
	// add new K/V pairs
	db1->addEntry(key1, entry1);
	db1->addEntry(key2, *entry2);

	//testRequirement3();
	//testRequirement4(*db1);
	testRequirement5(*db1);
}

#endif // !TEST_NOSQLDATABASE