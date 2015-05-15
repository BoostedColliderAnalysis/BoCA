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

    int Train(hanalysis::Event &event, const hanalysis::HObject::Tag Tag) {
        PreCuts pre_cuts;
        return Train(event, pre_cuts, Tag);
    }

    int Train(hanalysis::Event &event, PreCuts &pre_cuts, const hanalysis::HObject::Tag Tag);

    std::vector< WHadronicBranch > GetBranches(hanalysis::Event &, const hanalysis::HObject::Tag) {
        Print(kError, "train", "depreciated");
        return std::vector< WHadronicBranch >{};
    }

    virtual int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(GetDoublets(event, reader));
    }

    virtual int GetBdt(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event, pre_cuts, reader);
    }

    std::vector<Doublet> GetDoublets(Event &event, const TMVA::Reader &reader);

    std::vector<Doublet> GetBdt(const Jets &, const hanalysis::Reader &, hanalysis::BottomTagger &, hanalysis::Reader &) {
        Print(kError, "train", "depreciated");
        return std::vector<Doublet>{};
    }

    std::vector<hanalysis::Doublet> GetJetDoublets(Event &event, const TMVA::Reader &reader);

    std::vector<hanalysis::Doublet> GetJetDoublets(const Jets &jets, const TMVA::Reader &reader);

    std::vector<hanalysis::Doublet> GetSubJetDoublets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    std::vector<hanalysis::Doublet> GetDoublet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader);

    std::vector<hanalysis::Doublet> GetDoublet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);

    std::vector<Doublet> GetBdt(const Jets &, const hanalysis::Reader &) {
        Print(kError, "gete bdt", "depreciated");
        return std::vector<Doublet>{};
    }

    std::vector<Doublet> GetPairBdt(const Jets &, const hanalysis::Reader &) {
        Print(kError, "gete bdt", "depreciated");
        return std::vector<Doublet>{};
    }

    std::vector<Doublet> GetSingletBdt(const Jets &, const hanalysis::Reader &) {
        Print(kError, "gete bdt", "depreciated");
        return std::vector<Doublet>{};
    }

    Doublet GetBdt(Doublet &, const hanalysis::Reader &) {
        Print(kError, "gete bdt", "depreciated");
        return Doublet();
    }

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    WHadronicBranch GetBranch(const Doublet &doublet) const;

    int GetWHadId(hanalysis::Event &event) {
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
        return "WHadronicTagger";
    }

private:

    Jets GetWDaughters(hanalysis::Event &event);

    int GetWHadId(const Jets &jets);

    void DefineVariables();

    WHadronicBranch branch_;

    float w_mass_window_;
};
