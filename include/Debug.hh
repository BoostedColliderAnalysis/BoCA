#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

namespace analysis{

#define NOTIFICATION

#define STRING(x) #x

std::string Shorten(const std::string &pretty_function, std::size_t brake);

std::string Shorten2(const std::string &pretty_function, std::size_t brake);

std::string NameSpaceName2(const std::string &pretty_function);

#define NAMESPACE_NAME NameSpaceName2(__PRETTY_FUNCTION__)

std::string ClassName2(const std::string &pretty_function);

#define CLASS_NAME ClassName2(__PRETTY_FUNCTION__)

std::string FunctionName(const std::string &pretty_function);

#define FUNCTION_NAME FunctionName(__PRETTY_FUNCTION__)

std::string FileName(const std::string &file);

#define FILE_NAME FileName(__FILE__)

template<typename Value>
std::string Column(const int width, const Value &message)
{
    std::stringstream ss;
    ss << std::left << std::setw(width) << std::setfill(' ') << message;
    return ss.str();
}

void LogBase(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function);

template<typename Value>
void Log(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function, const std::string &variable, const Value value)
{
    LogBase(file, line, NameSpace, Class, function);
    std::string str2(variable.size(), '0');
    str2.erase(std::remove_copy(variable.begin(), variable.end(), str2.begin(), '"'), str2.end());
    if (value == str2) std::cout << Column(10, value) << std::endl;
    else std::cout << Column(10, variable) << Column(10, value) << std::endl;
}

#define LOG(value) Log(FILE_NAME, __LINE__, NAMESPACE_NAME, CLASS_NAME, FUNCTION_NAME, STRING(value), value)

#define Error(value) LOG(value)
#define Check(condition, value) if(!(condition)) { Error(value); }

#ifdef NOTIFICATION
#define Note(value) LOG(value)
#define Info(value) do { if (0) LOG(value); } while (0)
#define Debug(value) do { if (0) LOG(value); } while (0)
#define Detail(value) do { if (0) LOG(value); } while (0)
#else
#ifdef INFORMATION
#define Note(value) LOG(value)
#define Info(value) LOG(value)
#define Debug(value) do { if (0) LOG(value); } while (0)
#define Detail(value) do { if (0) LOG(value); } while (0)
#else
#ifdef DEBUG
#define Note(value) LOG(value)
#define Info(value) LOG(value)
#define Debug(value) LOG(value)
#define Detail(value) do { if (0) LOG(value); } while (0)
#else
#ifdef DETAILED
#define Note(value) LOG(value)
#define Info(value) LOG(value)
#define Debug(value) LOG(value)
#define Detail(value) LOG(value)
#else
#endif
#endif
#endif
#endif

}
