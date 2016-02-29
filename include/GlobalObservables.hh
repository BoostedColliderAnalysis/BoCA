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

    void SetEvent(Event const& event, std::vector<Jet> const& jets);

    void SetEvent(Event const& event);

    int LeptonNumber() const;

    int JetNumber() const;

    int BottomNumber() const;

    float BottomBdt() const;

    float BottomBdt(int number) const;

    float BottomBdt(int number_1, int number_2) const;

    Momentum ScalarHt() const;

    Momentum LeptonHt() const;

    Momentum JetHt() const;

    Momentum JetPt(int number) const;

    Momentum LeptonPt(int number) const;

    Energy MissingEt() const;

    boca::Singlet Singlet() const;

    std::vector<Jet> Jets() const;

    void SetJets(std::vector<Jet> const& jets);

    void SetLeptons(std::vector<Lepton> const& leptons);

private:

    std::vector<Jet> jets_;

    std::vector<Lepton> leptons_;

    Momentum scalar_ht_;

    Energy missing_et_;

};

}
