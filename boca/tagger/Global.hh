#pragma once

#include "boca/multivariant/Reader.hh"
#include "boca/branch/Global.hh"
#include "boca/multiplets/GlobalObservables.hh"
#include "boca/standardmodel/tagger/Bottom.hh"

namespace boca
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class Global : public Tagger<GlobalObservables, branch::Global>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<GlobalObservables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
