# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief W BDT tagger
 *
 */
// template <typename DoubletBranch>
class DoubletTagger : public BranchTagger<DoubletBranch>
{

public:

    DoubletTagger();

    int Train(Event &event, const Tag Tag) {
        PreCuts pre_cuts;
        return Train(event, pre_cuts, Tag);
    }

    int Train(Event &event, PreCuts &pre_cuts, const Tag Tag);

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

protected:

    virtual  std::string ClassName() const {
        return "DoubletTagger";
    }

private:

  std::vector<analysis::Doublet> Multiplet(analysis::Doublet &doublet, const TMVA::Reader &reader);

    std::vector<Doublet> Multiplets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

//     TClass &Class() const {
//         return *DoubletBranch::Class();
//     }

    void DefineVariables();

    DoubletBranch branch_;

    float doublet_mass_window_;
};

}
