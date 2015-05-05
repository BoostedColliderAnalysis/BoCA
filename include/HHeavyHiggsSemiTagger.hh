# ifndef HHeavyHiggsSemiTagger_hh
# define HHeavyHiggsSemiTagger_hh

# include "HSextet.hh"
# include "HTopSemiTagger.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class hanalysis::HHeavyHiggsSemiTagger : public Tagger
{

public:

    HHeavyHiggsSemiTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger, const hanalysis::HWHadronicTagger &NewWTagger, const hanalysis::HTopSemiTagger &NewTopSemiTagger, const hanalysis::HTopHadronicTagger &NewTopHadronicTagger);

    std::vector< HHeavyHiggsSemiBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, const float pre_cut = 0);

    std::vector<hanalysis::HSextet>  GetBdt(const std::vector< HTriplet > &TripletsSemi, const std::vector<HTriplet > &TripletsHadronic, const HReader & Reader);

    std::vector<hanalysis::HSextet>  GetBdt(const std::vector< hanalysis::HTriplet > &TripletsSemi, const std::vector< hanalysis::HTriplet > &TripletsHadronic, const hanalysis::HReader & Reader, const int Mass);

    HBottomTagger BottomTagger;
    HWHadronicTagger WTagger;
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

    Tag GetTag(const HSextet &Sextet);

    HJetTag JetTag;
    HHeavyHiggsSemiBranch Branch;
};

#endif
