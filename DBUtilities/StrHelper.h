#pragma once
 /////////////////////////////////////////////////////////////////////
 // StrHelper.h - Helper functions to trim string                   //
 //                                                                 //
 // Application: CSE687 - Object Oriented Design Project #1         //
 // Language:    C++, Visual Studio 2015                            //
 // Platform:    Win 8.1, Visual Studio 2015                        //
 // Author:      WENYU ZHANG, 233508014                             //
 //              wzhan102@syr.edu                                   //
 // Reference:   Jim Fawcett, CST 4-187, Syracuse University        //
 //              jfawcett@twcny.rr.com, (315) 443-3948              //
 // Source:      Evan Teran                                         //
 /////////////////////////////////////////////////////////////////////
 /*
 *  Package Operations
 * ====================
 * Source from consultation with Dr. Google: 
 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 *
 * Note:
 * - isspace(char), used below, fails with exception on certain non-ascii 
 *   characters. For example, some of the Chinese characters will do that.
 * - To fix need to use isspace(char, std::locale). You can't directly
 *   do that with the code below, due to the way it's using std algorithms,
 *   but it's not too hard to do.
 * - For our purposes this should not cause a problem.
 *
 *  Public Interface
 * ==================
 *  std::string &ltrim(std::string &s)          trim a string from start
 *  std::string &rtrim(std::string &s)          trim a string from end
 *  std::string &trim(std::string &s)           trim a string from both ends
 *
 /////////////////////////////////////////////////////////////////////
 // Build Process                                                   //
 /////////////////////////////////////////////////////////////////////
 //  Required Files:                                                //
 //  - StrHelper.h, DBUtilities.cpp                                 //
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
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>

// trim from start
static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
    std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
    std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
  try { return ltrim(rtrim(s)); }
  catch (...) { return std::move(std::string("trimming error")); }
}
