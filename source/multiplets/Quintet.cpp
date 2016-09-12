/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Quintet.hh"

namespace boca
{

Triplet const& Quintet::Triplet() const
{
    return Multiplet1();
}

Doublet const& Quintet::Doublet() const
{
    return Multiplet2();
}

Triplet &Quintet::Triplet()
{
    return Multiplet1();
}

Doublet &Quintet::Doublet()
{
    return Multiplet2();
}

}
