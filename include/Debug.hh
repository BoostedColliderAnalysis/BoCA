#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "fastjet/PseudoJet.hh"

#define NOTIFICATION

#define FILE_NAME ::analysis::FileName(__FILE__)

#define NAMESPACE_NAME ::analysis::NameSpaceName(__PRETTY_FUNCTION__)

#define CLASS_NAME ::analysis::ClassName(__PRETTY_FUNCTION__)

#define FUNCTION_NAME ::analysis::FunctionName(__PRETTY_FUNCTION__)

#define NAMES FILE_NAME, __LINE__, NAMESPACE_NAME, CLASS_NAME, FUNCTION_NAME

#define LOG0 ::analysis::Log0(NAMES)

#define STRING(x) #x

#define PAIR2(value) STRING(value), value

#define LOG1(value) ::analysis::Log1(NAMES, PAIR2(value))

#define LOG2(value, value2) ::analysis::Log2(NAMES, PAIR2(value), PAIR2(value2))

#define LOG3(value, value2, value3) ::analysis::Log3(NAMES, PAIR2(value), PAIR2(value2), PAIR2(value3))

#define LOG4(value, value2, value3, value4) ::analysis::Log4(NAMES, PAIR2(value), PAIR2(value2), PAIR2(value3), PAIR2(value4))

#define LOG(arg1, arg2, arg3, arg4, arg5, ...) arg5

#define LOGCHOOSE(...) LOG(__VA_ARGS__, LOG4, LOG3, LOG2, LOG1, LOG0)

#define ALIVE(...) LOGCHOOSE(__VA_ARGS__)(__VA_ARGS__)

#define DEAD(...) do { if (0) ALIVE(__VA_ARGS__); } while (0)

#define Error(...) ALIVE(__VA_ARGS__)
#define Note(...) DEAD(__VA_ARGS__)
#define Info(...) DEAD(__VA_ARGS__)
#define Debug(...) DEAD(__VA_ARGS__)
#define Detail(...) DEAD(__VA_ARGS__)

#ifdef NOTIFICATION
#define Note(...) ALIVE(__VA_ARGS__)
#endif
#ifdef INFORMATION
#define Note(...) ALIVE(__VA_ARGS__)
#define Info(...) ALIVE(__VA_ARGS__)
#endif
#ifdef DEBUG
#define Note(...) ALIVE(__VA_ARGS__)
#define Info(...) ALIVE(__VA_ARGS__)
#define Debug(...) ALIVE(__VA_ARGS__)
#endif
#ifdef DETAILED
#define Note(...) ALIVE(__VA_ARGS__)
#define Info(...) ALIVE(__VA_ARGS__)
#define Debug(...) ALIVE(__VA_ARGS__)
#define Detail(...) ALIVE(__VA_ARGS__)
#endif

#define Check(condition, ...) if(!(condition)) { ALIVE(__VA_ARGS__); }

namespace analysis
{

std::string Shorten(const std::string &pretty_function, std::size_t brake);

std::string Shorten2(const std::string &pretty_function, std::size_t brake);

std::string NameSpaceName(const std::string &pretty_function);

std::string ClassName(const std::string &pretty_function);

std::string FunctionName(const std::string &pretty_function);

std::string FileName(const std::string &file);

template<typename Value>
std::string Column(const int width, const Value &message)
{
    std::stringstream ss;
    ss << std::left << std::setw(width) << std::setfill(' ') << message;
    return ss.str();
}

void Log0(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function, bool final = true);

template<typename Value>
void LogVariable(const std::string &variable, const Value value)
{
    std::string str2(variable.size(), '0');
    str2.erase(std::remove_copy(variable.begin(), variable.end(), str2.begin(), '"'), str2.end());
    if (value == str2) std::cout << Column(15, value);
    else std::cout << Column(15, variable) << Column(15, value);
}

void LogVariable(const std::string &variable, const fastjet::PseudoJet jet);

template<typename Value>
void Log1(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function, const std::string &variable, const Value value, bool final = true)
{
    Log0(file, line, NameSpace, Class, function, false);
    LogVariable(variable, value);
    if (final) std::cout << std::endl;
}

template<typename Value, typename Value2>
void Log2(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function, const std::string &variable, const Value value, const std::string &variable2, const Value2 value2, bool final = true)
{
    Log1(file, line, NameSpace, Class, function, variable, value, false);
    LogVariable(variable2, value2);
    if (final) std::cout << std::endl;
}

template<typename Value, typename Value2, typename Value3>
void Log3(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function, const std::string &variable, const Value value, const std::string &variable2, const Value2 value2, const std::string &variable3, const Value3 value3, bool final = true)
{
    Log2(file, line, NameSpace, Class, function, variable, value, variable2, value2, false);
    LogVariable(variable3, value3);
    if (final) std::cout << std::endl;
}

template<typename Value, typename Value2, typename Value3, typename Value4>
void Log4(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function, const std::string &variable, const Value value, const std::string &variable2, const Value2 value2, const std::string &variable3, const Value3 value3, const std::string &variable4, const Value4 value4)
{
    Log3(file, line, NameSpace, Class, function, variable, value, variable2, value2, variable3, value3, false);
    LogVariable(variable4, value4);
    std::cout << std::endl;
}


}
