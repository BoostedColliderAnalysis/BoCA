#pragma once

#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/standardmodel/tagger/Boson.hh"
#include "boca/multiplets/Quintet.hh"
#include "boca/BranchesTopPartner.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerLeptonicNeutralTagger : public Tagger<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(Event const& event, Tag tag = Tag::signal) const;

private:

    std::vector<Quintet> Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function);

    Reader<standardmodel::tagger::TopLeptonic> top_reader_;

    Reader<standardmodel::tagger::Boson> boson_reader_;
};

}

}
