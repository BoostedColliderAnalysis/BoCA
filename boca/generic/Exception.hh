#pragma once

#include <stdexcept>
#include <string>

namespace boca
{

/**
 * @ingroup Generic
 * @defgroup Exceptions Exceptions
 * @brief Customized subclasses of std::exception or std::runtime_error
 * @{
 */

/**
* @brief Generic problematic cases
*/
class Problematic : public std::runtime_error
{
public:
    Problematic(std::string const &argument = __FILE__)  : std::runtime_error(argument)
    {
        arg_ = argument;
    };
    char const *what() const throw ();
    std::string arg_;
};

/**
* @brief %Overlap between structures
*/
class Overlap : public std::exception
{

public:

    char const *what() const throw ();

};

/**
* @brief %Empty multiplets
*/
class Empty : public std::exception
{
public:
    char const *what() const throw ();
};

/**
* @brief %Isolated objects
*/
class Isolated : public std::exception
{
public:
    char const *what() const throw ();
};

}

/*
 * @}
 */
