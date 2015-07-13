#include "Observable.hh"

namespace analysis
{

Observable::Observable(float &value, const std::string &expression, const std::string &title, const std::string &unit) : value_(value)
{
    expression_ = expression;
    title_ = title;
    unit_ = unit;
    if (value == int(value)) type_ = 'I';
    else type_ = 'F';
}

float &Observable::value() const
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
