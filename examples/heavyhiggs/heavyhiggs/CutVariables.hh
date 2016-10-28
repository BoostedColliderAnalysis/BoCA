/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/fastjet/Jet.hh"

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
    void SetInvariantMass(boca::Mass const& invariant_mass);
    void SetHt(const boca::Energy& ht);
    void SetEtMiss(const boca::Energy& et_miss);
    void SetBottomMinPt(Momentum const& bottom_min_pt);
    void SetBottomMaxRap(Angle const& bottom_max_rap);
    void SetLeptonPts(const std::vector< boca::Lepton >& leptons);
    int JetNumber() const;
    int BottomNumber() const;
    int Charge() const;
    double BottomBdt() const;
    Angle DeltaR() const;
    Mass InvariantMass() const;
    Momentum LeptonPt(unsigned number) const;
    Momentum BottomMinPt() const;
    Angle BottomMaxRap() const;
    Momentum Ht() const;
    Energy EtMiss() const;
    void SetPassed(std::vector<bool> const& passed);
    bool IsNaN();
    std::vector<bool> Passed() const;
    void SetJetPts(std::vector<Jet> const& jets);
    Momentum JetPt(unsigned number) const;

private:

    int jet_number_ = 0;
    int bottom_number_ = 0;
    Mass invariant_mass_ = 0;
    Energy ht_ = 0;
    Energy et_miss_ = 0;
    std::vector<Momentum> lepton_pts_;
    std::vector<Momentum> jet_pts_;
    Momentum bottom_min_pt_ = 0;
    Angle delta_r_ = 0;
    Angle bottom_max_rap_ = 0;
    std::vector<bool> passed_;
};

}
