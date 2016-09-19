#pragma once

#include "boca/tagger/Tagger.hh"

#include "tthh/Observables.hh"
#include "tthh/branch/Global.hh"

namespace tthh {

namespace tagger {

class Global : public boca::Tagger<Observables, branch::Global>
{

public:

    int Train(boca::Event const &event, boca::PreCuts const &pre_cuts, boca::Tag tag) override;

    std::vector<Observables> Multiplets(boca::Event const &event, boca::PreCuts const &pre_cuts, TMVA::Reader const &reader) override;

    std::string Name() const override;

    TMVA::Types::EMVA Mva() const override;

};

}

}
