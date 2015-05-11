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

    void SetTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger, const hanalysis::HWHadronicTagger &NewWTagger, const hanalysis::HTopSemiTagger &NewTopSemiTagger, const hanalysis::HTopHadronicTagger &NewTopHadronicTagger);

    std::vector< HHeavyHiggsSemiBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, const float pre_cut = 0);

    std::vector<hanalysis::HSextet>  GetBdt(const std::vector< Triplet > &tripletsSemi, const std::vector<Triplet > &tripletsHadronic, const Reader & Reader);

    std::vector<hanalysis::HSextet>  GetBdt(const std::vector< hanalysis::Triplet > &tripletsSemi, const std::vector< hanalysis::Triplet > &tripletsHadronic, const hanalysis::Reader & Reader, const int Mass);

    BottomTagger bottom_tagger_;
    HWHadronicTagger WTagger;
    HWSemiTagger WSemiTagger;
    HTopHadronicTagger TopHadronicTagger;
    HTopSemiTagger TopSemiTagger;

    Reader BottomReader;
    Reader WReader;
    Reader WSemiReader;
    Reader TopHadronicReader;
    Reader TopSemiReader;

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
