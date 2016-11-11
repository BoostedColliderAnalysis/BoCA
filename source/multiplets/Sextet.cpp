/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Sextet.hh"

namespace boca {

Triplet const& Sextet33::Triplet1() const
{
    return Multiplet1();
}

Triplet const& Sextet33::Triplet2() const
{
    return Multiplet2();
}

Triplet & Sextet33::Triplet1()
{
  return Multiplet1();
}

Triplet & Sextet33::Triplet2()
{
  return Multiplet2();
}

Quartet22 const& Sextet42::Quartet() const
{
    return Multiplet1();
}

boca::Doublet const& Sextet42::Doublet() const
{
    return Multiplet2();
}

Quartet22 & Sextet42::Quartet()
{
  return Multiplet1();
}

boca::Doublet & Sextet42::Doublet()
{
  return Multiplet2();
}


std::string Sextet33::Name() const
{
    return "Sextet33";
}


std::string Sextet42::Name() const
{
    return "Sextet42";
}

}
