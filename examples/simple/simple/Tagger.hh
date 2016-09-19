#pragma once

// include the Tagger base class
#include "boca/tagger/Tagger.hh"

// include the simple Observable definition
#include "simple/Observables.hh"
// include the simple Branch used by TMVA
#include "simple/Branch.hh"

namespace simple
{

// each Tagger class must inherit from the boca::Tagger base class
// the Base class expect a set of Observables and a root Branch definition as template paramter
class Tagger : public boca::Tagger<Observables, Branch>
{

public:

    // The first phase during a multivariant analysis is called Training phase
    int Train(boca::Event const &event, boca::PreCuts const &pre_cuts, boca::Tag tag) override;

    //  During the second Reading phase we retrieve objects of the Observable set
    std::vector<Observables> Multiplets(boca::Event const &event, boca::PreCuts const &pre_cuts, TMVA::Reader const &reader) override;

    // Name of the Tagger
    std::string Name() const override;

};

}
