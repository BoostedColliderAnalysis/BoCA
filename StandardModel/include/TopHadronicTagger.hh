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

namespace standardmodel
{

/**
 * @brief Hadronic top BDT tagger
 *
 */
class TopHadronicTagger : public TaggerTemplate<Triplet, TopHadronicBranch>
{

  typedef std::function<boost::optional<Triplet>(Triplet&, Jets const&)> Function;

public:

    TopHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final;

    std::string NiceName() const final;

    Jets TopParticles(Event const& event) const;

private:

    std::vector<Triplet> ThreeJets(Jets const& jets, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> TwoJets(Jets const& jets, fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> ThreeSubJets(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> TwoSubJets(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    boost::optional<Triplet> HighlyBoosted(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function) const;

    boost::optional<Triplet> Tripple(Doublet const& doublet, fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range, bool check_overlap = false) const;

    boost::optional<Triplet> Tripple(Triplet& triplet, boca::Jets const& leptons, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<Triplet> Triplets(Event const& event, Function const& function) const;

    std::vector<Triplet> Triplets(std::vector<Doublet> const& doublets, Jets const& jets, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> Triplets(Doublet const& doublet, Jets const& jets, Jets const& leptons, Function const& function, MomentumRange const& range) const;

    boost::optional<Triplet> Multiplet(Triplet& triplet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    void NSubJettiness(Triplet& triplet) const;

    float LeptonPt(Triplet const& triplet, Jets const& leptons) const;

    std::vector<Triplet> ordered_triplets(Jets const& jets, unsigned sub_jet_number, std::function<boost::optional<Triplet>(fastjet::PseudoJet const& piece_1, fastjet::PseudoJet const& piece_2, fastjet::PseudoJet const& piece_3)> const& function) const;

    Reader<BottomTagger> bottom_reader_;

    Reader<WHadronicTagger> w_hadronic_reader_;

    Mass top_mass_window_;

};

}

}
