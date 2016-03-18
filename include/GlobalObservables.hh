/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Singlet.hh"

namespace boca
{

class Event;

class GlobalObservables : public Identification
{

public:

    GlobalObservables();

    GlobalObservables(Event const& event);

    GlobalObservables(Event const& event, std::vector<boca::Jet> const& jets);

    void SetEvent(Event const& event, std::vector<boca::Jet> const& jets);

    void SetEvent(Event const& event);

    int LeptonNumber() const;

    int JetNumber() const;

    int BottomNumber() const;

    double BottomBdt() const;

    double BottomBdt(int number) const;

    double BottomBdt(int number_1, int number_2) const;

    Momentum ScalarHt() const;

    Momentum LeptonHt() const;

    Momentum JetHt() const;

    Momentum Ht() const;

    boca::Mass Mass() const;

    Angle DeltaRTo(boca::PseudoJet const& jet) const;

    int Charge() const;

    Momentum JetPt(int number) const;

    Momentum LeptonPt(int number) const;

    Energy MissingEt() const;

    boca::Singlet Singlet() const;

    std::vector<boca::Jet> Jets() const;

    void SetJets(std::vector<boca::Jet> const& jets);

    void SetLeptons(std::vector<Lepton> const& leptons);

    boca::Singlet const& ConstituentJet() const;

    boca::Jet Jet() const;

private:

    std::vector<boca::Jet> jets_;

    std::vector<Lepton> leptons_;

    Momentum scalar_ht_;

    Energy missing_et_;

    mutable boca::Singlet singlet_;

    mutable bool has_constituent_jet_ = false;

};

}
