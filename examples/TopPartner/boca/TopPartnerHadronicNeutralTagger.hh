#pragma once

#include "boca/multiplets/Quintet.hh"
#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/standardmodel/tagger/Boson.hh"
#include "boca/BranchesTopPartner.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHadronicNeutralTagger : public Tagger<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(Event const& event) const;

private:

    std::vector<Quintet> Quintets(const boca::Event& event, const std::function< Quintet(Quintet&) >& function);

    Reader<standardmodel::tagger::TopHadronic> top_reader_;

    Reader<standardmodel::tagger::Boson> boson_reader_;

};

}

}