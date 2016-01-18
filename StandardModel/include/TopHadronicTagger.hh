/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "WHadronicTagger.hh"
#include "multiplets/Triplet.hh"

namespace boca
{

class MomentumRange;

namespace standardmodel
{

/**
 * @brief Hadronic top BDT tagger
 *
 */
class TopHadronicTagger : public TaggerTemplate<Triplet, TopHadronicBranch>
{

    using Function = std::function<boost::optional<Triplet>(Triplet&, std::vector<Jet> const&)>;

public:

    TopHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final;

    std::string LatexName() const final;

    std::vector<Particle> Particles(Event const& event, boca::PreCuts const& pre_cuts) const;

private:

    std::vector<Triplet> ThreeJets(std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> TwoJets(std::vector<Jet> const& jets, Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> ThreeSubJets(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> TwoSubJets(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const;

    boost::optional<Triplet> HighlyBoosted(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function) const;

    boost::optional<Triplet> Tripple(Doublet const& doublet, Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range, bool check_overlap = false) const;

    boost::optional<Triplet> Tripple(Triplet& triplet, std::vector<Lepton> const& leptons, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<Triplet> Triplets(Event const& event, Function const& function) const;

    std::vector<Triplet> Triplets(std::vector<Doublet> const& doublets, std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> Triplets(Doublet const& doublet, std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const;

    boost::optional<Triplet> Multiplet(Triplet& triplet, std::vector<Lepton> const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    void NSubJettiness(Triplet& triplet) const;

    Momentum LeptonPt(Triplet const& triplet, std::vector<Lepton> const& leptons) const;

    Reader<BottomTagger> bottom_reader_;

    Reader<WHadronicTagger> w_hadronic_reader_;

    Mass top_mass_window_;

};

}

}