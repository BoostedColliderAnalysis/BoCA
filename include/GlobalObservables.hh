/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Singlet.hh"

namespace boca {

class Event;

class GlobalObservables {

public:

    void SetEvent(Event const& event, std::vector<Jet> const& jets);

    void SetEvent(Event const& event);

    int LeptonNumber() const;

    int JetNumber() const;

    int BottomNumber() const;

    float BottomBdt() const;

    float BottomBdt(int number) const;

    float BottomBdt(int number_1, int number_2) const;

    float ScalarHt() const;

    float LeptonHt() const;

    float JetHt() const;

    float MissingEt() const;

    boca::Singlet Singlet() const;

    std::vector<Jet> Jets() const;

    void SetJets(const std::vector<Jet> jets);

private:

    std::vector<Jet> leptons_;
    float scalar_ht_;
    float missing_et_;
    std::vector<Jet> jets_;

};

}
