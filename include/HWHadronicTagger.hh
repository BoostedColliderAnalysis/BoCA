# pragma once

# include "BottomTagger.hh"
# include "HDoublet.hh"
# include "Reader.hh"

/**
 * @brief W BDT tagger
 *
 */
class hanalysis::HWHadronicTagger : public Tagger
{

public:

    HWHadronicTagger();

    int Train(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector< HWBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag) {
        Print(HError, "train", "depreciated");
    }

    virtual int GetBdt(HEvent &event, const TMVA::Reader &reader) {
      return SaveEntries(GetDoublets(event, reader));
    }


//     std::vector<HParticleBranch> GetConstituentBranches();

    std::vector<HDoublet> GetDoublets(HEvent &event, const TMVA::Reader &reader);

    std::vector<HDoublet> GetBdt(const HJets &Jets, const hanalysis::Reader &WReader, hanalysis::BottomTagger &bottom_tagger, hanalysis::Reader &BottomReader) {
        Print(HError, "train", "depreciated");
    }

    std::vector<HDoublet> GetBdt(const HJets &Jets, const hanalysis::Reader &WReader);
    std::vector<HDoublet> GetPairBdt(const HJets &Jets, const hanalysis::Reader &WReader);
    std::vector<HDoublet> GetSingletBdt(const HJets &Jets, const hanalysis::Reader &WReader);

    HDoublet GetBdt(HDoublet &Doublet, const hanalysis::Reader &WReader);

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    HWBranch GetBranch(const HDoublet &Doublet) const;

    int GetWHadId(hanalysis::HEvent &Event) {
        return GetWHadId(GetWDaughters(Event));
    };

    int SaveEntries(const std::vector<HDoublet> &doublets) {
        for (const auto & doublet : doublets) static_cast<HWBranch &>(*tree_branch().NewEntry()) = GetBranch(doublet);
        return doublets.size();
    }

    TClass &Class() const {
        return *HWBranch::Class();
    }


protected:

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    }

private:

    HJets GetWDaughters(hanalysis::HEvent &Event);

    int GetWHadId(const HJets &Jets);

    void DefineVariables();

    HWBranch branch_;

    float w_mass_window_;
};
