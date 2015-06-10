# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Multiplet.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief W BDT tagger
 *
 */
class ZHadronicTagger : public BranchTagger<ZHadronicBranch>
{

public:

    ZHadronicTagger();

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

    std::vector<Doublet> Multiplets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    std::vector<Doublet> Multiplets(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader);

    std::vector<Doublet> Multiplets(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);

    int ZHadId(Event &event) {
        return ZHadronicId(ZDaughters(event));
    };

//     TClass &Class() const {
//         return *ZHadronicBranch::Class();
//     }


protected:

    virtual inline std::string ClassName() const {
        return "ZHadronicTagger";
    }

private:

    Jets ZDaughters(Event &event);

    int ZHadronicId(const Jets &jets);

    void DefineVariables();

//     ZHadronicBranch branch_;

    float z_mass_window_;

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;
};

}
