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

public:

    TopHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    /**
     * @brief Signed id of hadronic top, if 2 hadronic top with opposite charge are found 0 is returned
     *
     */
    int TopHadronicId(Event const& event) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 2);
    }

    std::vector<boca::Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final {
        return "TopHadronic";
    }

    std::string NiceName() const final {
        return "t_{h}";
    }

private:

    boca::Triplet Triplet(Doublet const& doublet, fastjet::PseudoJet const& jet, Jets const& leptons, PreCuts const& pre_cuts, Tag tag, bool check_overlap = false) const;

    boca::Triplet Triplet(boca::Triplet& triplet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const;

    std::vector<boca::Triplet> Triplets(std::vector<Doublet> const& doublets, Jets const& jets, Jets const& leptons, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<boca::Triplet> Triplets(Doublet const& doublet, Jets const& jets, Jets const& leptons, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<boca::Triplet> Multiplets(Event const& event, TMVA::Reader const& reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::vector<boca::Triplet>  Multiplets(std::vector<Doublet> const& doublets, Jets const& jets, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::vector<boca::Triplet>  Multiplets(Doublet const& doublet, Jets const& jets, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    boca::Triplet Multiplet(Doublet const& doublet, fastjet::PseudoJet const& jet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader, bool check_overlap = false) const;

    boca::Triplet Multiplet(boca::Triplet& triplet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    bool Problematic(boca::Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(boca::Triplet const& triplet, PreCuts const& pre_cuts) const;

    void NSubJettiness(boca::Triplet& triplet) const;

    SubJettiness NSubJettiness(fastjet::PseudoJet const& jet) const;

    float LeptonPt(boca::Triplet const& triplet, Jets const& leptons) const;

    Reader<BottomTagger> bottom_reader_;

    Reader<WHadronicTagger> w_hadronic_reader_;

    Mass top_mass_window_;

    std::vector<boca::Triplet> ordered_triplets(Jets const& jets, unsigned sub_jet_number, std::function<boca::Triplet(fastjet::PseudoJet const& piece_1, fastjet::PseudoJet const& piece_2, fastjet::PseudoJet const& piece_3)> const& function) const;

};

}

