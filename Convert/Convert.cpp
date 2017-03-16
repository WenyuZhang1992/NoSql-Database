/////////////////////////////////////////////////////////////////////
// Convert.cpp - Demonstrate Template Syntax                       //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #1         //
// Language:    C++, Visual Studio 2015                            //
// Platform:    Win 8.1, Visual Studio 2015                        //
// Author:      WENYU ZHANG, 233508014                             //
//              wzhan102@syr.edu                                   //
// Reference:   Jim Fawcett, CST 4-187, Syracuse University        //
//              jfawcett@twcny.rr.com, (315) 443-3948              //
/////////////////////////////////////////////////////////////////////

#include "Convert.h"
#include <string>
#include <iostream>
#include <functional>

//----< test stub >-------------------------------------------------------------------

#ifdef TEST_CONVERT

/////////////////////////////////////////////////////////////////////
// Widget class - shows user defined types can be template arguments

class Widget
{
public:
  Widget(const std::string& str = "") : state(str) {}
  std::string& value() { return state; }
private:
  std::string state;
};

std::ostream& operator<<(std::ostream& out, Widget& widget)
{
  out << widget.value();
  return out;
}

std::istream& operator >> (std::istream& in, Widget& widget)
{
  std::string temp;
  while (in.good())  // extract all the words from widget's string state
  {
    in >> temp;
    widget.value() += temp + " ";
  }
  return in;
}

/////////////////////////////////////////////////////////////////////
// lambdas that provide mildly useful local processing

std::function<void()> putLine = []() { std::wcout << "\n"; };

std::function<void(size_t)> putLines = [](size_t n) {
  for (size_t i = 0; i < n; ++i)
    putLine();
};

std::function<void(const std::string&, char)> titleCore = [](const std::string& msg, char underline='-') {
  std::cout << "\n  " << msg.c_str();
  std::wcout << "\n " << std::string(msg.size() + 2, underline).c_str();
};

std::function<void(const std::string&)> Title = [](const std::string& msg) { titleCore(msg, '='); };

std::function<void(const std::string&)> title = [](const std::string& msg) { titleCore(msg, '-'); };

/////////////////////////////////////////////////////////////////////
// Demo code

int main()
{
  Title("Demonstrating Templates");
  putLine();

  title("Demonstrating Conversion of numerical types");
  std::cout << "\n  conversion of integer: " << Convert<int>::toString(42);
  std::cout << "\n  conversion of double:  " << Convert<double>::toString(3.1415927);
  putLine();

  title("Demonstrating Conversion of Widget type");
  Widget widget("Joe Widget");
  std::string widgetStore = Convert<Widget>::toString(widget);
  std::cout << "\n  conversion of Widget: " << widgetStore;

  Widget newWidget = Convert<Widget>::fromString(widgetStore);
  std::cout << "\n  newWidget state = " << newWidget.value();

  putLines(2);
}
#endif TEST_CONVERT