# ifndef HHadronicTopTagger_hh
# define HHadronicTopTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HHadronicWTagger.hh"
# include "HPairJetPair.hh"

class HTopTriple{

    TopTriple(const hdelphes::HSuperStructure & NewJetPair, const fastjet::PseudoJet &NewBottom){
        JetPair = NewJetPair;
        Bottom = NewBottom;
    }

    hdelphes::HSuperStructure JetPair;

    fastjet::PseuodJet Bottom;

};

/**
 * @brief calculation regarding leptons
 *
 */
class hdelphes::HHadronicTopTagger : public hmva::HMva
{

public:

    HHadronicTopTagger(HBottomTagger *NewBottomTagger, HHadronicWTagger *NewHadronicWTagger);

    ~HHadronicTopTagger();

    std::vector<HLeptonicTopBranch*> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    void FillBranch(const hanalysis::HPairJetPair &PairJetPair);

    std::vector<HTopTriple> FillTriple(const fastjet::PseudoJet &Jet1,const fastjet::PseudoJet &Jet2,const fastjet::PseudoJet &Jet3);

private:

    HHadronicWTagger *HadronicWTagger;

    hmva::HReader *HadronicWReader;

    HBottomTagger *BottomTagger;

    hmva::HReader *BottomReader;

    HLeptonicTopBranch *Branch;

    hanalysis::HJetTag *JetTag;

    void DefineVariables();

    std::vector<hanalysis::HPairJetPair> FillTriple(const fastjet::PseudoJet &Jet1,const fastjet::PseudoJet &Jet2,const fastjet::PseudoJet &Jet3);


    void FillBranch(HLeptonicTopBranch *LeptonicTopBranch, const hanalysis::HJetLeptonPair &JetLeptonPair);

    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HHadronicTopTagger";
    };

};

#endif
