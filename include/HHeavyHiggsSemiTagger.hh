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

    HHeavyHiggsSemiTagger(HBottomTagger *const NewBottomTagger, HWTagger *const NewWTagger, HTopSemiTagger *const NewTopSemiTagger, HTopHadronicTagger *const NewTopHadronicTagger);

    ~HHeavyHiggsSemiTagger();

    std::vector<HHeavyHiggsSemiBranch *> GetBranches(HEvent *const Event, const HObject::HTag State);

    void FillBranch(const HSextet& Sextet);

    std::vector<hanalysis::HSextet>  GetBdt(std::vector< hanalysis::HTriplet > TripletsSemi, std::vector< hanalysis::HTriplet > TripletsHadronic, const hanalysis::HReader *const Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsSemiTagger";
    };

private:

    void DefineVariables();

    void FillBranch(HHeavyHiggsSemiBranch* HeavyHiggsBranch, const hanalysis::HSextet& Sextet);

    HTag GetTag(const HSextet &Sextet);

    HJetTag *JetTag;

    HBottomTagger *BottomTagger;

    HWTagger *WTagger;

    HTopHadronicTagger *TopHadronicTagger;

    HTopSemiTagger *TopSemiTagger;

    HReader *BottomReader;

    HReader *WReader;

    HReader *TopHadronicReader;

    HReader *TopSemiReader;

    HHeavyHiggsSemiBranch *Branch;
};

#endif
