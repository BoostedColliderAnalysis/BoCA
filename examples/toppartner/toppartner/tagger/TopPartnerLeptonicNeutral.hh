#pragma once

#include "boca/multiplets/Quintet.hh"

#include "standardmodel/tagger/TopLeptonic.hh"
#include "standardmodel/tagger/Boson.hh"

#include "toppartner/branch/TopPartner.hh"

namespace toppartner
{

using namespace boca;

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerLeptonicNeutral : public Tagger<Quintet, branch::TopPartnerBranch>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(boca::Event const& event, Tag tag = Tag::signal) const;

    std::vector<Quintet> Quintets(boca::Event const& event, std::function<Quintet(Quintet&)> const& function);

private:

    Reader<standardmodel::tagger::TopLeptonic> top_reader_;

    Reader<standardmodel::tagger::Boson> boson_reader_;
};

}

}
