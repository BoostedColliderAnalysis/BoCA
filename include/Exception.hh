#pragma once

// #include <exception>
#include <stdexcept>

namespace boca
{

class Problematic : public std::runtime_error
{
public:
  Problematic(std::string const& argument = __FILE__)  : std::runtime_error(argument) {
        arg_ = argument;
    };
    char const* what() const throw ();
    std::string arg_;
};

class Overlap : public std::exception
{
public:
    char const* what() const throw ();
};

class Empty : public std::exception
{
public:
    char const* what() const throw ();
};

class Isolation : public std::exception
{
public:
    char const* what() const throw ();
};

}
