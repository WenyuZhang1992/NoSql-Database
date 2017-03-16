#ifndef PERSIST_H
#define PERSIST_H
/////////////////////////////////////////////////////////////////////
// Persist.h - Persist Operations for database                     //
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
*  - Persist: provide persist operations for NoSqlDB instance;
*    Support save database contents into Xml files
*    Support restore database contents from Xml files
*
*  Public Interface
* ==================
*  Persist persist                         construct a persist instance
*  Persist persist1 = persist              construct persist1 as copy of persist
*  persist.save(std::string)               save string into predefined path
*  persist.restore()                       restore string from predefine path
*  persist.setOutPath(std::string)         set save path
*  persist.setInPath(std::string)          set restore path
*
/////////////////////////////////////////////////////////////////////
// Build Process                                                   //
/////////////////////////////////////////////////////////////////////
//  Required Files:                                                //
//  - Persist.h, Persist.cpp, XmlDocument.h                        //
//                                                                 //
//  Build Process:                                                 //
//    Set preprocessor definition TEST_PERSIST in properties.      //
//    Set HashTable as the startup project.                        //
//    Compile and run in Visual Studio.                            //
//                                                                 //
/////////////////////////////////////////////////////////////////////
*
*  Build Command
* ===============
*    devenv Persist.sln /rebuild debug
*
*  Maintenance History
* =====================
*  ver 1.0 : 07 Feb 17
*  - first release
* 
*/
#include <fstream>
#include <string>
#include <ostream>
#include <chrono>
#include <thread>
#include <functional>

#include "..\XmlDocument\XmlDocument\XmlDocument.h"

namespace NoSqlDatabase {

	/////////////////////////////////////////////////////////////////////
	// Persist:
	// - declares methods used to persist to and restore from xml file
	// - Provide auto-save in certain time interval
	class Persist
	{
	public:

		using Xml = std::string;
		using Path = std::string;
		using sPtr = std::shared_ptr<XmlProcessing::AbstractXmlElement>;

		Persist();                                         // default constructor
		virtual ~Persist() {}                              // destructor
		Persist& operator=(const Persist& persist);        // assignment operator

		void save(Xml xml);                                              // save string-type xml documents into xml file
		Xml restore();                                                   // restore xml file contents into database
		void setOutPath(const Path& out) { fileOutPath = out; }          // set path to save file
		void setInPath(const Path& in) { fileInPath = in; }              // set path to restore from xml file
		//void turnOn() { autoPersist_ = ON; };                          // turn on auto-save in certain time interval
		//void turnOff() { autoPersist_ = OFF; };                        // turn off auto-save in certain time interval

	private:
		
		enum Switch{ ON, OFF };

		Path fileOutPath;                        // path to save xml file
		Path fileInPath;                         // path to restore xml file
		Switch autoPersist_;                     // member to control if conduct auto persist to xml file
		Xml xmlToStr(const Path& inPath);        // private member method to convert file into string
	};

	//----< promotion constructor for Persist class >------------------------------------

	Persist::Persist()
		:autoPersist_(OFF)
	{}

	//----< assignment operator for Persist class >--------------------------------------

	Persist& Persist::operator=(const Persist& persist) {
		if (this != &persist) {
			this->autoPersist_ = persist.autoPersist_;
		}
		return *this;
	}

	//----< save operation for Persist class >-------------------------------------------

	using namespace XmlProcessing;
	void Persist::save(Xml xml) {
		std::fstream out;
		out.open(fileOutPath, std::fstream::out | std::fstream::trunc);
		out << xml;
		out.close();
	}

	//----< restore operation for Persist class >----------------------------------------

	using namespace XmlProcessing;
	Persist::Xml Persist::restore() {
		Xml xml = xmlToStr(fileInPath);
		return xml;
	}

	//----< read xml file into string >--------------------------------------------------

	using namespace XmlProcessing;
	Persist::Xml Persist::xmlToStr(const Path& inPath) {
		Xml xml;
		try
		{
			XmlDocument doc2(inPath, XmlDocument::file);
			xml = doc2.toString();
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n  " << ex.what();
		}
		return xml;
	}

}

#endif // !PERSIST_H
