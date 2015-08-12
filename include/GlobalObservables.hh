#pragma once

#include "Singlet.hh"

namespace analysis {

class Event;

class GlobalObservables {

public:

    void SetEvent(Event const& event, analysis::Jets const& jets);

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

    analysis::Singlet Singlet() const;

    analysis::Jets Jets() const;

    void SetJets(const analysis::Jets jets);

private:

    analysis::Jets leptons_;
    float scalar_ht_;
    float missing_et_;
    analysis::Jets jets_;

};

}
