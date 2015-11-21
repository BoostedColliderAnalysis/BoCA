/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Doublet.hh"

#include "Math.hh"
#include "Debug.hh"

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



