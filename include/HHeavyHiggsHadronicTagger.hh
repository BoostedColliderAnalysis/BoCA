# ifndef HHeavyHiggsHadronicTagger_hh
# define HHeavyHiggsHadronicTagger_hh

# include "HSextet.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsHadronicTagger : public Tagger
{

public:

    HHeavyHiggsHadronicTagger();

    HHeavyHiggsHadronicTagger(const BottomTagger &NewBottomTagger, const WHadronicTagger &NewWTagger, const TopHadronicTagger &NewTopTagger);

    ~HHeavyHiggsHadronicTagger();

    std::vector<HHeavyHiggsHadronicBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    HHeavyHiggsHadronicBranch GetBranch(const hanalysis::HSextet &Sextet);

    std::vector<hanalysis::HSextet> GetBdt(std::vector< hanalysis::Triplet > triplets, const hanalysis::Reader &Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsHadronicTagger";
    }

private:

    void DefineVariables();


    Tag GetTag(const HSextet &Sextet);

    BottomTagger bottom_tagger_;
    WHadronicTagger WTagger;
    TopHadronicTagger top_hadronic_tagger;

    Reader BottomReader;
    Reader WReader;
    Reader TopHadronicReader;

    HHeavyHiggsHadronicBranch Branch;

    HJetTag JetTag;

};

#endif
