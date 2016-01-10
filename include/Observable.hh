/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Names.hh"

namespace boca
{

class Observable
{

public:

    Observable(float& value, std::string const& expression, std::string const& title, std::string const& unit);

    Observable(float& value, std::string const& name, std::string const& latex_name = "");

    float& Value() const;

    std::string Expression() const;

    std::string Name() const;

    std::string LatexName() const;

    std::string Unit() const;

    char Type() const;

    boca::Names const& Names() const;

private:

    std::string expression_;

    std::string unit_;

    boca::Names names_;

    char type_;

    float* value_;

};

}
