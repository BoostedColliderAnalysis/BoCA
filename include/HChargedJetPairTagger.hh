# ifndef HChargedJetPairTagger_hh
# define HChargedJetPairTagger_hh

# include "BottomTagger.hh"
# include "HQuartet31.hh"
# include "HTopSemiTagger.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief JetPair BDT tagger
 *
 */
class hanalysis::HChargedJetPairTagger : public Tagger
{

public:

    HChargedJetPairTagger();

    void SetTagger(const BottomTagger &NewBottomTagger, const HWSemiTagger &NewWSemiTagger, const WHadronicTagger &NewWTagger, const HTopSemiTagger &NewTopSemiTagger, const TopHadronicTagger &Newtop_hadronic_tagger);

    std::vector< HChargedJetPairBranch> GetBranches(HEvent &Event, const HObject::Tag Tag);

    std::vector< HQuartet31 > GetBdt(const std::vector< hanalysis::Triplet > &triplets, const Jets &jets, const hanalysis::Reader &JetPairReader);

    HChargedJetPairBranch GetBranch(const hanalysis::HQuartet31 &Quartet) const;

    BottomTagger bottom_tagger_;
    WHadronicTagger WTagger;
    HWSemiTagger WSemiTagger;
    TopHadronicTagger top_hadronic_tagger;
    HTopSemiTagger TopSemiTagger;

    Reader BottomReader;
    Reader WReader;
    Reader WSemiReader;
    Reader TopHadronicReader;
    Reader TopSemiReader;

protected:

    virtual inline std::string ClassName() const {
        return "HChargedJetPairTagger";
    }

private:

    void DefineVariables();

    hanalysis::HObject::Tag GetTag(const hanalysis::HQuartet31 &Quartet);

    HChargedJetPairBranch Branch;

    HJetTag JetTag;

};

#endif
