/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Tag.hh"
#include "boca/multivariant/Stage.hh"

namespace boca
{

class Phase
{
public:
    Phase(boca::Stage stage, boca::Tag tag);
    boca::Stage Stage() const;
    boca::Tag Tag() const;
private:
    boca::Stage stage_;
    boca::Tag tag_;
};

}
