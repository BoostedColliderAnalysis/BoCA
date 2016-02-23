/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "multiplets/Quintet.hh"

namespace boca {

  Triplet const& Quintet::Triplet() const
{
    return Multiplet1();
}

Doublet const& Quintet::Doublet() const
{
    return Multiplet2();
}

}
