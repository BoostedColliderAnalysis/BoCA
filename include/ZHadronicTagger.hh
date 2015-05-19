# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief W BDT tagger
 *
 */
class ZHadronicTagger : public Tagger
{

public:

    ZHadronicTagger();

    int Train(Event &event, const Object::Tag Tag) {
        PreCuts pre_cuts;
        return Train(event, pre_cuts, Tag);
    }

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag Tag);

    virtual int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(GetDoublets(event, reader));
    }

    virtual int GetBdt(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event, pre_cuts, reader);
    }

    std::vector<Doublet> GetDoublets(Event &event, const TMVA::Reader &reader);

    std::vector<Doublet> GetJetDoublets(Event &event, const TMVA::Reader &reader);

    std::vector<Doublet> GetJetDoublets(const Jets &jets, const TMVA::Reader &reader);

    std::vector<Doublet> GetSubJetDoublets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    std::vector<Doublet> GetDoublet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader);

    std::vector<Doublet> GetDoublet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    ZHadronicBranch GetBranch(const Doublet &doublet) const;

    int GetWHadId(Event &event) {
        return ZHadronicId(ZDaughters(event));
    };

    int SaveEntries(const std::vector<Doublet> &doublets) {
        for (const auto & doublet : doublets) static_cast<ZHadronicBranch &>(*tree_branch().NewEntry()) = GetBranch(doublet);
        return doublets.size();
    }

    TClass &Class() const {
        return *ZHadronicBranch::Class();
    }


protected:

    virtual inline std::string ClassName() const {
        return "ZHadronicTagger";
    }

private:

    Jets ZDaughters(Event &event);

    int ZHadronicId(const Jets &jets);

    void DefineVariables();

    ZHadronicBranch branch_;

    float z_mass_window_;
};

}
