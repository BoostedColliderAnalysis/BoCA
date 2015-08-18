/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Sextet.hh"

namespace boca {

Triplet const& Sextet::Triplet1() const
{
    return Multiplet1();
}

Triplet const& Sextet::Triplet2() const
{
    return Multiplet2();
}

}
