# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

/**
 * @brief W BDT tagger
 *
 */
class hanalysis::WHadronicTagger : public Tagger
{

public:

    WHadronicTagger();

    int Train(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag) {
        PreCuts pre_cuts;
        return Train(Event, pre_cuts, Tag);
    }

    int Train(hanalysis::HEvent &Event, PreCuts &pre_cuts, const hanalysis::HObject::Tag Tag);

    std::vector< WHadronicBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag) {
        Print(kError, "train", "depreciated");
    }

    virtual int GetBdt(HEvent &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(GetDoublets(event, reader));
    }

    virtual int GetBdt(HEvent &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event, pre_cuts, reader);
    }

    std::vector<Doublet> GetDoublets(HEvent &event, const TMVA::Reader &reader);

    std::vector<Doublet> GetBdt(const Jets &jets, const hanalysis::Reader &WReader, hanalysis::BottomTagger &bottom_tagger, hanalysis::Reader &BottomReader) {
        Print(kError, "train", "depreciated");
    }

    std::vector<hanalysis::Doublet> GetJetDoublets(HEvent &event, const TMVA::Reader &reader);
    std::vector<hanalysis::Doublet> GetJetDoublets(const Jets &jets, const TMVA::Reader &reader);

    std::vector<hanalysis::Doublet> GetSubJetDoublets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    std::vector<hanalysis::Doublet> GetDoublet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader);

    std::vector<hanalysis::Doublet> GetDoublet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);

    std::vector<Doublet> GetBdt(const Jets &jets, const hanalysis::Reader &WReader) {
        Print(kError, "gete bdt", "depreciated");
    }

    std::vector<Doublet> GetPairBdt(const Jets &jets, const hanalysis::Reader &WReader) {
        Print(kError, "gete bdt", "depreciated");
    }

    std::vector<Doublet> GetSingletBdt(const Jets &jets, const hanalysis::Reader &WReader) {
        Print(kError, "gete bdt", "depreciated");
    }

    Doublet GetBdt(Doublet &doublet, const hanalysis::Reader &WReader) {
        Print(kError, "gete bdt", "depreciated");
    }

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    WHadronicBranch GetBranch(const Doublet &doublet) const;

    int GetWHadId(hanalysis::HEvent &event) {
        return GetWHadId(GetWDaughters(event));
    };

    int SaveEntries(const std::vector<Doublet> &doublets) {
        for (const auto & doublet : doublets) static_cast<WHadronicBranch &>(*tree_branch().NewEntry()) = GetBranch(doublet);
        return doublets.size();
    }

    TClass &Class() const {
        return *WHadronicBranch::Class();
    }


protected:

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    }

private:

    Jets GetWDaughters(hanalysis::HEvent &event);

    int GetWHadId(const Jets &jets);

    void DefineVariables();

    WHadronicBranch branch_;

    float w_mass_window_;
};
