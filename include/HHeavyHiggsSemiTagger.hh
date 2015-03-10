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

    HHeavyHiggsSemiTagger();
    
    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger, const hanalysis::HWTagger &NewWTagger, const hanalysis::HTopSemiTagger &NewTopSemiTagger, const hanalysis::HTopHadronicTagger &NewTopHadronicTagger);

    std::vector< HHeavyHiggsSemiBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);

    std::vector<hanalysis::HSextet>  GetBdt(const std::vector< hanalysis::HTriplet > &TripletsSemi, const std::vector< hanalysis::HTriplet > &TripletsHadronic, const hanalysis::HReader & Reader);

    HBottomTagger BottomTagger;
    HWTagger WTagger;
    HWSemiTagger WSemiTagger;
    HTopHadronicTagger TopHadronicTagger;
    HTopSemiTagger TopSemiTagger;

    HReader BottomReader;
    HReader WReader;
    HReader WSemiReader;
    HReader TopHadronicReader;
    HReader TopSemiReader;

    HHeavyHiggsSemiBranch GetBranch(const hanalysis::HSextet& Sextet) const;


protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsSemiTagger";
    }

private:

    void DefineVariables();

    HTag GetTag(const HSextet &Sextet);

    HJetTag JetTag;
    HHeavyHiggsSemiBranch Branch;
};

#endif
