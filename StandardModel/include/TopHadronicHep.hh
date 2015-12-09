#pragma once

#include "TaggerTemplate.hh"
#include "multiplets/Triplet.hh"
#include "BranchesSm.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief prepares the data for the top tagger
 *
 */
class TopHadronicHep : public TaggerTemplate<Triplet, TopHadronicHepBranch>
{

public:

    TopHadronicHep();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Triplet> Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string LatexName() const final;

    /**
     * @brief tagges the tops
     *
     */
    std::vector<fastjet::PseudoJet> Tops(std::vector<fastjet::PseudoJet>& e_flows);

private:

    std::vector<Particle> Particles(boca::Event const& event) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    std::vector<Triplet> Triplets(Event const& event, PreCuts const& pre_cuts, std::function<Triplet(Triplet&)> const& function) const;

    Mass top_mass_window_;

};

}
}
