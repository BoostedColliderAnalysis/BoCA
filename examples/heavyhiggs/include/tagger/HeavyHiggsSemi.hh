#pragma once

#include "standardmodel/tagger/TopLeptonic.hh"
#include "standardmodel/tagger/TopHadronic.hh"
#include "boca/multiplets/Sextet.hh"

#include "include/branch/HeavyHiggsSemi.hh"

namespace heavyhiggs
{

/**
* @brief %Tagger
*
*/
namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemi : public Tagger<Sextet, branch::HeavyHiggsSemi>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Sextet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Particle> TopParticles(boca::Event const& event, Decay decay) const;

    static std::vector<Particle> HiggsParticle(boca::Event const& event, Tag tag);

    std::vector<Triplet> FinalTriplet(boca::Event const& event, Tag tag, Decay decay);

private:

    Reader<standardmodel::tagger::TopHadronic> top_hadronic_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;
};

}

}
