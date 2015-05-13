# ifndef HChargedHiggsHadronicTagger_hh
# define HChargedHiggsHadronicTagger_hh

# include "HQuartet31.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HChargedHiggsHadronicTagger : public Tagger
{

public:

  HChargedHiggsHadronicTagger();

    HChargedHiggsHadronicTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::WHadronicTagger &NewWTagger, const hanalysis::TopHadronicTagger &NewTopTagger);

    ~HChargedHiggsHadronicTagger();

    std::vector<HChargedHiggsHadronicBranch> GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);

    HChargedHiggsHadronicBranch GetBranch(const hanalysis::HQuartet31 &Quartet);

    std::vector< HQuartet31 > GetBdt(std::vector< hanalysis::Triplet >& triplets, Jets& jets, const hanalysis::Reader& Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsHadronicTagger";
    }

private:

    void DefineVariables();


    Tag GetTag(const hanalysis::HQuartet31 &Quartet);

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
