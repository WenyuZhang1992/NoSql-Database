#ifndef TESTEXECUTIVE_H
#define TESTEXECUTIVE_H
/////////////////////////////////////////////////////////////////////
// TestExecutive.h - Test code for project #1                      //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations
* ===================
*  This package contains a class: Widget, mainly used for demonstrating 
*  the template value capacility of NoSqlDatabase
*  This package also provides separated testing code and executive 
*  for whole project
*  This package clearly demonstrates Requirement #2-#9 of project 1
*  
*  - Widget: provide class for testing;
*    - Contain a int-type member
*    - Contain a double-type member
*    - Support istream and ostream operation
*
*  Public Interface
* ==================
*  Widget widget                            construct a widget instance
*  widget.intData = 1                       assign widget's int member
*  widget.doubleData = 1.11                 assign widget's double member
*  std::cout << widget                      ostream widget into string with format [ 1, 1.11 ]
*  in >> widget                             widget assignment using istream
*
*  buildIntElem()                           create an int-type element
*  buildStrElem()                           create a string-type element
*  buildWidgetElem()                        create a widget-type element
*  buildIntDB()                             create a int-type NoSqlDB for demonstrating
*  buildStrDB()                             create a String-type NoSqlDB for demonstrating
*  buildWidgetDB()                          create a Widget-type NoSqlDB for demonstrating
*  testAddStr()                             test adding new pair for string-type database
*  testDeleteStr()                          test deleting pair for string-type database
*  testAddWidget()                          test adding new pair for Widget-type database
*  testDeleteWidget()                       test deleting pair for Widget-type database
*  testAddChild()                           test adding child relationship
*  testDeleteChild()                        test deleting child relationship
*  testEditMetadata()                       test editing text metadata
*  testEditValue()                          test editing template value
*  testReplaceValue()                       demonstrating replacing existing instance with new instance
*  testStrSave()                            test saving process using string-type database
*  testStrRestore()                         test restoring process using string-type database
*  testStrAugment()                         test augmenting process using string-type database
*  testWidgetSave()                         test saving process using Widget-type database
*  testWidgetRestore()                      test restoring process using Widget-type database
*  testWidgetAugment()                      test augmenting process using Widget-type database
*  testOffPersist()                         test timed persisting by default
*  testOnPersist()                          test timed persisting after turning on
*  testOffAgain()                           test timed persisting process after cancelling
*  testQueryValue(NoSqlDB<Str>& db)         test query value of specified key
*  testQueryChildren(NoSqlDB<Str>& db)      test query children of specified key
*  testKeyPattern(NoSqlDB<Str>& db)         test query for keys matching key pattern
*  testQueryName(NoSqlDB<Str>& db)          test query item name
*  testQueryCategory(NoSqlDB<Str>& db)      test query category name
*  testQueryValue(NoSqlDB<Str>& db)         test query string-type value
*  testQueryTime(NoSqlDB<Str>& db)          test query time interval
*  testDemo1()                              provide one demo for testing Requirement #8
*  testDemo2()                              provide another demo for testing Requirement #8
*  testDemo1(NoSqlDB<Str>& db)              provide one demo for testing Requirement #9
*  testDemo2(NoSqlDB<Str>& db)              provide another demo for testing Requirement #9
*  buildPackageDependency()                 provide code to generate package structure xml file
*  testRegexValue(NoSqlDB<Str>& db)         test regex used for query value of specified keys
*  testRegexChild(NoSqlDB<Str>& db)         test regex used for query children of specified keys
*  testRegexKayPattern(NoSqlDB<Str>& db)    test regex used for query of keys matching key pattern
*  testRegexItem(NoSqlDB<Str>& db)          test regex used for query item name
*  testRegexCate(NoSqlDB<Str>& db)          test regex used for query category name
*  testRegexTemplateValue(NoSqlDB<Str>& db) test regex used for query item name
*  testRequirement2()              display Requirement #2
*  testRequirement3()              display Requirement #3
*  testRequirement4()              display Requirement #4
*  testRequirement5()              display Requirement #5
*  testRequirement6()              display Requirement #6
*  testRequirement7()              display Requirement #7
*  testRequirement8()              display Requirement #8
*  testRequirement9()              display Requirement #9
*  testRequirement10()             generated package-structure and display in console
*  testRequirement12()             display Requirement #12: Bonus
*
/////////////////////////////////////////////////////////////////////
// Build Process                                                   //
/////////////////////////////////////////////////////////////////////
//  Required Files:                                                //
//  - CppProperty.h, NoSqlDB.h, DBEntry.h,                         //
//  - DBUtilities.h, TestExecutive.h, TestExecutive.cpp            //
//  - Persist.h, Query.h, Convert.h, StrHelper.h                   //
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
*    devenv TestExecutive.sln /rebuild debug
*
*  Maintenance History
* =====================
*  ver 1.0 : 07 Feb 17
*  - first release
*
*/

#include <iostream>

#include "..\CppProperties\CppProperties.h"
#include "..\DBEntry\DBEntry.h"
#include "..\NoSqlDatabase\NoSqlDatabase.h"

namespace NoSqlDatabase {
	
	///////////////////////////////////////////////////////////////////////////
	// Widget:
	// - class built for demonstration
	// - contains a integer-type member and a double-type member
	class Widget
	{
	public:

		Property<int> intData;
		Property<double> doubleData;

		friend std::ostream& operator<<(std::ostream &output, const Widget& num);
		friend std::istream& operator>>(std::istream &input, Widget& num);

	};

	std::ostream& operator<<(std::ostream &output, const Widget& num)
	{
		output << "[ " << num.intData << ", "
			<< num.doubleData << " ]";
		return output;
	}

	std::istream& operator>>(std::istream &input, Widget& num)
	{
		int i;
		double d;
		input.ignore(2);
		input >> i;
		input.ignore(2);
		input >> d;
		num.intData = i;
		num.doubleData = d;
		return input;
	}
}


#endif // !TESTEXECUTIVE_H

