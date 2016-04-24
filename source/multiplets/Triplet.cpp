/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Triplet.hh"

namespace boca
{

Doublet const& Triplet::Doublet() const
{
    return Multiplet1();
}

Doublet& Triplet::Doublet()
{
    return Multiplet1();
}

Singlet const& Triplet::Singlet() const
{
    return Multiplet2();
}

}
