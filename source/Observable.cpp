/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/Observable.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

Observable::Observable(float& value, std::string const& name, std::string const& latex_name) :
    value_(&value)
{
    names_.Set(name, latex_name);
    DEBUG(branch_name_, value_, names_.Name());
}

float& Observable::Value() const
{
    return *value_;
}

std::string Observable::Expression() const
{
    return branch_name_ + "." + Name();
}

std::string Observable::Name() const
{
    return names_.Name();
}

std::string Observable::Unit() const
{
    return "";
}

char Observable::Type() const
{
    return IsInt() ? 'I' : 'F';
}

std::string Observable::LatexName() const
{
    return names_.LatexName();
}

Names const& Observable::Names() const
{
    return names_;
}

void Observable::SetBranchName(std::string const& branch_name)
{
    branch_name_ = branch_name;
}

bool Observable::IsInt() const
{
    return Value() == int(Value());
}

}
