/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Names.hh"

namespace boca
{

class Observable
{

public:

    Observable(float& value, std::string const& name, latex::String const& latex_name = latex::String());

    float& Value() const;

    std::string Expression() const;

    std::string Name() const;

    latex::String LatexName() const;

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
