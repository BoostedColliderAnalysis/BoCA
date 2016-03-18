/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Names.hh"

namespace boca
{

class Observable
{

public:

    Observable(float& value, std::string const& name, std::string const& latex_name = "");

    float& Value() const;

    std::string Expression() const;

    std::string Name() const;

    std::string LatexName() const;

    std::string Unit() const;

    char Type() const;

    boca::Names const& Names() const;

    void SetBranchName(std::string const& branch_name);

    bool IsInt() const;

private:

    std::string branch_name_;

    boca::Names names_;

    float* value_;

};

}
