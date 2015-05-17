# ifndef HHeavyHiggsHadronicTagger_hh
# define HHeavyHiggsHadronicTagger_hh

# include "HSextet.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class analysis::HHeavyHiggsHadronicTagger : public Tagger
{

public:

    HHeavyHiggsHadronicTagger();

    HHeavyHiggsHadronicTagger(const BottomTagger &NewBottomTagger, const WHadronicTagger &NewWTagger, const TopHadronicTagger &NewTopTagger);

    ~HHeavyHiggsHadronicTagger();

    std::vector<HHeavyHiggsHadronicBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    HHeavyHiggsHadronicBranch GetBranch(const analysis::HSextet &Sextet);

    std::vector<analysis::HSextet> GetBdt(std::vector< analysis::Triplet > triplets, const analysis::Reader &Reader);

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
