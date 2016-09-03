/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boost/range/algorithm/sort.hpp"

#include "heavyhiggs/CutVariables.hh"

#include "boca/generic/DEBUG_MACROS.hh"

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
double CutVariables::BottomBdt() const
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
void CutVariables::SetInvariantMass(Mass const& invariant_mass)
{
    invariant_mass_ = invariant_mass;
}
void CutVariables::SetHt(Energy const& ht)
{
    ht_ = ht;
}
void CutVariables::SetEtMiss(Energy const& et_miss)
{
    et_miss_ = et_miss;
}
void CutVariables::SetBottomMinPt(Momentum const& bottom_min_pt)
{
    bottom_min_pt_ = bottom_min_pt;
}
void CutVariables::SetBottomMaxRap(Angle const& bottom_max_rap)
{
    bottom_max_rap_ = bottom_max_rap;
}
void CutVariables::SetLeptonPts(std::vector<Lepton> const& leptons)
{
  for (auto const & lepton : leptons) lepton_pts_.emplace_back(lepton.Pt());
  boost::range::sort(lepton_pts_, [](Momentum const & pt_1, Momentum const & pt_2) {
    return pt_1 > pt_2;
  });
}
Momentum CutVariables::LeptonPt(unsigned number) const
{
  return lepton_pts_.size() > number ? lepton_pts_.at(number) : at_rest;
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
void CutVariables::SetJetPts(std::vector<Jet> const& jets)
{
    for (auto const & jet : jets) jet_pts_.emplace_back(jet.Pt());
    boost::range::sort(jet_pts_, [](Momentum const & pt_1, Momentum const & pt_2) {
        return pt_1 > pt_2;
    });
}

Momentum CutVariables::JetPt(unsigned number) const
{
    return jet_pts_.size() > number ? jet_pts_.at(number) : at_rest;
}

}
