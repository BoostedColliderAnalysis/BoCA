#pragma once

#include "boca/multiplets/Quintet.hh"
#include "boca/standardmodel/tagger/TopLeptonic.hh"

#include "include/tagger/ResonanceTagger.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class NewPartnerLeptonicTagger : public Tagger<Quintet, branch::TopPartnerBranch>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(boca::Event const& event) const;

private:

    std::vector<Quintet> Quintets(boca::Event const& event, std::function<Quintet(Quintet&)> const& function);

    Reader<standardmodel::tagger::TopLeptonic> top_reader_;

    Reader<ResonanceTagger> boson_reader_;
};

}
