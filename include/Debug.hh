/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <boost/units/systems/si/io.hpp>

// defined by cmake for debug runs
#ifndef NDEBUG
#define NOTIFICATION
#endif
// #define DEBUGGING
// #define INFORMATION
// #define NOTIFICATION

namespace boca
{

class Jet;
class Particle;

std::string Shorten(std::string const& pretty_function, size_t brake);

std::string Shorten2(std::string const& pretty_function, size_t brake);

std::string NameSpaceName(std::string const& pretty_function);

std::string ClassName(std::string const& pretty_function);

std::string FunctionName(std::string const& pretty_function);

std::string FileName(std::string const& file);

template<typename Value>
std::string Column(int width, Value const& message)
{
    std::stringstream stream_1;
    stream_1 << std::boolalpha << boost::units::engineering_prefix << message;
    std::stringstream stream_2;
    stream_2 << std::left << std::setw(width) << std::setfill(' ') << stream_1.str();
    return stream_2.str();
}

template<typename Value>
std::string ColumnRight(int width, Value const& message)
{
    std::stringstream stream_1;
    stream_1 << std::boolalpha << boost::units::engineering_prefix << message;
    std::stringstream stream_2;
    stream_2 << std::right << std::setw(width) << std::setfill(' ') << stream_1.str();
    return stream_2.str();
}

int ValueLength();

void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, bool final = true);

template<typename Value>
void LogVariable(std::string const& variable, Value const& value)
{
    std::cout << Column(ValueLength(), variable) << Column(ValueLength(), value);
}

template<typename Value>
void LogVariable(std::string const& variable, const std::vector<Value>& values)
{
//     for (auto const& value : values) LogVariable(variable, values);
    LogVariable(variable, values.size());
}

void LogVariable(std::string const&, char const* value);

void LogVariable(std::string const& variable, Jet const& jet);

void LogVariable(std::string const& variable, Particle const& jet);

// template<typename Value>
// void LogVariable(std::string const& variable, Bound<Value> const& bound){
//   LogVariable(variable, bound.Min());
//   LogVariable(variable, bound.Max());
// }
//
// template<typename Value>
// void LogVariable(std::string const& variable, Rectangle<Value> const& bound){
//   LogVariable(variable, bound.Horizontal());
//   LogVariable(variable, bound.Vertical());
// }

template<typename Value>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, Value value, bool final = true)
{
    Log(file, line, name_space, class_name, function, false);
    LogVariable(variable, value);
    if (final) std::cout << "\n";
}

template<typename Value, typename Value2>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, bool final = true)
{
    Log(file, line, name_space, class_name, function, variable, value, false);
    LogVariable(variable2, value2);
    if (final) std::cout << "\n";
}

template<typename Value, typename Value2, typename Value3>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, bool final = true)
{
    Log(file, line, name_space, class_name, function, variable, value, variable2, value2, false);
    LogVariable(variable3, value3);
    if (final) std::cout << "\n";
}

template<typename Value, typename Value2, typename Value3, typename Value4>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, std::string const& variable4, const Value4 value4, bool final = true)
{
    Log(file, line, name_space, class_name, function, variable, value, variable2, value2, variable3, value3, false);
    LogVariable(variable4, value4);
    if (final) std::cout << "\n";
}

template<typename Value, typename Value2, typename Value3, typename Value4, typename Value5>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, std::string const& variable4, const Value4 value4, std::string const& variable5, const Value5 value5)
{
    Log(file, line, name_space, class_name, function, variable, value, variable2, value2, variable3, value3, variable4, value4, false);
    LogVariable(variable5, value5);
    std::cout << "\n";
}

}

#define FILE_NAME ::boca::FileName(__FILE__)

#define NAMESPACE_NAME ::boca::NameSpaceName(__PRETTY_FUNCTION__)

#define CLASS_NAME ::boca::ClassName(__PRETTY_FUNCTION__)

#define FUNCTION_NAME ::boca::FunctionName(__PRETTY_FUNCTION__)

#define NAMES FILE_NAME, __LINE__, NAMESPACE_NAME, CLASS_NAME, FUNCTION_NAME

#define VARIABLE(value) #value, value

#define LOG0 ::boca::Log(NAMES)

#define LOG1(value) ::boca::Log(NAMES, VARIABLE(value))

#define LOG2(value, value2) ::boca::Log(NAMES, VARIABLE(value), VARIABLE(value2))

#define LOG3(value, value2, value3) ::boca::Log(NAMES, VARIABLE(value), VARIABLE(value2), VARIABLE(value3))

#define LOG4(value, value2, value3, value4) ::boca::Log(NAMES, VARIABLE(value), VARIABLE(value2), VARIABLE(value3), VARIABLE(value4))

#define LOG5(value, value2, value3, value4, value5) ::boca::Log(NAMES, VARIABLE(value), VARIABLE(value2), VARIABLE(value3), VARIABLE(value4), VARIABLE(value5))

#define LOG(arg0, arg1, arg2, arg3, arg4, arg5, arg, ...) arg

// #define LOGCHOOSE(...) LOG(,##__VA_ARGS__, LOG4, LOG3, LOG2, LOG1, LOG0)
#define LOGCHOOSE(...) LOG(__VA_ARGS__, , LOG5, LOG4, LOG3, LOG2, LOG1, )

#define ALIVE(...) LOGCHOOSE(__VA_ARGS__)(__VA_ARGS__)

#define DEAD(...) do { if (0) ALIVE(__VA_ARGS__); } while (0)

#define DEAD0 do { if (0) LOG0; } while (0)

#define ERROR(...) ALIVE(__VA_ARGS__)
#define ERROR0 LOG0

#if defined(DETAILED)
#define DETAIL(...) ALIVE(__VA_ARGS__)
#define DETAIL0 LOG0
#else
#define DETAIL(...) DEAD(__VA_ARGS__)
#define DETAIL0 DEAD0
#endif

#if defined(DETAILED) || defined(DEBUGGING)
#define DEBUG(...) ALIVE(__VA_ARGS__)
#define DEBUG0 LOG0
#else
#define DEBUG(...) DEAD(__VA_ARGS__)
#define DEBUG0 DEAD0
#endif

#if defined(DETAILED) || defined(DEBUGGING) || defined(INFORMATION)
#define INFO(...) ALIVE(__VA_ARGS__)
#define INFO0 LOG0
#else
#define INFO(...) DEAD(__VA_ARGS__)
#define INFO0 DEAD0
#endif

#if defined(DETAILED) || defined(DEBUGGING) || defined(INFORMATION) || defined(NOTIFICATION)
#define NOTE(...) ALIVE(__VA_ARGS__)
#define NOTE0 LOG0
#else
#define NOTE(...) DEAD(__VA_ARGS__)
#define NOTE0 DEAD0
#endif

#define CHECK(condition, ...) if(!(condition)) { ERROR(__VA_ARGS__); }
#define DEBUG_CHECK(condition, ...) if(!(condition)) { DEBUG(__VA_ARGS__); }

#define DEFAULT_1(condition) default : ERROR("Switch Default", condition); break;
#define DEFAULT_2(condition, value) default : ERROR("Switch Default", condition); return value;

#define DEFAULT_ARGUMENTS(arg1, arg2, arg, ...) arg
#define DEFAULT_CHOOSE(...) DEFAULT_ARGUMENTS(__VA_ARGS__, DEFAULT_2, DEFAULT_1, )

#define DEFAULT(...) DEFAULT_CHOOSE(__VA_ARGS__)(__VA_ARGS__)

// #include "Logging.hh"

// #define HAS_ARGS_IMPL2(_1, _2, _3, N, ...) N
// #define HAS_ARGS_SOURCE() MULTI, MULTI, ONE, ERROR
//
// #define HAS_ARGS_IMPL(...) HAS_ARGS_IMPL2(__VA_ARGS__)
// #define HAS_ARGS(...) HAS_ARGS_IMPL(__VA_ARGS__, HAS_ARGS_SOURCE())
//
// #define MACRO_ONE(x) ONE_ARG: x
// #define MACRO_MULTI(...) MULTI_ARG: __VA_ARGS__
//
// #define DISAMBIGUATE2(args, ...) MACRO_ ## args (__VA_ARGS__)
// #define DISAMBIGUATE(args, ...) DISAMBIGUATE2(args, __VA_ARGS__)
// #define ERROR(...) DISAMBIGUATE(HAS_ARGS(__VA_ARGS__), __VA_ARGS__)
