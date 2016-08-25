/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Sextet.hh"

namespace boca {

Triplet const& Sextet::Triplet1() const
{
    return Multiplet1();
}

Triplet const& Sextet::Triplet2() const
{
    return Multiplet2();
}

Triplet & Sextet::Triplet1()
{
  return Multiplet1();
}

Triplet & Sextet::Triplet2()
{
  return Multiplet2();
}

}
