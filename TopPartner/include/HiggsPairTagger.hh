#pragma once

#include "multiplets/Quartet.hh"
#include "HiggsTagger.hh"
#include "BranchesTopPartner.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HiggsPairTagger : public TaggerTemplate<Quartet22, HiggsPairBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Quartet22> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

    std::vector<std::pair<Particle, Particle>> Particles(const boca::Event& event, boca::Tag tag) const;

private:

    std::vector<Quartet22> Quartets(Event const& event, std::function<Quartet22(Quartet22&)> const& function) const;

    Reader<standardmodel::HiggsTagger> higgs_reader_;
};

}

}
