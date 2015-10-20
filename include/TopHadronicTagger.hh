/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "WHadronicTagger.hh"
#include "Triplet.hh"

namespace boca
{

/**
 * @brief Hadronic top BDT tagger
 *
 */
class TopHadronicTagger : public BranchTagger<TopHadronicBranch>
{

    typedef std::function<boca::Triplet(boca::Triplet&, Jets const&, bool&)> Function;

public:

    TopHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 2);
    }

    std::vector<boca::Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final {
        return "TopHadronic";
    }

    std::string NiceName() const final {
        return "t_{h}";
    }

    Jets TopParticles(Event const& event) const;

private:

    std::vector<Triplet> ThreeJets(Jets const& jets, Jets const& leptons, Function const& function) const;

    std::vector<Triplet> TwoJets(Jets const& jets, fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function) const;

    std::vector<Triplet> ThreeSubJets(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function) const;

    std::vector<Triplet> TwoSubJets(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function) const;

    Triplet HighlyBoosted(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function) const;

    boca::Triplet Triplet(Doublet const& doublet, fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, bool& failure, bool check_overlap = false) const;

    boca::Triplet Triplet(boca::Triplet& triplet, boca::Jets const& leptons, PreCuts const& pre_cuts, Tag tag, bool& failure) const;

    std::vector<boca::Triplet> Triplets(Event const& event, PreCuts const& pre_cuts, Function const& function) const;

    std::vector<boca::Triplet> Triplets(std::vector<Doublet> const& doublets, Jets const& jets, Jets const& leptons, Function const& function) const;

    std::vector<boca::Triplet> Triplets(Doublet const& doublet, Jets const& jets, Jets const& leptons, Function const& function) const;

    std::vector<boca::Triplet> Multiplets(Event const& event, TMVA::Reader const& reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

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

    Momentum PtMin(Id id, double cone_size = DetectorGeometry::JetConeSize()) const {
        return 0.8 * MassOf(id) * 2. / cone_size;
    }

    Momentum PtMax(Id id, double cone_size = DetectorGeometry::JetConeSize()) const {
        return 1.2 * MassOf(id) * 2. / cone_size;
    }

    bool Softer(fastjet::PseudoJet const& jet, Id id, bool limit = false) const {
        double cone_size = limit ? DetectorGeometry::MinCellResolution() : DetectorGeometry::JetConeSize();
        return jet.pt() * GeV < PtMax(id, cone_size);
    }

    bool Harder(fastjet::PseudoJet const& jet, Id id, bool limit = false) const {
        double cone_size = limit ? DetectorGeometry::MinCellResolution() : DetectorGeometry::JetConeSize();
        return jet.pt() * GeV > PtMin(id, cone_size);
    }


};

}

