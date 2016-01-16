/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Identification.hh"

namespace boca
{

enum class Stage
{
    trainer,
    reader
};

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
