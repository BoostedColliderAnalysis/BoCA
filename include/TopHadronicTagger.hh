/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "WHadronicTagger.hh"
#include "Triplet.hh"
#include "MomentumRange.hh"

namespace boca
{

/**
 * @brief Hadronic top BDT tagger
 *
 */
class TopHadronicTagger : public TaggerTemplate<boca::Triplet, TopHadronicBranch>
{

    typedef std::function<boca::Triplet(boca::Triplet&, Jets const&, bool&)> Function;

public:

    TopHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<boca::Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final;

    std::string NiceName() const final;

    Jets TopParticles(Event const& event) const;

private:

    std::vector<Triplet> ThreeJets(Jets const& jets, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> TwoJets(Jets const& jets, fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> ThreeSubJets(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> TwoSubJets(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    Triplet HighlyBoosted(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function) const;

    boca::Triplet Triplet(Doublet const& doublet, fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range, bool& failure, bool check_overlap = false) const;

    boca::Triplet Triplet(boca::Triplet& triplet, boca::Jets const& leptons, PreCuts const& pre_cuts, Tag tag, bool& failure) const;

    std::vector<boca::Triplet> Triplets(Event const& event, Function const& function) const;

    std::vector<boca::Triplet> Triplets(std::vector<Doublet> const& doublets, Jets const& jets, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<boca::Triplet> Triplets(Doublet const& doublet, Jets const& jets, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    boca::Triplet Multiplet(boca::Triplet& triplet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader, bool& failure) const;

    bool Problematic(boca::Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(boca::Triplet const& triplet, PreCuts const& pre_cuts) const;

    void NSubJettiness(boca::Triplet& triplet) const;

    SubJettiness NSubJettiness(fastjet::PseudoJet const& jet) const;

    float LeptonPt(boca::Triplet const& triplet, Jets const& leptons) const;

    std::vector<boca::Triplet> ordered_triplets(Jets const& jets, unsigned sub_jet_number, std::function<boca::Triplet(fastjet::PseudoJet const& piece_1, fastjet::PseudoJet const& piece_2, fastjet::PseudoJet const& piece_3)> const& function) const;

    Reader<BottomTagger> bottom_reader_;

    Reader<WHadronicTagger> w_hadronic_reader_;

    Mass top_mass_window_;

};

}

