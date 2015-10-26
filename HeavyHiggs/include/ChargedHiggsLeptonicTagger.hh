#pragma once

#include "TopLeptonicTagger.hh"
#include "Triplet.hh"
#include "Branch.hh"

namespace boca {

namespace heavyhiggs {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsLeptonicTagger : public TaggerTemplate<Triplet,ChargedHiggsLeptonicBranch> {

public:

    ChargedHiggsLeptonicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<boca::Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final { return "ChargedHiggsLeptonic"; }

private:

    boca::Reader<boca::BottomTagger> bottom_reader_;

    boca::Reader<boca::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
