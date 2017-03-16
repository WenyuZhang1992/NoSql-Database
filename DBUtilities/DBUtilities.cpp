/////////////////////////////////////////////////////////////////////
// DBUtilities.cpp - Generally useful helper functions             //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
// Reference:   Jim Fawcett, CST 4-187, Syracuse University        //
//              jfawcett@twcny.rr.com, (315) 443-3948              //
/////////////////////////////////////////////////////////////////////

#include "DBUtilities.h"
#include <iostream>
#include <string>

#ifdef TEST_UTILITIES

int main()
{
  std::cout << title("Demonstrating Utiltites", '=', true);
  std::string str = "this is a string";
  std::cout << title("Demonstrating show horizontal");
  std::cout << show(str);
  std::cout << title("Demonstrating show vertical");
  std::cout << show(str, true, vertical);
  std::cout << title("Demonstrating parenWrap");
  std::cout << "\n  " << parenWrap(str);

  std::cout << "\n\n";
}

#endif // TEST_UTILITIES