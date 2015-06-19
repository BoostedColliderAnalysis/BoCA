# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

namespace analysis
{

/**
 * @brief W BDT tagger
 *
 */
class WHadronicTagger : public BranchTagger<WHadronicBranch>
{

public:

    WHadronicTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag Tag);

    virtual int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::vector<Doublet> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    std::vector<Doublet> Multiplets(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader);


    Doublet Multiplet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader);

    Doublet Multiplet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplet(jet_1, jet_2, pre_cuts, reader);
    }

    Doublet SubMultiplet(const fastjet::PseudoJet &jet, PreCuts &pre_cuts, const TMVA::Reader &reader);

    Doublet Multiplet(const fastjet::PseudoJet &jet, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader);

    Doublet Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplet(jet, pre_cuts, reader);
    }

    Doublet SubMultiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return SubMultiplet(jet, pre_cuts, reader);
    }

    int GetWHadId(Event &event) const {
        return WHadronicId(WDaughters(event));
    }

protected:

    virtual inline std::string ClassName() const {
        return "WHadronicTagger";
    }

private:

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Object::Tag tag);

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts);

    Doublet Multiplet(analysis::Doublet &doublet, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader);

    std::vector<Doublet> SubMultiplets(const analysis::Jets &jets, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader, const int sub_jet_number);

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    Jets WDaughters(Event &event) const;

    int WHadronicId(const Jets &jets) const;

    float w_mass_window_;
};

}
