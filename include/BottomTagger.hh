# pragma once

# include "BranchTagger.hh"
# include "Branches.hh"


namespace analysis
{

/**
 * @brief Bottom BDT tagger
 *
 */
class BottomTagger : public BranchTagger<BottomBranch>
{

public:

    BottomTagger();

    /**
     * @brief Train the bottom tagger with pre cuts
     */
    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    Jets Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    /**
     * @brief Save all jets with bottom bdt value condidering pre cuts
     *
     */
    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    /**
     * @brief calculate bottom bdt for given jet
     *
     */
    fastjet::PseudoJet Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);

    /**
     * @brief calculate bottom bdt for subjets of given jet
     *
     */
    Jets SubMultiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader, const int sub_jet_number);

protected:

    virtual inline std::string ClassName() const {
        return "BottomTagger";
    }

private:

    Jets Multiplets(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader);

    Jets Multiplets(const Jets &jets, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplets(jets,pre_cuts,reader);
    }

    Jets CleanJets(Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Object::Tag tag);

    bool Problematic(const fastjet::PseudoJet &jet, analysis::PreCuts &pre_cuts, const analysis::Object::Tag tag) const;

    bool Problematic(const fastjet::PseudoJet &jet, analysis::PreCuts &pre_cuts) const;

    Jets SubJets(const Jets &jets, const int sub_jet_number);

    Jets TrainOnSubJets(const Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Object::Tag tag, const int sub_jet_number);

};

}
