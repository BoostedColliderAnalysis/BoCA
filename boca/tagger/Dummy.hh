#pragma once

#include "boca/tagger/Tagger.hh"
#include "boca/branch/Global.hh"
#include "boca/multiplets/Global.hh"

namespace boca
{

namespace tagger
{

class Dummy : public boca::Tagger<boca::Global, boca::branch::Global>
{

public:

    int Train(boca::Event const & event, boca::PreCuts const & pre_cuts, boca::Tag tag) override;

    std::vector<boca::Global> Multiplets(boca::Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const & reader) override;

    std::string Name() const override;

};

}

}
