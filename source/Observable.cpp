/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Observable.hh"
#include "Debug.hh"

namespace boca {

Observable::Observable(float& value, std::string const& expression, std::string const& title, std::string const& unit) : value_(value)
{
    expression_ = expression;
    title_ = title;
    unit_ = unit;
    if (value == int(value)) type_ = 'I';
    else type_ = 'F';
    Debug(expression_, type_, value_, title_);
}

float& Observable::value() const
{
    return value_;
}

std::string Observable::expression() const
{
    return expression_;
}

std::string Observable::title() const
{
    return title_;
}

std::string Observable::unit() const
{
    return unit_;
}

char Observable::type() const
{
    return type_;
}

}
