#pragma once

#include "boca/BranchesHeavyHiggs.hh"
#include "boca/standardmodel/tagger/Bottom.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/Tagger.hh"
#include "boca/CutVariables.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class CutTagger : public Tagger<CutVariables, HeavyHiggsCut>
{

public:

    int Train(const boca::Event& event, const boca::PreCuts&, boca::Tag) override;

    std::vector<CutVariables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    TMVA::Types::EMVA Mva() const override;

private:

    boost::optional<CutVariables> CutMethod(const boca::Event& event);

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
