# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

/**
 * @brief W BDT tagger
 *
 */
class hanalysis::HWHadronicTagger : public Tagger
{

public:

    HWHadronicTagger();

    int Train(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);

    std::vector< WHadronicBranch > GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag) {
        Print(kError, "train", "depreciated");
    }

    virtual int GetBdt(Event &event, const TMVA::Reader &reader) {
      return SaveEntries(GetDoublets(event, reader));
    }

    std::vector<Doublet> GetDoublets(Event &event, const TMVA::Reader &reader);

    std::vector<Doublet> GetBdt(const Jets &jets, const hanalysis::Reader &WReader, hanalysis::BottomTagger &bottom_tagger, hanalysis::Reader &BottomReader) {
        Print(kError, "train", "depreciated");
    }

    std::vector<hanalysis::Doublet> GetJetDoublets(Event &event, const TMVA::Reader &reader);
    std::vector<hanalysis::Doublet> GetJetDoublets(const Jets &jets, const TMVA::Reader &reader);

    std::vector<hanalysis::Doublet> GetSubJetDoublets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    std::vector<hanalysis::Doublet> GetDoublet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader);

    std::vector<hanalysis::Doublet> GetDoublet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);

    std::vector<Doublet> GetBdt(const Jets &jets, const hanalysis::Reader &WReader);
    std::vector<Doublet> GetPairBdt(const Jets &jets, const hanalysis::Reader &WReader);
    std::vector<Doublet> GetSingletBdt(const Jets &jets, const hanalysis::Reader &WReader);

    Doublet GetBdt(Doublet &doublet, const hanalysis::Reader &WReader);

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
        return "HHadronicWTagger";
    }

private:

    Jets GetWDaughters(hanalysis::Event &event);

    int GetWHadId(const Jets &jets);

    void DefineVariables();

    WHadronicBranch branch_;

    float w_mass_window_;
};
