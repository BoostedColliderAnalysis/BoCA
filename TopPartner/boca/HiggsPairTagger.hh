#pragma once

#include "boca/multiplets/Quartet.hh"
#include "boca/standardmodel/HiggsTagger.hh"
#include "boca/BranchesTopPartner.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HiggsPairTagger : public Tagger<Quartet22, MultiBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quartet22> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<std::pair<Particle, Particle>> Particles(const boca::Event& event, boca::Tag tag) const;

private:

  std::vector<Quartet22> Quartets(const boca::Event& event, const std::function< Quartet22(Quartet22&) >& function);

    Reader<standardmodel::HiggsTagger> higgs_reader_;
};

}

}
