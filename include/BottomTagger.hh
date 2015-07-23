#pragma once

#include "BranchTagger.hh"
#include "Branches.hh"


namespace analysis {

/**
 * @brief Bottom BDT tagger
 *
 */
class BottomTagger : public BranchTagger<BottomBranch> {

public:

    BottomTagger();

    /**
     * @brief Train the bottom tagger with pre cuts
     */
    int Train(const Event& event, const PreCuts& pre_cuts,  Tag tag) const final;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    Jets Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    /**
     * @brief Save all jets with bottom bdt value condidering pre cuts
     *
     */
    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    /**
     * @brief calculate bottom bdt for given jet
     *
     */
    fastjet::PseudoJet Multiplet(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const;

    /**
     * @brief calculate bottom bdt for subjets of given jet
     *
     */
    Jets SubMultiplet(const fastjet::PseudoJet& jet, const TMVA::Reader& reader, int sub_jet_number) const;

    std::string Name() const final
    {
        return "Bottom";
    }

    std::string NiceName() const final
    {
        return "b";
    }

private:

    Jets Multiplets(const Jets& jets, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Jets SubMultiplets(const analysis::Jets& jets, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader, const size_t sub_jet_number) const;

    Jets Multiplets(const Jets& jets, const TMVA::Reader& reader) const;

    Jets CleanJets(Jets& jets, const PreCuts& pre_cuts,  Tag tag) const;

    bool Problematic(const fastjet::PseudoJet& jet, const analysis::PreCuts& pre_cuts, Tag tag) const;

    bool Problematic(const fastjet::PseudoJet& jet, const analysis::PreCuts& pre_cuts) const;

    Jets SubJets(const Jets& jets, int sub_jet_number) const;

    Jets TrainOnSubJets(const Jets& jets, const PreCuts& pre_cuts,  Tag tag, int sub_jet_number) const;

};

}
