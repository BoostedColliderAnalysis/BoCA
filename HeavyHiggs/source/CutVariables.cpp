/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "CutVariables.hh"
#include "Debug.hh"

namespace boca
{

void CutVariables::SetPassed(std::vector<bool> const& passed)
{
    passed_ = passed;
}
Momentum CutVariables::Ht() const
{
    return ht_;
}
Energy CutVariables::EtMiss() const
{
    return et_miss_;
}
int CutVariables::JetNumber() const
{
    return jet_number_;
}
int CutVariables::BottomNumber() const
{
    return bottom_number_;
}
Mass CutVariables::InvariantMass() const
{
    return invariant_mass_;
}
Angle CutVariables::DeltaR() const
{
    return delta_r_;
}
int CutVariables::Charge() const
{
    return 0;
}
float CutVariables::BottomBdt() const
{
    return 0;
}
bool CutVariables::IsNaN()
{
    return (Ht() != Ht() || EtMiss() != EtMiss() || JetNumber() != JetNumber() || BottomNumber() != BottomNumber() || InvariantMass() != InvariantMass() || DeltaR() != DeltaR());
}
void CutVariables::SetJetNumber(int jet_number)
{
    jet_number_ = jet_number;
}
void CutVariables::SetBottomNumber(int bottom_number)
{
    bottom_number_ = bottom_number;
}
void CutVariables::SetInvariantMass(Mass invariant_mass)
{
    invariant_mass_ = invariant_mass;
}
void CutVariables::SetHt(Energy ht)
{
    ht_ = ht;
}
void CutVariables::SetEtMiss(Energy et_miss)
{
    et_miss_ = et_miss;
}
void CutVariables::SetBottomMinPt(Momentum bottom_min_pt)
{
    bottom_min_pt_ = bottom_min_pt;
}
void CutVariables::SetBottomMaxRap(Angle bottom_max_rap)
{
    bottom_max_rap_ = bottom_max_rap;
}
void CutVariables::SetLeadingPt(Momentum leading_pt)
{
    leading_pt_ = leading_pt;
}
void CutVariables::SetSecondLeadingPt(Momentum second_leading_pt)
{
    second_leading_pt_ = second_leading_pt;
}
Momentum CutVariables::LeadingPt() const
{
    return leading_pt_;
}
Momentum CutVariables::SecondLeadingPt() const
{
    return second_leading_pt_;
}
Momentum CutVariables::BottomMinPt() const
{
    return bottom_min_pt_;
}
Angle CutVariables::BottomMaxRap() const
{
    return bottom_max_rap_;
}
std::vector< bool > CutVariables::Passed() const
{
    return passed_;
}

}
