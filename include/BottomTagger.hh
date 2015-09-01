/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Branches.hh"
#include "BranchTagger.hh"


namespace boca {

/**
 * @brief Derived Tagger class for bottom jets.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class BottomTagger : public BranchTagger<BottomBranch> {

public:

    BottomTagger();

    /**
     * @brief Train the bottom tagger with pre cuts
     */
    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    Jets Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    /**
     * @brief Save all jets with bottom bdt value condidering pre cuts
     *
     */
    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    /**
     * @brief calculate bottom bdt for given jet
     *
     */
    fastjet::PseudoJet Multiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const;

    /**
     * @brief calculate bottom bdt for subjets of given jet
     *
     */
    Jets SubMultiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader, int sub_jet_number) const;

    std::string Name() const final { return "Bottom"; }

    std::string NiceName() const final { return "b"; }

private:

    Jets Multiplets(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Jets SubMultiplets(boca::Jets const& jets, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader, size_t sub_jet_number) const;

    Jets Multiplets(Jets const& jets, TMVA::Reader const& reader) const;

    Jets CleanJets(Jets& jets, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(fastjet::PseudoJet const& jet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(fastjet::PseudoJet const& jet, boca::PreCuts const& pre_cuts) const;

    Jets SubJets(Jets const& jets, int sub_jet_number) const;

    Jets TrainOnSubJets(Jets const& jets, PreCuts const& pre_cuts, Tag tag, int sub_jet_number) const;

};

}
