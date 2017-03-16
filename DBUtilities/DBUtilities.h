#pragma once
/////////////////////////////////////////////////////////////////////
// DBUtilities.h - Generally useful helper functions               //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
// Reference:   Jim Fawcett, CST 4-187, Syracuse University        //
//              jfawcett@twcny.rr.com, (315) 443-3948              //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations
* ====================
*  - This package provides some simple but generally useful functions
*    needed by this project
*  - The functions inside this package have high reusability
*  - Provide methods mainly for displaying or demonstrating
*
*  Public Interface
* ==================
*  std::string showItem(const T&)                 show an template item in string
*  std::string showItem(const std::pair<K, V>&)   show an template pair in string
*  std::string show(Cont& cont)                   show the contents of STL in string
*  makeTitle(std::string)                         display a string-type title
*  makeSubTitle(std::string)                      display a string-type subtitle
*  makeComment(std::string)                       display a string0type comment
*  std::string getTime()                          get current time and return in string
*  time_t strToTime(std::string)                  convert time string into time_t
*
/////////////////////////////////////////////////////////////////////
// Build Process                                                   //
/////////////////////////////////////////////////////////////////////
//  Required Files:                                                //
//  - DBUtilities.h, DBUtilities.cpp                               //
//                                                                 //
//  Build Process:                                                 //
//    Set preprocessor definition TEST_DBUTILITIES in properties.  //
//    Set HashTable as the startup project.                        //
//    Compile and run in Visual Studio.                            //
//                                                                 //
/////////////////////////////////////////////////////////////////////
*
*  Build Command
* ===============
*    devenv DBUtilities.sln /rebuild debug
*
*  Maintenance History
* =====================
*  ver 1.0 : 07 Feb 17
*  - first release
*
*/
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <functional>

/*----< show item >------------------------------------------*/

template <typename T>
std::string showItem(const T& item)
{
  std::ostringstream out;
  out << item;
  return out.str();
}
/*----< show pair as item >----------------------------------*/

template <typename K, typename V>
std::string showItem(const std::pair<K, V>& pr)
{
  std::ostringstream out;
  out << "{" << (pr.first) << ", " << (pr.second) << "}";
  return out.str();
}

/*----< display contents of STL container >------------------*/

enum alignment { horizontal, vertical };

template <typename Cont>
std::string show(Cont& cont, bool endNewLine = false, alignment al = alignment::horizontal)
{
  std::ostringstream out;
  //out << "\n  ";
  out << "[ ";
  bool first = true;
  for (auto item : cont)
  {
    if (first)
    {
      out << showItem(item);
      first = false;
    }
    else if (al == horizontal)
      out << ", " << showItem(item);
    else
      out << "\n  " << showItem(item);
  }
  out << " ]";
  //if (endNewLine)
    //out << std::endl;
  return out.str();
}

/*----< Helper function to make title >------------------*/

void makeTitle(const std::string& title, char underlineChar = '=')
{
	std::cout << "\n " << std::string(16, underlineChar);
	std::cout << " " << title;
	std::cout << " " << std::string(16, underlineChar) << std::endl;
}

/*----< Helper function to make subtitle >------------------*/

void makeSubTitle(const std::string& subTitle, char underlineChar = '=') {
	std::cout << "\n  " << subTitle;
	std::cout << "\n " << std::string(subTitle.size() + 2, underlineChar);
}

/*----< Helper function to make comment for demo >------------------*/

void makeComment(const std::string& comment, char underlineChar = '-')
{
	std::cout << "\n " << std::string(8, underlineChar);
	std::cout << " " << comment;
	std::cout << " " << std::string(8, underlineChar) << std::endl;
}

/*----< Helper function to return current time in string >------------------*/

std::string getTime() {
	time_t t = time(nullptr);
	tm tm;
	localtime_s(&tm, &t);
	std::stringstream out;
	out << std::put_time(&tm, "%H:%M:%S %Y/%m/%d");
	return out.str();
}

/*----< Helper function to retrive time from string >------------------*/

time_t strToTime(std::string timeString) {
	struct tm tm;
	std::istringstream ss(timeString);
	ss >> std::get_time(&tm, "%H:%M:%S %Y/%m/%d");
	struct tm *tPtr = &tm;
	std::time_t time = mktime(tPtr);
	return time;
}
