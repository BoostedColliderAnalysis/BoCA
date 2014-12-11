# ifndef HHadronicTopTagger_hh
# define HHadronicTopTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HWTagger.hh"
# include "HTriplet.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hanalysis::HHadronicTopTagger : public HMva
{

public:

    HHadronicTopTagger(HBottomTagger *NewBottomTagger, HWTagger *NewHadronicWTagger);

    ~HHadronicTopTagger();

    std::vector<HHadronicTopBranch*> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    void FillBranch(const hanalysis::HTriplet &PairJetPair);

//     std::vector<hanalysis::HTriplet> FillTriple(const fastjet::PseudoJet &Jet1,const fastjet::PseudoJet &Jet2,const fastjet::PseudoJet &Jet3);

private:

    HBottomTagger *BottomTagger;
    HWTagger *WTagger;

    HReader  *BottomReader;
    HReader  *HadronicWReader;

    HHadronicTopBranch *Branch;

    hanalysis::HJetTag *JetTag;

    void DefineVariables();

    HState GetTripleTag(const hanalysis::HDoublet &JetPair, const fastjet::PseudoJet &Jet);

    std::vector<hanalysis::HTriplet> FillTriple(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2, const fastjet::PseudoJet &Jet3, const hanalysis::HObject::HState State);

    void FillBranch(HHadronicTopBranch *LeptonicTopBranch, const hanalysis::HTriplet &PairJetPair);

    virtual inline std::string ClassName() const {
        return "HHadronicTopTagger";
    };

};

#endif
