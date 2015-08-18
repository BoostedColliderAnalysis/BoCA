#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace fastjet {
class PseudoJet;
}

// FIXME do we really want to write non standard compliant code?
// #pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
// #pragma GCC diagnostic ignored "-Wmacro-redefined"
// #pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
// #pragma clang diagnostic ignored "-Wmacro-redefined"

// defined by cmake for debug runs
#ifndef NDEBUG
#define NOTIFICATION
#endif

namespace analysis {

std::string Shorten(std::string const& pretty_function, size_t brake);

std::string Shorten2(std::string const& pretty_function, size_t brake);

std::string NameSpaceName(std::string const& pretty_function);

std::string ClassName(std::string const& pretty_function);

std::string FunctionName(std::string const& pretty_function);

std::string FileName(std::string const& file);

template<typename Value>
std::string Column(int width, const Value& message)
{
    std::stringstream stream;
    stream << std::left << std::setw(width) << std::setfill(' ') << message;
    return stream.str();
}

template<typename Value>
std::string ColumnRight(int width, const Value& message)
{
    std::stringstream stream;
    stream << std::right << std::setw(width) << std::setfill(' ') << message;
    return stream.str();
}

int ValueLength();

void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, bool final = true);

template<typename Value>
void LogVariable(std::string const& variable, const Value& value)
{
    std::cout << Column(ValueLength(), variable) << Column(ValueLength(), value);
}

template<typename Value>
void LogVariable(std::string const& variable, const std::vector<Value>& values)
{
//     for (auto const& value : values) LogVariable(variable, values);
        LogVariable(variable, values.size());
}

void LogVariable(const std::string&, char const* value);

void LogVariable(std::string const& variable, fastjet::PseudoJet const& jet);

template<typename Value>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable = "", const Value value = 0, bool final = true)
{
    Log(file, line, name_space, class_name, function, false);
    LogVariable(variable, value);
    if (final) std::cout << std::endl;
}

template<typename Value, typename Value2>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, bool final = true)
{
    Log(file, line, name_space, class_name, function, variable, value, false);
    LogVariable(variable2, value2);
    if (final)
        std::cout << std::endl;
}

template<typename Value, typename Value2, typename Value3>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, bool final = true)
{
    Log(file, line, name_space, class_name, function, variable, value, variable2, value2, false);
    LogVariable(variable3, value3);
    if (final)
        std::cout << std::endl;
}

template<typename Value, typename Value2, typename Value3, typename Value4>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, std::string const& variable4, const Value4 value4)
{
    Log(file, line, name_space, class_name, function, variable, value, variable2, value2, variable3, value3, false);
    LogVariable(variable4, value4);
    std::cout << std::endl;
}

}

#define FILE_NAME ::analysis::FileName(__FILE__)

#define NAMESPACE_NAME ::analysis::NameSpaceName(__PRETTY_FUNCTION__)

#define CLASS_NAME ::analysis::ClassName(__PRETTY_FUNCTION__)

#define FUNCTION_NAME ::analysis::FunctionName(__PRETTY_FUNCTION__)

#define NAMES FILE_NAME, __LINE__, NAMESPACE_NAME, CLASS_NAME, FUNCTION_NAME

#define VARIABLE(value) #value, value

#define LOG0() ::analysis::Log(NAMES)

#define LOG1(value) ::analysis::Log(NAMES, VARIABLE(value))

#define LOG2(value, value2) ::analysis::Log(NAMES, VARIABLE(value), VARIABLE(value2))

#define LOG3(value, value2, value3) ::analysis::Log(NAMES, VARIABLE(value), VARIABLE(value2), VARIABLE(value3))

#define LOG4(value, value2, value3, value4) ::analysis::Log(NAMES, VARIABLE(value), VARIABLE(value2), VARIABLE(value3), VARIABLE(value4))

#define LOG(arg0, arg1, arg2, arg3, arg4, arg, ...) arg

#define LOGCHOOSE(...) LOG(,##__VA_ARGS__, LOG4, LOG3, LOG2, LOG1, LOG0)

#define ALIVE(...) LOGCHOOSE(__VA_ARGS__)(__VA_ARGS__)

#define DEAD(...) do { if (0) ALIVE(__VA_ARGS__); } while (0)

#define Error(...) ALIVE(__VA_ARGS__)

#ifdef NDEBUG
#define Note(...) DEAD(__VA_ARGS__)
#define Info(...) DEAD(__VA_ARGS__)
#define Debug(...) DEAD(__VA_ARGS__)
#define Detail(...) DEAD(__VA_ARGS__)
#endif

#ifdef NOTIFICATION
#define Note(...) ALIVE(__VA_ARGS__)
#define Info(...) DEAD(__VA_ARGS__)
#define Debug(...) DEAD(__VA_ARGS__)
#define Detail(...) DEAD(__VA_ARGS__)
#endif

#ifdef INFORMATION
#define Note(...) ALIVE(__VA_ARGS__)
#define Info(...) ALIVE(__VA_ARGS__)
#define Debug(...) DEAD(__VA_ARGS__)
#define Detail(...) DEAD(__VA_ARGS__)
#endif

#ifdef DEBUG
#define Note(...) ALIVE(__VA_ARGS__)
#define Info(...) ALIVE(__VA_ARGS__)
#define Debug(...) ALIVE(__VA_ARGS__)
#define Detail(...) DEAD(__VA_ARGS__)
#endif

#ifdef DETAILED
#define Note(...) ALIVE(__VA_ARGS__)
#define Info(...) ALIVE(__VA_ARGS__)
#define Debug(...) ALIVE(__VA_ARGS__)
#define Detail(...) ALIVE(__VA_ARGS__)
#endif

#define Check(condition, ...) if(!(condition)) { Error(__VA_ARGS__); }
// #define DebugCheck(condition, ...) if(!(condition)) { Debug(__VA_ARGS__); }
