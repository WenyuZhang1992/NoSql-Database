#ifndef DBENTRY_H
#define DBENTRY_H
/////////////////////////////////////////////////////////////////////
// KVEntry.h - Entry key/value information for key/value databases //
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

#include <iostream>
#include <string>
#include <unordered_set>
#include <iomanip>

#include "..\CppProperties\CppProperties.h"
#include "..\DBUtilities\DBUtilities.h"

enum Edit_choice { name, category, description, addtime, child };

namespace NoSqlDatabase 
{

	///////////////////////////////////////////////////////////////////////////
	// EntryValue:
	// - Contains MetaData and Value information for each key/value pair
	// - Provide access to MetaData and Value attributes
	// - Provide functions to update child collection
	// - Provide function to display EntryValue contents

	template<class _Value>
	class EntryValue 
	{

	public:

		using Key = std::string;
		using Name = std::string;
		using Category = std::string;
		using Description = std::string;
		using TimeDate = std::string;
		using ChildCollection = std::unordered_set<Key>;
		using Value = _Value;

		Property<Name> name;                       // metadata
		Property<Category> categoryName;           // metadata
		Property<TimeDate> timeDate;               // metadata
		Property<Description> txtDescription;      // metadata
		Property<ChildCollection> childCollection; // metadata
		Property<Value> value;                     // value

		// constructor and destructor for EntryValue class
		EntryValue() { timeDate = "-"; }                      // default constructor
		EntryValue(const EntryValue& entryValue);             // copy constructor
		EntryValue& operator=(const EntryValue& entryValue);  // copy assignment operator
		ChildCollection operator[](Edit_choice child);        // index operator for child collection
		ChildCollection operator[](Edit_choice child) const;  // index operator for child collection for const instance
		virtual ~EntryValue() {}                              // destructor

		bool addToChildCollection(const Key& childKey);       // add child relationship
		bool deleteFromChildCollection(const Key& childKey);  // delete child relationship
		bool containChild(const Key& childKey);               // check if contain a key as child 

		// helper function to display EntryValue attributes information
		std::string showChildCollection();          // return the contents of childCollection_ in string
		std::string showValue();                    // return value_ attribute in string
		std::string showEntryValue();               // display whole entry value information

	};

	//----< copy constructor >-----------------------------------------------------------

	template<class _Value>
	EntryValue<_Value>::EntryValue(const EntryValue<_Value>& entryValue) {
		name = entryValue.name;
		categoryName = entryValue.categoryName;
		timeDate = entryValue.timeDate;
		txtDescription = entryValue.txtDescription;
		childCollection = entryValue.childCollection;
		value = entryValue.value;
	}

	//----< copy assignment operator >---------------------------------------------------

	template<class _Value>
	EntryValue<_Value>& EntryValue<_Value>::operator=(const EntryValue<_Value>& entryValue) {
		if (this != &entryValue) {
			this->name = entryValue.name;
			this->categoryName = entryValue.categoryName;
			this->timeDate = entryValue.timeDate;
			this->txtDescription = entryValue.txtDescription;
			this->childCollection = entryValue.childCollection;
			this->value = entryValue.value;
		}
		return *this;
	}

	//----< index operator >-------------------------------------------------------------

	template<class _Value>
	typename EntryValue<_Value>::ChildCollection EntryValue<_Value>::operator[](Edit_choice child) {
		if (child == Edit_choice::child)
			return childCollection.getValue();
		return ChildCollection();
	}

	//----< index operator for const instance >------------------------------------------

	template<class _Value>
	typename EntryValue<_Value>::ChildCollection EntryValue<_Value>::operator[](Edit_choice child) const {
		if (child == Edit_choice::child)
			return childCollection.getValue();
		return ChildCollection();
	}

	//----< add child collection >-------------------------------------------------------

	template<class _Value>
	bool EntryValue<_Value>::addToChildCollection(const Key& childKey) {
		ChildCollection &temp = childCollection.getValue();
		ChildCollection::iterator iter = temp.find(childKey);
		if (iter != temp.end())
			//std::cout << "\n The Key: " << newKey << "already exists.\n";
			return false;
		else {
			temp.insert(childKey);
			childCollection = temp;
			return true;
		}
	}

	//----< delete child collection >----------------------------------------------------

	template<class _Value>
	bool EntryValue<_Value>::deleteFromChildCollection(const Key& childKey) {
		ChildCollection &temp = childCollection.getValue();
		if (!temp.erase(childKey))
			return false;
		else {
			childCollection = temp;
			return true;
		}
	}

	//----< check if contains a child key >----------------------------------------------

	template<class _Value>
	bool EntryValue<_Value>::containChild(const Key& childKey) {
		ChildCollection &temp = childCollection.getValue();
		ChildCollection::iterator iter = temp.find(childKey);
		if (iter != temp.end())
			return true;
		return false;
	}

	//----< return contents of childCollection_ in string >------------------------------

	template<class _Value>
	std::string EntryValue<_Value>::showChildCollection() {
		return show(childCollection.getValue());
	}

	//----< return value_ attribute in string >------------------------------------------

	template<class _Value>
	std::string EntryValue<_Value>::showValue() {
		std::ostringstream out;
		out << value;
		return out.str();
	}

	//----< return EntryValue information in string >------------------------------------

	template<class _Value>
	std::string EntryValue<_Value>::showEntryValue() {
		std::ostringstream out;
		out << "\n    " << std::setw(8) << "Item Name" << " : " << name;
		out << "\n    " << std::setw(8) << "Category Name" << " : " << categoryName;
		out << "\n    " << std::setw(8) << "Description" << " : " << txtDescription;		
		out << "\n    " << std::setw(8) << "Child Collection" << " : " << showChildCollection();
		out << "\n    " << std::setw(8) << "Add Time" << " : " << timeDate;
		out << "\n    " << std::setw(5) << "Value" << " : " << value;
		out << std::endl;
		return out.str();
	}

}
#endif // !DBENTRY_H