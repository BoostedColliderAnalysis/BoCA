#pragma once

#include "boca/multivariant/Reader.hh"
#include "boca/branch/Global.hh"
#include "boca/multiplets/Global.hh"
#include "standardmodel/tagger/Bottom.hh"

namespace standardmodel
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class Global : public boca::Tagger<boca::Global, boca::branch::Global>
{

public:

    int Train(boca::Event const& event, boca::PreCuts const& pre_cuts, boca::Tag tag) override;

    using Tagger::Multiplets;

    std::vector<boca::Global> Multiplets(boca::Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    boca::Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
