#pragma once

#include "Quintet.hh"
#include "TopHadronicTagger.hh"
#include "BosonTagger.hh"
#include "BranchesTopPartner.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHadronicTagger : public BranchTagger<TopPartnerBranch>
{

public:

    TopPartnerHadronicTagger();

    int Train(const Event& event, const PreCuts& pre_cuts,
              Tag tag) const final;

    std::vector<Quintet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts,
               const TMVA::Reader& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "TopPartnerHadronic";
    }

    std::string NiceName() const final {
        return "#tilde t_{h}";
    }

private:

    Reader<TopHadronicTagger> top_reader_;

    Reader<BosonTagger> boson_reader_;

};

}

}
