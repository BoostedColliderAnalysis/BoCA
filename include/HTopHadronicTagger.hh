# ifndef HTopHadronicTagger_hh
# define HTopHadronicTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HTriplet.hh"
# include "HSextet.hh"
# include "HBottomTagger.hh"
# include "HWTagger.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hanalysis::HTopHadronicTagger : public HMva
{

public:

    HTopHadronicTagger(HBottomTagger *NewBottomTagger, HWTagger *NewHadronicWTagger);

    ~HTopHadronicTagger();

    std::vector<HTopHadronicBranch*> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    void FillBranch(const hanalysis::HTriplet &PairJetPair);

//     std::vector<hanalysis::HTriplet> FillTriple(const fastjet::PseudoJet &Jet1,const fastjet::PseudoJet &Jet2,const fastjet::PseudoJet &Jet3);

private:

    HBottomTagger *BottomTagger;
    HWTagger *WTagger;

    HReader  *BottomReader;
    HReader  *HadronicWReader;

    HTopHadronicBranch *Branch;

    hanalysis::HJetTag *JetTag;

    void DefineVariables();

    HState GetTripletTag(const hanalysis::HTriplet& Triplet);

    HState GetDoubletTag(const HDoublet &Doublet);

    HState GetSextetTag(const HSextet &Sextet);

//     std::vector<hanalysis::HTriplet> FillTriple(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2, const fastjet::PseudoJet &Jet3, const hanalysis::HObject::HState State);

    void FillBranch(HTopHadronicBranch *LeptonicTopBranch, const hanalysis::HTriplet &PairJetPair);

    virtual inline std::string ClassName() const {
        return "HTopHadronicTagger";
    };

};

#endif
