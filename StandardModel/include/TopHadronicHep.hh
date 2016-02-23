#pragma once

#include "TaggerTemplate.hh"
#include "multiplets/Triplet.hh"
#include "BranchesSm.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief BDT tagger for hadronically decaying top quarks based on the HEP top tagger
 *
 */
class TopHadronicHep : public TaggerTemplate<Triplet, TopHadronicHepBranch>
{

public:

    TopHadronicHep();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Triplet> Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

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
