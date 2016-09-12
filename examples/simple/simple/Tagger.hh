#pragma once

#include "boca/tagger/Tagger.hh"

#include "simple/Observables.hh"
#include "simple/Branch.hh"

namespace simple
{

class Tagger : public boca::Tagger<Observables, Branch>
{

public:

    int Train(boca::Event const &event, boca::PreCuts const &pre_cuts, boca::Tag tag) override;

//     using boca::Tagger::Multiplets;

    std::vector<Observables> Multiplets(boca::Event const &event, boca::PreCuts const &pre_cuts, TMVA::Reader const &reader) override;

    std::string Name() const override;

};

}