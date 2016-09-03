#pragma once

#include "boca/multiplets/Quintet.hh"
#include "standardmodel/tagger/TopHadronic.hh"
#include "standardmodel/tagger/Boson.hh"

#include "include/branch/TopPartner.hh"

namespace toppartner
{

using namespace boca;

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHadronicNeutral : public Tagger<Quintet, branch::TopPartnerBranch>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(boca::Event const& event) const;

private:

    std::vector<Quintet> Quintets(const boca::Event& event, const std::function< Quintet(Quintet&) >& function);

    Reader<standardmodel::tagger::TopHadronic> top_reader_;

    Reader<standardmodel::tagger::Boson> boson_reader_;

};

}

}
