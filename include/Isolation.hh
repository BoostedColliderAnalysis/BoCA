#pragma once

#include "Leptons.hh"
// #include "TreeReader.hh"

namespace boca
{

class Event;
class TreeReader;

class Isolation : public Leptons
{
public:
    Isolation(Event& event, boca::TreeReader const& tree_reader);
    std::vector<Lepton> leptons() const;
    std::vector<Lepton> Electrons() const;
    std::vector<Lepton> Muons() const;
    std::vector<Lepton> Photons() const;
private:
    Event& event_;
};

}
