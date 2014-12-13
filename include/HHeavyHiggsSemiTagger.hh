# ifndef HHeavyHiggsSemiTagger_hh
# define HHeavyHiggsSemiTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HDoublet.hh"
# include "HQuartet.hh"
# include "HTopSemiTagger.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsSemiTagger : public HMva
{

public:

    HHeavyHiggsSemiTagger(HBottomTagger *const NewBottomTagger, HWTagger *const NewWTagger, HTopSemiTagger *const NewTopSemiTagger, HTopHadronicTagger *const NewTopHadronicTagger);

    ~HHeavyHiggsSemiTagger();

    std::vector<HHeavyHiggsSemiBranch *> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const HSextet& TriplePair);

    std::vector<hanalysis::HSextet>  GetHeavyHiggsSemiBdt(std::vector<HTriplet> TripletsSemi ,std::vector<HTriplet> TripletsHadronic, const HReader *const HeavyHiggsSemiReader, const HState State);


private:

    HSextet GetTriplePair(HJets &Jets, fastjet::PseudoJet Lepton,fastjet::PseudoJet MissingEt,const HObject::HState State);

    HBottomTagger *BottomTagger;
    HWTagger *WTagger;
    HTopHadronicTagger *TopHadronicTagger;
    HTopSemiTagger *TopSemiTagger;

    HReader *BottomReader;
    HReader *WReader;
    HReader *TopHadronicReader;
    HReader *TopSemiReader;

    HHeavyHiggsSemiBranch *Branch;

    HJetTag *JetTag;
    HState GetSextetTag(const HSextet &Sextet);

    void DefineVariables();

    void FillBranch(HHeavyHiggsSemiBranch* HeavyHiggsBranch, const hanalysis::HSextet& TriplePair);

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsSemiTagger";
    };

};

#endif
