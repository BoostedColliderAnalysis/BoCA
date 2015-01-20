# ifndef HHeavyHiggsSemiTagger_hh
# define HHeavyHiggsSemiTagger_hh

# include "HSextet.hh"
# include "HTopSemiTagger.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class hanalysis::HHeavyHiggsSemiTagger : public HMva
{

public:

  HHeavyHiggsSemiTagger(HBottomTagger *const NewBottomTagger, HWSemiTagger *const NewSemiWTagger, HWTagger *const NewWTagger, HTopSemiTagger *const NewTopSemiTagger, HTopHadronicTagger *const NewTopHadronicTagger);

    ~HHeavyHiggsSemiTagger();

    std::vector<HHeavyHiggsSemiBranch *> GetBranches(HEvent *const Event, const HObject::HTag State);

    void FillBranch(const HSextet& Sextet);

    std::vector<hanalysis::HSextet>  GetBdt(const std::vector< hanalysis::HTriplet > &TripletsSemi, const std::vector< hanalysis::HTriplet > &TripletsHadronic, const hanalysis::HReader *const Reader);

//     std::vector<hanalysis::HSextet>  GetSextets(const HReader *const Reader);



//     HBottomTagger *BottomTagger;
//     HWTagger *WTagger;
    HWSemiTagger *WSemiTagger;
    HTopHadronicTagger *TopHadronicTagger;
    HTopSemiTagger *TopSemiTagger;
//     HReader *BottomReader;
//     HReader *WReader;
    HReader *WSemiReader;
    HReader *TopHadronicReader;
    HReader *TopSemiReader;


    void FillBranch(HHeavyHiggsSemiBranch* HeavyHiggsBranch, const hanalysis::HSextet& Sextet);


protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsSemiTagger";
    }

private:

    void DefineVariables();

    HTag GetTag(const HSextet &Sextet, const float Mass);

    HTag GetTag(const HSextet &Sextet);

    HJetTag *JetTag;
    HHeavyHiggsSemiBranch *Branch;
};

#endif
