#pragma once

#include <exception>

namespace boca
{

class Problematic : public std::exception
{
public:
    char const* what() const throw () {
        return "Problematic Multiplet";
    }
};

class Overlap : public std::exception
{
public:
    char const* what() const throw () {
        return "Overlap";
    }
};

class Empty : public std::exception
{
public:
    char const* what() const throw () {
        return "empty";
    }
};

class Isolation : public std::exception
{
public:
    char const* what() const throw () {
        return "not isolated";
    }
};

}
