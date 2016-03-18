#pragma once

#include "Jet.hh"

namespace boca
{

class Event;

class ClosestLepton
{
public:
    ClosestLepton();
    ClosestLepton(Jet const& jet);
    ClosestLepton(Jet const& jet, std::vector<Lepton> const& leptons);
    ClosestLepton(Jet const& jet, Event const& event);
    void SetJet(Jet const& jet);
    void AddLepton(Lepton const& lepton);
    void AddLeptons(std::vector<Lepton> const& leptons);
    Angle DeltaR();
    Momentum Pt();
private:
    Lepton lepton_;
    Jet jet_;
};

}
