/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Identification.hh"
#include "physics/Units.hh"

namespace boca
{

/**
 * @brief variables for cut based analysis
 *
 */
class CutVariables : public Identification
{

public:

    void SetJetNumber(int jet_number);
    void SetBottomNumber(int bottom_number);
    void SetInvariantMass(Mass invariant_mass);
    void SetHt(Energy ht);
    void SetEtMiss(Energy et_miss);
    void SetBottomMinPt(Momentum bottom_min_pt);
    void SetBottomMaxRap(Angle bottom_max_rap);
    void SetLeadingPt(Momentum leading_pt);
    void SetSecondLeadingPt(Momentum second_leading_pt);
    int JetNumber() const;
    int BottomNumber() const;
    int Charge() const;
    float BottomBdt() const;
    Angle DeltaR() const;
    Mass InvariantMass() const;
    Momentum LeadingPt() const;
    Momentum SecondLeadingPt() const;
    Momentum BottomMinPt() const;
    Angle BottomMaxRap() const;
    Momentum Ht() const;
    Energy EtMiss() const;
    void SetPassed(std::vector<bool> const& passed);
    bool IsNaN();
    std::vector<bool> Passed() const;

private:

    int jet_number_ = 0;
    int bottom_number_ = 0;
    Mass invariant_mass_ = 0;
    Energy ht_ = 0;
    Energy et_miss_ = 0;
    Momentum leading_pt_ = 0;
    Momentum second_leading_pt_ = 0;
    Momentum bottom_min_pt_ = 0;
    Angle delta_r_ = 0;
    Angle bottom_max_rap_ = 0;
    std::vector<bool> passed_;
};

}
