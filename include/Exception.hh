#pragma once

#include <exception>

namespace boca
{

class Problematic : public std::exception
{
public:
    char const* what() const throw ();
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
