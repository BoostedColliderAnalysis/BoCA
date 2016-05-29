#pragma once

#include "boca/multiplets/Quintet.hh"
#include "boca/standardmodel/TopHadronicTagger.hh"
#include "boca/ResonanceTagger.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class NewPartnerHadronicTagger : public Tagger<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(Event const& event) const;

private:

    std::vector<Quintet> Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function);

    Reader<standardmodel::TopHadronicTagger> top_reader_;

    Reader<ResonanceTagger> resonance_reader_;

};

}

}
