/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "Quintet.hh"
#include "TopPartnerHadronicTagger.hh"
#include "TopLeptonicTagger.hh"
#include "HiggsTagger.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class VetoTopPartnerLeptonicTagger : public BranchTagger<TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final {
        return "VetoTopPartnerLeptonic";
    }

    std::string NiceName() const final {
        return "#slash{T}_{l}";
    }

private:

    std::vector<Quintet> Quintets(Event const& event, PreCuts const& pre_cuts, std::function<Quintet(Quintet&)> const& function) const;

    Reader<TopPartnerHadronicTagger> partner_reader_;

    Reader<TopLeptonicTagger> top_reader_;

    Reader<HiggsTagger> higgs_reader_;

};

}

}
