/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Doublet.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/standardmodel/BottomTagger.hh"
#include "HeavyHiggs/boca/BranchesHeavyHiggs.hh"
#include "boca/Tagger.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief JetPair BDT tagger
 *
 */
class JetPairTagger : public Tagger<Doublet, JetPairBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Particle> PairBottomQuarks(Event const& event, Tag tag) const;

    bool CheckIfBadBottom(boca::Doublet const& doublet, std::vector<Particle> const& jets) const;

    std::vector<Particle> HiggsParticle(Event const& event, Tag tag) const;

    Doublet TruthDoubletPair(Doublet const& doublet, std::vector<Particle> const& bottoms, Tag tag) const;

private:

    std::vector<Jet> TruthJetPair(Event const& event, std::vector<Jet>& jets, Tag tag) const;

    std::vector<Doublet> TruthDoubletPairs(Event const& event, std::vector<Doublet>& doublets, Tag tag) const;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
