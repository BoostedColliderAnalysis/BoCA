#include "Octet44.hh"

namespace analysis
{

namespace heavyhiggs
{

float Octet44::BottomBdt() const
{
    return Quartet1().Singlet().UserInfo().Bdt() + Quartet1().Triplet().Singlet().UserInfo().Bdt() + Quartet2().Singlet().UserInfo().Bdt() + Quartet2().Triplet().Singlet().UserInfo().Bdt();
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
    return Quartet2().Singlet().UserInfo().Bdt() + Quartet2().Triplet().Singlet().UserInfo().Bdt();
}

}

}
