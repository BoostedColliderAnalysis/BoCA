/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "multiplets/Octet.hh"

namespace boca {

const Sextet& Octet62::Sextet() const
{
    return Multiplet1();
}

Doublet const& Octet62::Doublet() const
{
    return Multiplet2();
}

// float Octet44::BottomBdt() const
// {
//   return (Quartet1().Singlet().UserInfo().Bdt() + Quartet1().Triplet().Singlet().UserInfo().Bdt() + Quartet2().Singlet().UserInfo().Bdt() + Quartet2().Triplet().Singlet().UserInfo().Bdt())/2;
// }

const Quartet31& Octet44::Quartet2() const
{
  return Multiplet2();
}

const Quartet31& Octet44::Quartet1() const
{
  return Multiplet1();
}

// float Octet44::PairBottomBdt() const
// {
//   return (Quartet2().Singlet().UserInfo().Bdt() + Quartet2().Triplet().Singlet().UserInfo().Bdt()) / 2;
// }

Quintet const& Octet53::Quintet() const
{
  return Multiplet1();
}

Triplet const& Octet53::Triplet() const
{
  return Multiplet2();
}

}
