/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Octet.hh"

namespace boca {

const Sextet& Octet62::Sextet() const
{
    return Multiplet1();
}

Doublet const& Octet62::Doublet() const
{
    return Multiplet2();
}

const Quartet31& Octet44::Quartet1() const
{
  return Multiplet1();
}

const Quartet31& Octet44::Quartet2() const
{
  return Multiplet2();
}

Quintet const& Octet53::Quintet() const
{
  return Multiplet1();
}

Triplet const& Octet53::Triplet() const
{
  return Multiplet2();
}

const Triplet& Octet332::Triplet1() const
{
    return Multiplet1();
}

const Triplet& Octet332::Triplet2() const
{
    return Multiplet2();
}

const Doublet& Octet332::Doublet() const
{
    return Multiplet3();
}

}
