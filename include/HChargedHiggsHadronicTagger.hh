# ifndef HChargedHiggsHadronicTagger_hh
# define HChargedHiggsHadronicTagger_hh

# include "Quartet31.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class analysis::HChargedHiggsHadronicTagger : public Tagger
{

public:

  HChargedHiggsHadronicTagger();

    HChargedHiggsHadronicTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::WHadronicTagger &NewWTagger, const analysis::TopHadronicTagger &NewTopTagger);

    ~HChargedHiggsHadronicTagger();

    std::vector<HChargedHiggsHadronicBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    HChargedHiggsHadronicBranch GetBranch(const analysis::Quartet31 &quartet);

    std::vector< Quartet31 > GetBdt(std::vector< analysis::Triplet >& triplets, Jets& jets, const analysis::Reader& Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsHadronicTagger";
    }

private:

    void DefineVariables();


    Tag GetTag(const analysis::Quartet31 &quartet);

    BottomTagger bottom_tagger_;
    WHadronicTagger WTagger;
    TopHadronicTagger top_hadronic_tagger;

    Reader BottomReader;
    Reader WReader;
    Reader TopHadronicReader;

    HChargedHiggsHadronicBranch Branch;
    HJetTag JetTag;

};

#endif
