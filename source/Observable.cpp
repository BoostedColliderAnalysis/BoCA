/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Observable.hh"
#include "Debug.hh"

namespace boca
{

Observable::Observable(float& value, std::string const& expression, std::string const& title, std::string const& unit) :
    value_(&value)
{
    expression_ = expression;
    names_.SetName(title);
    unit_ = unit;
    if (value == int(value)) type_ = 'I';
    else type_ = 'F';
    Debug(expression_, type_, value_, names_.Name());
}

Observable::Observable(float& value, std::string const& name, std::string const& latex_name) :
    value_(&value)
{
    names_.SetName(name);
    if (latex_name.empty()) names_.SetLatexName(name);
    else names_.SetLatexName(latex_name);
    //     std::cout << value << " " << name << " " << nice_name << std::endl;
}

float& Observable::Value() const
{
    return *value_;
}

std::string Observable::Expression() const
{
    return expression_;
}

std::string Observable::Name() const
{
    return names_.Name();
}

std::string Observable::Unit() const
{
    return unit_;
}

char Observable::Type() const
{
    return type_;
}

std::string Observable::LatexName() const
{
    return names_.LatexName();
}

const Names& Observable::Names() const
{
    return names_;
}

}
