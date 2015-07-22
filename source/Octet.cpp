#include "Octet.hh"

namespace analysis {

Sextet& Octet62::Sextet() const
{
    return Multiplet1();
}

Doublet& Octet62::Doublet() const
{
    return Multiplet2();
}

float Octet44::BottomBdt() const
{
  return (Quartet1().Singlet().UserInfo().Bdt() + Quartet1().Triplet().Singlet().UserInfo().Bdt() + Quartet2().Singlet().UserInfo().Bdt() + Quartet2().Triplet().Singlet().UserInfo().Bdt())/2;
}

Quartet31 Octet44::Quartet2() const
{
  return Multiplet2();
}

Quartet31 Octet44::Quartet1() const
{
  return Multiplet1();
}

float Octet44::PairBottomBdt() const
{
  return (Quartet2().Singlet().UserInfo().Bdt() + Quartet2().Triplet().Singlet().UserInfo().Bdt()) / 2;
}

Quintet& Octet53::Quintet() const
{
  return Multiplet1();
}

Triplet& Octet53::Triplet() const
{
  return Multiplet2();
}

}
