/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Observable.hh"
#include "Debug.hh"

namespace boca {

Observable::Observable(float& value, std::string const& expression, std::string const& title, std::string const& unit) : value_(&value)
{
    expression_ = expression;
    title_ = title;
    unit_ = unit;
    if (value == int(value)) type_ = 'I';
    else type_ = 'F';
    Debug(expression_, type_, value_, title_);
}

float &Observable::Value() const
{
    return *value_;
}

std::string Observable::Expression() const
{
    return expression_;
}

std::string Observable::Title() const
{
    return title_;
}

std::string Observable::Unit() const
{
    return unit_;
}

char Observable::Type() const
{
    return type_;
}

}
