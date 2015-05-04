# ifndef HHeavyHiggsHadronicTagger_hh
# define HHeavyHiggsHadronicTagger_hh

# include "HSextet.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsHadronicTagger : public Tagger
{

public:

    HHeavyHiggsHadronicTagger();

    HHeavyHiggsHadronicTagger(const HBottomTagger &NewBottomTagger, const HWTagger &NewWTagger, const HTopHadronicTagger &NewTopTagger);

    ~HHeavyHiggsHadronicTagger();

    std::vector<HHeavyHiggsHadronicBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    HHeavyHiggsHadronicBranch GetBranch(const hanalysis::HSextet &Sextet);

    std::vector<hanalysis::HSextet> GetBdt(std::vector< hanalysis::HTriplet > Triplets, const hanalysis::HReader &Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsHadronicTagger";
    }

private:

    void DefineVariables();


    Tag GetTag(const HSextet &Sextet);

    HBottomTagger BottomTagger;
    HWTagger WTagger;
    HTopHadronicTagger TopHadronicTagger;

    HReader BottomReader;
    HReader WReader;
    HReader TopHadronicReader;

    HHeavyHiggsHadronicBranch Branch;

    HJetTag JetTag;

};

#endif
