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
class analysis::HChargedJetPairTagger : public Tagger
{

public:

    HChargedJetPairTagger();

    void SetTagger(const BottomTagger &NewBottomTagger, const HWSemiTagger &NewWSemiTagger, const WHadronicTagger &NewWTagger, const HTopSemiTagger &NewTopSemiTagger, const TopHadronicTagger &Newtop_hadronic_tagger);

    std::vector< HChargedJetPairBranch> GetBranches(Event &event, const Object::Tag Tag);

    std::vector< HQuartet31 > GetBdt(const std::vector< analysis::Triplet > &triplets, const Jets &jets, const analysis::Reader &JetPairReader);

    HChargedJetPairBranch GetBranch(const analysis::HQuartet31 &Quartet) const;

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

    analysis::Object::Tag GetTag(const analysis::HQuartet31 &Quartet);

    HChargedJetPairBranch Branch;

    HJetTag JetTag;

};

#endif
