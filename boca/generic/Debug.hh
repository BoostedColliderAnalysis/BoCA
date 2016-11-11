/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <boost/units/systems/si/io.hpp>

namespace boca
{

class Jet;
class Particle;

/**
 * @ingroup Generic
 * @defgroup Debug Debug
 * @brief Debugging and error reporting functions and macros
 * @{
 */

std::string NameSpaceName(std::string const& pretty_function);

std::string ClassName(std::string const& pretty_function);

std::string FunctionName(std::string const& pretty_function);

std::string FileName(std::string const& file);

template<typename Value>
std::string ApplyIoFlags(Value const& message) {
    std::stringstream stream;
    stream << std::boolalpha << boost::units::engineering_prefix << message;
    auto string = stream.str();
    if (!string.empty()) string.erase(std::remove_if(string.end() - 1, string.end(), [](char character) {
        return character == '_';
    }), string.end()); // remove trailing underscore
    auto dot = string.rfind('.');
    return string;
    return (dot == std::string::npos) ? string : string.substr(dot,string.length()); // remove potential class
}

template<typename Value>
std::string Stream(Value const& message, int width = 20,  bool right = false)
{
    std::stringstream stream;
    stream << (right ? std::right : std::left);
    stream << std::setw(width) << std::setfill(' ') << ApplyIoFlags(message);
    return stream.str();
}

template<typename Value>
std::string Stream2(std::string const& variable, Value const& value)
{
  return Stream(variable) + Stream(value);
}

void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, bool final = true);

template<typename Value>
void LogVariable(std::string const& variable, Value const& value)
{
    std::cout << Stream(variable) << Stream(value);
}

template<typename Value>
void LogVariable(std::string const& variable, const std::vector<Value>& values)
{
    LogVariable(variable, values.size());
}

void LogVariable(std::string const&, char const* value);

template<typename Value>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, Value value, bool final = true)
{
    Log(file, line, name_space, class_name, function, false);
    LogVariable(variable, value);
    if (final) std::cout << '\n';
}

template<typename Value, typename Value2>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, bool final = true)
{
    Log(file, line, name_space, class_name, function, variable, value, false);
    LogVariable(variable2, value2);
    if (final) std::cout << '\n';
}

template<typename Value, typename Value2, typename Value3>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, bool final = true)
{
    Log(file, line, name_space, class_name, function, variable, value, variable2, value2, false);
    LogVariable(variable3, value3);
    if (final) std::cout << '\n';
}

template<typename Value, typename Value2, typename Value3, typename Value4>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, std::string const& variable4, const Value4 value4, bool final = true)
{
    Log(file, line, name_space, class_name, function, variable, value, variable2, value2, variable3, value3, false);
    LogVariable(variable4, value4);
    if (final) std::cout << '\n';
}

template<typename Value, typename Value2, typename Value3, typename Value4, typename Value5>
void Log(std::string const& file, int line, std::string const& name_space, std::string const& class_name, std::string const& function, std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, std::string const& variable4, const Value4 value4, std::string const& variable5, const Value5 value5)
{
    Log(file, line, name_space, class_name, function, variable, value, variable2, value2, variable3, value3, variable4, value4, false);
    LogVariable(variable5, value5);
    std::cout << '\n';
}





void Debug(bool final = true);

template<typename Value>
void Debug(std::string const& variable, Value value, bool final = true)
{
    Debug(false);
    LogVariable(variable, value);
    if (final) std::cout << '\n';
}

template<typename Value, typename Value2>
void Debug(std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, bool final = true)
{
    Debug(variable, value, false);
    LogVariable(variable2, value2);
    if (final) std::cout << '\n';
}

template<typename Value, typename Value2, typename Value3>
void Debug(std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, bool final = true)
{
    Debug(variable, value, variable2, value2, false);
    LogVariable(variable3, value3);
    if (final) std::cout << '\n';
}

template<typename Value, typename Value2, typename Value3, typename Value4>
void Debug(std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, std::string const& variable4, const Value4 value4, bool final = true)
{
    Debug(variable, value, variable2, value2, variable3, value3, false);
    LogVariable(variable4, value4);
    if (final) std::cout << '\n';
}

template<typename Value, typename Value2, typename Value3, typename Value4, typename Value5>
void Debug(std::string const& variable, const Value value, std::string const& variable2, const Value2 value2, std::string const& variable3, const Value3 value3, std::string const& variable4, const Value4 value4, std::string const& variable5, const Value5 value5)
{
    Debug(variable, value, variable2, value2, variable3, value3, variable4, value4, false);
    LogVariable(variable5, value5);
    std::cout << '\n';
}

template<typename Value>
void Default(std::string const& variable, const Value value) {
    std::cout << "Defaul value for switch" << '\n';
    LogVariable(variable, value);
    std::cout << '\n';
}

void Error(std::string const& variable);

//@}

}
