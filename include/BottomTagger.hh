# pragma once

# include "Tagger.hh"
# include "Reader.hh"
# include "Singlet.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
namespace analysis
{

class BottomTagger : public Tagger
{

public:

    BottomTagger();

    int Train(Event &event, const Object::Tag tag) {
        PreCuts pre_cuts;
        return Train(event,pre_cuts,tag);
    }

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    Jets GetMultiJetBdt(const Jets& jets, const TMVA::Reader& reader);

    Jets GetJetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    Jets Multiplets(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetJetBdt(event,pre_cuts,reader);
    }

    Jets GetSubBdt(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        Jets jets = GetJetBdt(event, pre_cuts, reader);
        std::vector<Singlet> singlets;
        for(const auto &jet : jets) singlets.emplace_back(Singlet(jet));
        return SaveEntries<BottomBranch>(singlets);
    }

    int GetBdt(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event,pre_cuts,reader);
    }

    fastjet::PseudoJet GetJetBdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);


    Jets GetSubJets(const Jets &jets, const int sub_jet_number) {
        Jets subjets;
        for(const auto &jet : jets) {
            Jets jets = Tagger::GetSubJets(jet,sub_jet_number);
            subjets = JoinVectors(subjets, jets);
        }
        return subjets;
    }

    Jets GetJetBdt(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader);

    Jets GetJetBdt(const Jets &jets, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetJetBdt(jets,pre_cuts,reader);
    }

    Jets GetSubJetBdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader, const int sub_jet_number);

protected:

    virtual inline std::string ClassName() const {
        return "BottomTagger";
    }

private:

    TClass &Class() const {
        return *BottomBranch::Class();
    }

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Object::Tag tag);

    Jets GetSubJets(const Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Object::Tag tag, const int sub_jet_number);

    BottomBranch branch_;

};
}
