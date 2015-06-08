# pragma once

# include "Tagger.hh"
# include "Reader.hh"
# include "Singlet.hh"

namespace analysis
{

/**
 * @brief Bottom BDT tagger
 *
 */
class BottomTagger : public Tagger
{

public:

    BottomTagger();

    /**
     * @brief Train the bottom tagger without pre cuts
     */
    int Train(Event &event, const Object::Tag tag) {
        PreCuts pre_cuts;
        return Train(event,pre_cuts,tag);
    }

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
     * @brief Return all jets of the event with bottom bdt value without pre cuts
     *
     */
    Jets Multiplets(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplets(event,pre_cuts,reader);
    }

    /**
     * @brief Save all jets with bottom bdt value condidering pre cuts
     *
     */
    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        Jets jets = Multiplets(event, pre_cuts, reader);
        std::vector<Singlet> singlets;
        for(const auto &jet : jets) singlets.emplace_back(Singlet(jet));
        return SaveEntries<BottomBranch>(singlets);
    }

    /**
     * @brief Save all jets with bottom bdt value without pre cuts
     *
     */
    int GetBdt(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event,pre_cuts,reader);
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

    TClass &Class() const {
        return *BottomBranch::Class();
    }

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Object::Tag tag);

    Jets SubJets(const Jets &jets, const int sub_jet_number);

    Jets TrainOnSubJets(const Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Object::Tag tag, const int sub_jet_number);

    BottomBranch branch_;

};

}
