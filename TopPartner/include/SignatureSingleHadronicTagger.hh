#pragma once

#include <functional>
#include "Decuplet.hh"
#include "TopPartnerHadronicTagger.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "HiggsTagger.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSingleHadronicTagger : public BranchTagger<SignatureSingleBranch>
{

public:

    SignatureSingleHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::vector<Decuplet532> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final {
       return "SignatureSingleHadronic";
    }

    std::string NiceName() const final {
        return "T_{h}t_{l}h";
    }

private:

    std::vector<Decuplet532> Decuplets(Event const& event, std::function<Decuplet532(Decuplet532&)> const& function) const;

    Reader<TopPartnerHadronicTagger> partner_reader_;

    Reader<TopLeptonicTagger> top_reader_;

    Reader<HiggsTagger> higgs_reader_;

    Reader<TopPartnerLeptonicTagger> veto_reader_;

};

}

}
