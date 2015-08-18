/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Singlet.hh"

namespace boca {

class Event;

class GlobalObservables {

public:

    void SetEvent(Event const& event, boca::Jets const& jets);

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

    boca::Jets Jets() const;

    void SetJets(const boca::Jets jets);

private:

    boca::Jets leptons_;
    float scalar_ht_;
    float missing_et_;
    boca::Jets jets_;

};

}
