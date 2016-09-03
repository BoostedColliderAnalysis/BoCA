#pragma once

#include "boca/multiplets/Quartet.hh"
#include "standardmodel/tagger/Higgs.hh"

#include "boca/branch/Multi.hh"

namespace toppartner
{

using namespace boca;

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HiggsPair : public Tagger<Quartet22, boca::branch::Multi>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quartet22> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<std::pair<Particle, Particle>> Particles(const boca::Event& event, boca::Tag tag) const;

private:

    std::vector<Quartet22> Quartets(const boca::Event& event, const std::function< Quartet22(Quartet22&) >& function);

    Reader<standardmodel::tagger::Higgs> higgs_reader_;
};

}

}
