#ifndef NOSQLDATABASE_H
#define NOSQLDATABASE_H
/////////////////////////////////////////////////////////////////////
// NoSqlDatabase.h - NoSql Database                                //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
/////////////////////////////////////////////////////////////////////
/*
*  Class Operations
* ==================
*  - NoSqlDB: provide STL container for key/value pairs and functions to
*    implement on the database, offers public interfaces to conducts required operations
*    on the database
*  - Support add and delete new pairs
*  - Support edit element information
*  - Support save and restore xml files
*  - Support turn on and off timed saving
*
*  Public Interface
* ==================
*  NoSqlDB<std::string> db                        default construct a string-type database
*  NoSqlDB<std::string> db1 = db                  construct db1 as copy of db
*  db1[key]                                       indexing for db
*  db1.containKey(key)                            check if contains a key
*  db1.keySet()                                   return key set containing all keys in database
*  db1.addEntry(key, entry)                       add new entry into database
*  db1.deleteEntry(key)                           delete entry from database
*  db1.addChild(key, key)                         add childKey as child of parent key
*  db1.deleteChild(key, key)                      delete childKey from child collection of parent
*  db1.editStrMetadata(Edit_choice, key, string)  edit text metadata
*  db1.editChildCollection(key, children)         edit child collection of specified key
*  db1.editValue(key, T value)                    edit template value of specified key
*  db1.editEntryValue(key, EntryValue entry)      edit element instance with new one
*  db1.turnOn()                                   turn on timed saving
*  db1.turnOff()                                  turn off timed saving
*  db1.buildXmlDocument()                         generate string-type xml for database contents
*  db1.save(std::string)                          persist database to xml file
*  db1.restore(std::string)                       restore or augment database from xml file
*  db1.showDatabase()                             display contents of database
*  parseChild(const std::vector<sPtr>&)           Helper function to parse children into key set
*
/////////////////////////////////////////////////////////////////////
// Build Process                                                   //
/////////////////////////////////////////////////////////////////////
//  Required Files:                                                //
//  - Persist.h, Query.cpp, NoSqlDB.h, DBEntry.h, DBUtilities.h    //
//  - NoSqlDatabase.cpp                                            //
//                                                                 //
//  Build Process:                                                 //
//    Set preprocessor definition TEST_NOSQLDATABASE in properties.//
//    Set HashTable as the startup project.                        //
//    Compile and run in Visual Studio.                            //
//                                                                 //
/////////////////////////////////////////////////////////////////////
*
*  Build Command
* ===============
*    devenv NoSqlDatabase.sln /rebuild debug
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
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <fstream>


#include "..\DBEntry\DBEntry.h"
#include "..\XmlDocument\XmlDocument\XmlDocument.h"
#include "..\XmlDocument\XmlElement\XmlElement.h"
#include "..\Convert\Convert.h"
#include "..\DBUtilities\StrHelper.h"
#include "..\Persist\Persist.h"

namespace NoSqlDatabase {

	///////////////////////////////////////////////////////////////////////////
	// NoSqlDB:
	// - Provides STL container for key/value pairs
	// - Provides functions to read and write from XML documents
	// - Provide functions to update value attributes
	// - all three methods are equivalent

	template<class _Value>
	class NoSqlDB
	{

	public:

		using Key = std::string;
		using Keys = std::unordered_set<Key>;
		using ChildCollection = std::unordered_set<Key>;
		using Value = _Value;
		using EntryValue = EntryValue<Value>;
		using Entry = std::pair<Key, EntryValue>;
		using Database = std::unordered_map<Key, EntryValue>;
		using Xml = std::string;
		using Path = std::string;
		using sPtr = std::shared_ptr<XmlProcessing::AbstractXmlElement>;

		NoSqlDB();                                                    // default constructor		
		NoSqlDB(const NoSqlDB& DB);                                   // copy constructor
		NoSqlDB& operator=(const NoSqlDB& DB);                        // copy assignment operator
		virtual ~NoSqlDB() { save("./DestructedDB/demo.xml"); }       // destructor
		EntryValue operator[](const Key& key);                        // indexing operator
		EntryValue operator[](const Key& key) const;                  // indexing operator for const instance



		// public operation functions for NoSql database
		bool containKey(const Key& key);                                          // check if database contains a key
		Keys keySet();                                                            // return set contains all keys
		bool addEntry(const Key newKey, EntryValue newEntryValue);                // add K/V pair
		EntryValue deleteEntry(const Key oldKey);                                 // delete K/V pair
		bool addChild(const Key parentKey, const Key childKey);                   // add child relationship
		bool deleteChild(const Key parentKey, const Key childKey);                // delete child relationship
		bool editStrMetaData(const Edit_choice choice, const Key key, 
							const std::string newStr);                            // edit string-type metadata
		bool editChildCollection(const Key key, const ChildCollection newChild);  // edit child collection
		bool editValue(const Key key, const Value newValue);                      // edit value
		bool editEntryValue(const Key key, EntryValue newEntry);                  // edit entry value instance
		void turnOn() { autoPersist_ = ON; }                                      // turn on persist to xml file
		void turnOff() { autoPersist_ = OFF; }                                    // turn off persist to xml file
		Xml buildXmlDocument();                                                   // generate xml string based on database contents
		void save(const Path& fileOutPath);                                       // write string-type xml documents into xml file
		void restore(const Path& fileInPath);                                     // read xml into database
		std::string showDatabase();                                               // display database contents in string


	private:

		enum Switch { ON, OFF };

		size_t UPDATE = 3;                       // threshold to persist for number of operations 

		Switch autoPersist_;                     // member to control if conduct auto persist to xml file
		size_t updateTime_;                      // record the number of operations since last persist when autoPersist = ON
		Persist persist_;                        // class instance to conduct save and restore operations
		Database database;                       // unordered_map container to store K/V pairs

		// private helper functions
		size_t size() { return database.size(); }                                 // get size of NoSql database
		void formatDatabase();                                                    // format database after importing from xml
		bool checkUpdate();                                                       // persist to xml file after number of operation
		Entry toPair(const sPtr pKey, const sPtr pElem);                          // generate K/V pair from xml content
		EntryValue toEntryValue(const std::vector<sPtr>& pChildren);              // generate EntryValue from xml contents
		Database toDatabase(const Xml& xmlDocument);                              // generate unordered_map from string-type xml document
		sPtr buildXmlElement(const std::string& tag, const std::string& text);    // generate xml element from xml file 
		sPtr buildChildrenElement(const std::string& tag,
			const ChildCollection children);                                      // generate children element from xml file
		sPtr buildValueElement(const EntryValue& value);                          // generate xml element for K/V pair from xml file
		bool addWithoutCheck(Entry newEntry);                                     // add new K/V pair without checking children
		void import(const Database db);                                           // import from unordered_map container
	};

	//----< default constructor for NoSql database >-------------------------------------

	template<class _Value>
	NoSqlDB<_Value>::NoSqlDB() 
		:database(Database()),
		 updateTime_(0),
		 autoPersist_(OFF)
	{}

	//----< copy constructor for NoSql database >----------------------------------------

	template<class _Value>
	NoSqlDB<_Value>::NoSqlDB(const NoSqlDB<_Value>& DB) 
		:database(DB.database),
		 updateTime_(0),
		 autoPersist_(OFF)
	{}

	//----< copy assignment operator for NoSql database >--------------------------------

	template<class _Value>
	NoSqlDB<_Value>& NoSqlDB<_Value>::operator=(const NoSqlDB<_Value>& DB) {
		if (this != &DB) {
			this->database = DB.database;
			this->updateTime_ = 0;
			this->autoPersist_ = OFF;
		}
		return *this;
	}

	//----< indexing operator for NoSql database >---------------------------------------

	template<class _Value>
	typename NoSqlDB<_Value>::EntryValue NoSqlDB<_Value>::operator[](const Key& key) {
		EntryValue temp = EntryValue();
		if (containKey(key))
			temp = database[key];
		return temp;
	}

	//----< indexing operator for const instance >---------------------------------------

	template<class _Value>
	typename NoSqlDB<_Value>::EntryValue NoSqlDB<_Value>::operator[](const Key& key) const {
		EntryValue temp = EntryValue();
		if (containKey(key))
			temp = database[key];
		return temp;
	}

	//----< check if database contains a key >-------------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::containKey(const Key& key) {
		Database::iterator iter = database.find(key);
		if (iter == database.end())
			return false;
		return true;
	}

	//----< format the database after importing xml contents >---------------------------

	template<class _Value>
	void NoSqlDB<_Value>::formatDatabase() {
		Keys key_set = keySet();
		for (Entry entry : database) {
			ChildCollection children = entry.second.childCollection.getValue();
			for (Key key : children) {
				if (key_set.find(key) == key_set.end()) {
					deleteChild(entry.first, key);
				}
			}
		}
	}

	//----< return a set contains all keys in database >---------------------------------

	template<class _Value>
	typename NoSqlDB<_Value>::Keys NoSqlDB<_Value>::keySet() {
		Keys keys;
		for (Entry entry : database) {
			keys.insert(entry.first);
		}
		return keys;
	}

	//----< add new pair into database >-------------------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::addEntry(const Key newKey, EntryValue newEntryValue) {
		newEntryValue.timeDate = getTime();
		auto entry = std::make_pair(newKey, newEntryValue);
		auto result = database.insert(entry);  
		// If key previously not exist
		if (result.second) {
			formatDatabase();
			checkUpdate();
			return true;
		}
		// key already exist
		return false;
	}

	//----< delete pair from database >--------------------------------------------------

	template<class _Value>
	typename NoSqlDB<_Value>::EntryValue NoSqlDB<_Value>::deleteEntry(const Key oldKey) {

		// If key exists
		if (containKey(oldKey)) {
			EntryValue temp = database[oldKey];
			database.erase(oldKey);
			// delete key from other elements' child collections
			formatDatabase();
			checkUpdate();
			return temp;
		}
		return EntryValue();
	}

	//----< add child relationship >-----------------------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::addChild(const Key parentKey, const Key childKey) {
		// If parentKey not exist
		if (!containKey(parentKey)) {
			return false;
		}
		// if childKey not exist
		if (!containKey(childKey)) {
			return false;
		}
		if (database[parentKey].addToChildCollection(childKey)) {
			checkUpdate();
			return true;
		}
		// If childKey already exist in child collection
		return false;
	}

	//----< delete child relationship >-----------------------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::deleteChild(const Key parentKey, const Key childKey) {
		// If parentKey not exist
		if (!containKey(parentKey)) {
			return false;
		}
		if (database[parentKey].deleteFromChildCollection(childKey)) {
			//checkUpdate();
			return true;
		}
		// if childKey not exist
		return false;
	}

	//----< edit string-type metadata >--------------------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::editStrMetaData(const Edit_choice choice, const Key key, const std::string newStr) {
		if (containKey(key)) {
			// Choose which text data to edit
			switch (choice) {
			case name:
				database[key].name = newStr;
				break;
			case category:
				database[key].categoryName = newStr;
				break;
			case description:
				database[key].txtDescription = newStr;
				break;
			case addtime:
				database[key].timeDate = newStr;
				break;
			}
			checkUpdate();
			return true;
		}
		// If key not exist
		return false;
	}

	//----< edit child collection >------------------------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::editChildCollection(const Key key, const ChildCollection newChild) {
		if (containKey(key)) {
			database[key].childCollection = newChild;
			formatDatabase();
			checkUpdate();
			return true;
		}
		// If key not exist
		return false;
	}

	//----< edit value >-----------------------------------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::editValue(const Key key, const Value newValue) {
		if (containKey(key)) {
			database[key].value = newValue;
			checkUpdate();
			return true;
		}
		return false;
	}

	//----< edit entry value instance >--------------------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::editEntryValue(const Key key, EntryValue newEntry) {
		if (containKey(key)) {
			newEntry.timeDate = getTime();
			database[key] = newEntry;
			checkUpdate();
			return true;
		}
		// If key not exist
		return false;
	}

	//----< import from container >------------------------------------------------------

	template<class _Value >
	void NoSqlDB<_Value>::import(const Database db) {
		for (Entry entry : db) {
			addWithoutCheck(entry);
		}
		// check the validity of child collections
		formatDatabase();
		checkUpdate();
	}

	//----< generate xml element >-------------------------------------------------------

	using namespace XmlProcessing;
	template<class _Value>
	typename NoSqlDB<_Value>::sPtr NoSqlDB<_Value>::buildXmlElement(const std::string& tag, const std::string& text) {
		sPtr pTag = makeTaggedElement(tag);
		sPtr pText = makeTextElement(text);
		pTag->addChild(pText);
		return pTag;
	}

	//----< generate children element >--------------------------------------------------

	using namespace XmlProcessing;
	template<class _Value>
	typename NoSqlDB<_Value>::sPtr NoSqlDB<_Value>::buildChildrenElement(const std::string& tag, ChildCollection children) {
		sPtr pChild = makeTaggedElement(tag);
		for (Key key : children) {
			sPtr child = makeTaggedElement("child");
			pChild->addChild(child);
			sPtr chilsStr = makeTextElement(key);
			child->addChild(chilsStr);
		}
		return pChild;
	}

	//----< generate key element for K/V pair >------------------------------------------

	using namespace XmlProcessing;
	template<class _Value>
	typename NoSqlDB<_Value>::sPtr NoSqlDB<_Value>::buildValueElement(const EntryValue& value) {
		sPtr pElement = makeTaggedElement("element");

		// make item-name element and add to pKey
		pElement->addChild(buildXmlElement("item-name", value.name));
		// make category-name element and add to pKey
		pElement->addChild(buildXmlElement("category-name", value.categoryName));
		// make description element and add to pKey
		pElement->addChild(buildXmlElement("description", value.txtDescription));
		// make time-date element and add to pKey
		pElement->addChild(buildXmlElement("time-date", value.timeDate));
		// make child-collection element and add to pKey
		ChildCollection children = value.childCollection;
		pElement->addChild(buildChildrenElement("children", children));
		// make value element and add to pKey
		std::string valueString = Convert<_Value>::toString(value.value);
		pElement->addChild(buildXmlElement("value", valueString));

		return pElement;
	}

	//----< generate xml documents on current database contents >------------------------
	
	using namespace XmlProcessing;
	template<class _Value>
	typename NoSqlDB<_Value>::Xml NoSqlDB<_Value>::buildXmlDocument() {
		XmlProcessing::XmlDocument doc;
		sPtr pRoot = makeTaggedElement("NoSqlDatabase");
		doc.docElement() = pRoot;

		for (Entry entry : database) {
			pRoot->addChild(buildXmlElement("key", entry.first));
			pRoot->addChild(buildValueElement(entry.second));
		}
		return doc.toString();
	}

	//----< save xml documents into files >---------------------------------------------

	template<class _Value>
	void NoSqlDB<_Value>::save(const Path& fileOutPath) {
		Xml xmlDocument = buildXmlDocument();
		persist_.setOutPath(fileOutPath);
		persist_.save(xmlDocument);
	}

	//----< restore xml documents into database >----------------------------------------

	template<class _Value>
	void NoSqlDB<_Value>::restore(const Path& fileInPath) {
		persist_.setInPath(fileInPath);
		Xml xml = persist_.restore();
		Database fromXml = toDatabase(xml);
		import(fromXml);
		checkUpdate();
	}

	//----< add new K/V pair without check childCollection >-----------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::addWithoutCheck(Entry newEntry) {
		auto result = database.insert(newEntry);

		if (result.second) {
			return true;
		}
		std::cout << "\n  -----<Xml Entry failed to be inserted!>-----\n\n";
		return false;
	}

	//----< generate STL container from xml contents >-----------------------------------

	using namespace XmlProcessing;
	template<class _Value>
	typename NoSqlDB<_Value>::Database NoSqlDB<_Value>::toDatabase(const Xml& xmlDocument) {
		Database xmlDatabase;
		try {
			XmlDocument doc(xmlDocument, XmlDocument::str);
			std::vector<sPtr> keyDesc = doc.descendents("key").select();
			std::vector<sPtr> elemDesc = doc.descendents("element").select();
			// check if each key match an element
			if (keyDesc.size() != elemDesc.size()) {
				std::cout << "\n  Unvalid Xml File!" << std::endl;
				return Database();
			}

			for (size_t i = 0; i < keyDesc.size(); i++) {
				xmlDatabase.insert(toPair(keyDesc[i], elemDesc[i]));
			}
		}
		catch (std::exception& ex)
		{
			std::cout << "\n  " << ex.what();
		}
		return xmlDatabase;
	}

	//----< generate K/V pair from xml contents >----------------------------------------

	using namespace XmlProcessing;
	template<class _Value>
	typename NoSqlDB<_Value>::Entry NoSqlDB<_Value>::toPair(const sPtr pKey, const sPtr pElem) {
		Entry newPair;
		try {
			newPair.first = trim(pKey->children()[0]->value());
			newPair.second = toEntryValue(pElem->children());
		}
		catch (std::exception& ex)
		{
			std::cout << "\n  " << ex.what();
		}
		return newPair;
	}

	//----< generate EntryValue from xml contents >--------------------------------------

	using namespace XmlProcessing;
	template<class _Value>
	typename NoSqlDB<_Value>::EntryValue NoSqlDB<_Value>::toEntryValue(const std::vector<sPtr>& pChildren) {
		EntryValue newEntryValue;
		newEntryValue.name = trim(pChildren[0]->children()[0]->value());
		newEntryValue.categoryName = trim(pChildren[1]->children()[0]->value());
		newEntryValue.txtDescription = trim(pChildren[2]->children()[0]->value());
		newEntryValue.timeDate = trim(pChildren[3]->children()[0]->value());
		newEntryValue.childCollection = parseChild(pChildren[4]->children());
		newEntryValue.value = Convert<_Value>::fromString(pChildren[5]->children()[0]->value());
		return newEntryValue;
	}

	//----< convert database contents to string >----------------------------------------

	template<class _Value>
	std::string NoSqlDB<_Value>::showDatabase() {
		std::ostringstream out;
		size_t count = 1;
		if (size()) {
			std::cout << "\n  -----< This NoSql Database contains " << size() << " elements >-----\n";
			for (auto iter : database) {
				out << "\n  -----< " << "Element >-----";
				out << "\n    " << std::setw(3) << "Key" << " : " << iter.first;
				out << iter.second.showEntryValue();
				count++;
			}
		}
		else {
			out << "\n   -----<Empty Database>-----" << std::endl;
		}
		return out.str();
	}

	//----< persist to xml file after operations >---------------------------------------

	template<class _Value>
	bool NoSqlDB<_Value>::checkUpdate() {
		if (autoPersist_ == OFF) {
			return false;
		}
		updateTime_++;
		if (updateTime_ >= UPDATE) {
			save("./XmlFiles/demoTimedSave.xml");
		}
		return true;
	}

	///////////////////////////////////////////////////////////////////////////
	// parseChild():
	// - Helper function parse childCollection in xml into key set
	using namespace XmlProcessing;
	using ChildCollection = std::unordered_set<std::string>;
	using sPtr = std::shared_ptr<XmlProcessing::AbstractXmlElement>;
	ChildCollection parseChild(const std::vector<sPtr>& pChildren) {
		ChildCollection newCollection;
		for (sPtr temp : pChildren) {
			newCollection.insert(trim(temp->children()[0]->value()));
		}
		return newCollection;
	}
}


#endif // !NOSQLDATABASE_H 