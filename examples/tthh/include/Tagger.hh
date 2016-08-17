#pragma once

#include "boca/tagger/Tagger.hh"

#include "include/Observables.hh"
#include "include/Branch.hh"

class Tagger : public boca::Tagger<Observables, Branch>
{

public:

    int Train(boca::Event const &event, boca::PreCuts const &pre_cuts, boca::Tag tag) override;

//     using boca::Tagger::Multiplets;

    std::vector<Observables> Multiplets(boca::Event const &event, boca::PreCuts const &pre_cuts, TMVA::Reader const &reader) override;

    std::string Name() const override;

};
