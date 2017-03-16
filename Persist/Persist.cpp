/////////////////////////////////////////////////////////////////////
// Persist.cpp - Persist Operations for database                   //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Persist.h"

#ifdef TEST_PERSIST

using namespace NoSqlDatabase;

int main()
{	
	// Test to save string into file
	Persist persist;
	// Test to set out path
	persist.setOutPath("../XmlFiles/demo.xml");
	persist.save("Test demo");
	// Test to restore string from file
	Persist persist1;
	// Test to set in path
	persist1.setInPath("../XmlFiles/demo.xml");
	std::cout << persist1.restore();
}

#endif
