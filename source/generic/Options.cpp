#include "TString.h"
#include "boca/generic/Options.hh"

namespace boca
{

Options::Options() {}

Options::Options(const std::string& string, bool do_it)
{
    Add(string, do_it);
}

void Options::Add(const std::string& string, bool do_it)
{
    Separator();
    if (!do_it) options_ << "!";
    options_ << string;
}

std::string Options::str() const
{
    return options_.str();
}

void Options::Separator()
{
    if (!first_) options_ << ":";
    first_ = false;
}

Options::operator TString() const
{
    return str();
}

Options::operator std::string() const
{
    return str();
}

}

