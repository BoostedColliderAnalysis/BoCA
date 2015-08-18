/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "WHadronicTagger.hh"
#include "Triplet.hh"

namespace analysis
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

    std::vector<analysis::Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final {
        return "TopHadronic";
    }

    std::string NiceName() const final {
        return "t_{h}";
    }

private:

    analysis::Triplet Triplet(Doublet const& doublet, fastjet::PseudoJet const& jet, Jets const& leptons, PreCuts const& pre_cuts, Tag tag, bool check_overlap = false) const;

    analysis::Triplet Triplet(analysis::Triplet& triplet, analysis::Jets const& leptons, analysis::PreCuts const& pre_cuts, Tag tag) const;

    std::vector<analysis::Triplet> Triplets(std::vector<Doublet> const& doublets, Jets const& jets, Jets const& leptons, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<analysis::Triplet> Triplets(Doublet const& doublet, Jets const& jets, Jets const& leptons, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<analysis::Triplet> Multiplets(Event const& event, TMVA::Reader const& reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::vector<analysis::Triplet>  Multiplets(std::vector<Doublet> const& doublets, Jets const& jets, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::vector<analysis::Triplet>  Multiplets(Doublet const& doublet, Jets const& jets, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    analysis::Triplet Multiplet(Doublet const& doublet, fastjet::PseudoJet const& jet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader, bool check_overlap = false) const;

    analysis::Triplet Multiplet(analysis::Triplet& triplet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    bool Problematic(analysis::Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(analysis::Triplet const& triplet, PreCuts const& pre_cuts) const;

    void NSubJettiness(analysis::Triplet& triplet) const;

    SubJettiness NSubJettiness(fastjet::PseudoJet const& jet) const;

    float LeptonPt(analysis::Triplet const& triplet, Jets const& leptons) const;

    Reader<BottomTagger> bottom_reader_;

    Reader<WHadronicTagger> w_hadronic_reader_;

    float top_mass_window_ ;

    std::vector<analysis::Triplet> ordered_triplets(Jets const& jets, unsigned sub_jet_number, std::function<analysis::Triplet(fastjet::PseudoJet const& piece_1, fastjet::PseudoJet const& piece_2, fastjet::PseudoJet const& piece_3)> const& function) const;

};

}

