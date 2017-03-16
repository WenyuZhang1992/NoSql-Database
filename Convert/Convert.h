#pragma once
 /////////////////////////////////////////////////////////////////////
 // Convert.h - Demonstrate Template Syntax                         //
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
 * - Template classes use one or more unspecified types, defined by
 *   arguments in the template declaration: template<typename T, ...>.
 *
 * - Because the arguments are not specified, the C++ compiler cannot
 *   generate object code until it sees an application instantiate
 *   the template type(s).
 *
 * - The consequence of this is that all template definitions must be
 *   placed in a header file, to be included by the application.
 *
 * - Unlike C# and Java, template syntax checking happens when the
 *   application is compiled.  
 *
 * - That means that a template class can use any methods for the 
 *   unspecified type and will successfully compile.  If the type does
 *   not have a method used by the template code, a compile time error
 *   occurs when the application is compiled.
 * 
 * - This package contains one class Convert
 * - Convert: Provide methods to convert template value into or from 
 *   string
 *   - Provide method to create an id string from an instance of T 
 *   using RTTI
 *
 *  Public Interface
 * ==================
 *  Convert<T>::toString(const T& t)                   convert a template data into string
 *  fromString(const std::string& str)                 convert a string into template data
 *  id(const T& t)                                     create an id string for instance of T
 *  std::string fromString(const std::string& str)     template specialization for fromStr()
 *
 /////////////////////////////////////////////////////////////////////
 // Build Process                                                   //
 /////////////////////////////////////////////////////////////////////
 //  Required Files:                                                //
 //  - Convert.h, Convert.cpp                                       //
 //                                                                 //
 //  Build Process:                                                 //
 //    Set preprocessor definition TEST_CONVERT in properties.      //
 //    Set HashTable as the startup project.                        //
 //    Compile and run in Visual Studio.                            //
 //                                                                 //
 /////////////////////////////////////////////////////////////////////
 *
 *  Build Command
 * ===============
 *    devenv Convert.sln /rebuild debug
 *
 *  Maintenance History
 * =====================
 *  ver 1.0 : 07 Feb 17
 *  - first release
 *
 */
#include <sstream>
#include <string>

/////////////////////////////////////////////////////////////////////
// Convert<T> class
// - (de)serializes objects of type T (from)to strings
// - generates a type identifier using Run-Time Type Identification
//
template<typename T>
class Convert
{
public:
  virtual ~Convert<T>() {}
  static std::string toString(const T& t);
  static T fromString(const std::string& str);
  static std::string id(const T& t);
};

/*----< serialize t to a std::string >-----------------------------*/
/*
 * Assumes that T defines an insertion operator.
 */
template<typename T>
std::string Convert<T>::toString(const T& t)
{
  std::ostringstream out;
  out << *const_cast<T*>(&t);  
  return out.str();
}
/*----< create an instance of T from a std::string >---------------*/
/*
 * Assumes that T defines an extraction operator.
 * To succeed str must be created from Convert<T>::toString(const T& t). 
 */
template<typename T>
T Convert<T>::fromString(const std::string& str)
{
  std::istringstream in(str);
  T value;
  in >> value;    // istringstream extraction provides the conversion
  return value;
}

/*----< create an id string from an instance of T using RTTI >----*/

template<typename T>
std::string Convert<T>::id(const T& t)
{
  return typeid(t).name();
}

/*----< template specialization of fromString() method >-----------*/

template<>
std::string Convert<std::string>::fromString(const std::string& str)
{
	std::istringstream in(str);
	std::string value;
	std::getline(in, value);
	return value;
}


///////////////////////////////////////////////////////////////////////
//// TemplateDemo<T>
//// - demonstrates template syntax
////
//template<typename T>
//class TemplateDemo
//{
//public:
//  TemplateDemo() : state(T()) {}
//  TemplateDemo(const T& t) : state(t) {}
//  ~TemplateDemo() {}
//  T& value();
//private:
//  T state;
//};
///*----< return reference to internal state >-----------------------*/
//
//template<typename T>
//T& TemplateDemo<T>::value()
//{
//  return state;
//}
///*----< insertion operator >---------------------------------------*/
//
//template<typename T>
//std::ostream& operator<<(std::ostream& out, TemplateDemo<T>& td)
//{
//  out << td.value();
//  return out;
//}
///*----< extraction operator >--------------------------------------*/
//
//template<typename T>
//std::istream& operator>>(std::istream& in, TemplateDemo<T>& td)
//{
//  in >> td.value();
//  return in;
//}