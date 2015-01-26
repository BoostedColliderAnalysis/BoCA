# ifndef HHeavyHiggsHadronicTagger_hh
# define HHeavyHiggsHadronicTagger_hh

# include "HSextet.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsHadronicTagger : public HMva
{

public:

    HHeavyHiggsHadronicTagger();

    HHeavyHiggsHadronicTagger(const HBottomTagger &NewBottomTagger, const HWTagger &NewWTagger, const HTopHadronicTagger &NewTopTagger);

    ~HHeavyHiggsHadronicTagger();

    std::vector<HHeavyHiggsHadronicBranch *> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const hanalysis::HSextet &Sextet);

    std::vector<hanalysis::HSextet> GetBdt(std::vector< hanalysis::HTriplet > Triplets, const hanalysis::HReader &Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsHadronicTagger";
    }

private:

    void DefineVariables();

    void FillBranch(HHeavyHiggsHadronicBranch* HeavyHiggsBranch, const hanalysis::HSextet& Sextet);

    HTag GetTag(const HSextet &Sextet);

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
