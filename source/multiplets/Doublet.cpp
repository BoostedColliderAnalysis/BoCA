/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "multiplets/Doublet.hh"

namespace boca
{

Singlet const& Doublet::Singlet1() const
{
    return Multiplet1();
}

Singlet const& Doublet::Singlet2() const
{
    return Multiplet2();
}

}



