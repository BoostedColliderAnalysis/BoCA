# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief W BDT tagger
 *
 */
class WHadronicTagger : public BranchTagger<WHadronicBranch>
{

public:

    WHadronicTagger();

    int Train(Event &event, const Object::Tag Tag) {
        PreCuts pre_cuts;
        return Train(event, pre_cuts, Tag);
    }

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag Tag);

    virtual int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, reader));
    }

    virtual int GetBdt(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event, pre_cuts, reader);
    }

    std::vector<Doublet> Multiplets(Event &event, const TMVA::Reader &reader);

    std::vector<Doublet> Multiplets(const Jets &jets, const TMVA::Reader &reader);


    std::vector<Doublet> Multiplet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader);

    std::vector<Doublet> Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);

    int GetWHadId(Event &event) const {
        return WHadronicId(WDaughters(event));
    }

protected:

    virtual inline std::string ClassName() const {
        return "WHadronicTagger";
    }

private:

  std::vector<analysis::Doublet> Multiplet(analysis::Doublet &doublet, const TMVA::Reader &reader);

    std::vector<Doublet> Multiplets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    Jets WDaughters(Event &event) const;

    int WHadronicId(const Jets &jets) const;

    float w_mass_window_;
};

}
