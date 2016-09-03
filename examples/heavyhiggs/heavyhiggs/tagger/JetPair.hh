/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Doublet.hh"
#include "boca/multivariant/Reader.hh"
#include "standardmodel/tagger/Bottom.hh"
#include "boca/tagger/Tagger.hh"

#include "heavyhiggs/branch/JetPair.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 * @brief JetPair BDT tagger
 *
 */
class JetPair : public Tagger<Doublet, branch::JetPair>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Doublet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Particle> PairBottomQuarks(boca::Event const& event, Tag tag) const;

    bool CheckIfBadBottom(boca::Doublet const& doublet, std::vector<Particle> const& jets) const;

    std::vector<Particle> HiggsParticle(boca::Event const& event, Tag tag) const;

    Doublet TruthDoubletPair(Doublet const& doublet, std::vector<Particle> const& bottoms, Tag tag) const;

private:

    std::vector<boca::Jet> TruthJetPair(boca::Event const& event, std::vector<boca::Jet>& jets, Tag tag) const;

    std::vector<Doublet> TruthDoubletPairs(boca::Event const& event, std::vector<Doublet>& doublets, Tag tag) const;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
