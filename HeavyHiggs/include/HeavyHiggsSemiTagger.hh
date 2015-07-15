#pragma once

#include "TopLeptonicTagger.hh"
#include "Sextet.hh"
#include "TopHadronicTagger.hh"
#include "Branch.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public BranchTagger<HeavyHiggsSemiBranch>
{

public:

    HeavyHiggsSemiTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<Sextet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final {
        return "HeavyHiggsSemi";
    }

    Jets Particles_Top(const Event &event, int charge) const;

    Jets Particle_Higgs(const Event &event, const Tag tag) const;

    std::vector<Triplet> FinalTriplet(const Event &event, const Tag tag, int charge) const;

private:

    Reader<TopHadronicTagger> top_hadronic_reader_;

    Reader<TopLeptonicTagger> top_leptonic_reader_;
};

}

}
