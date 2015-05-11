# ifndef HChargedJetPairTagger_hh
# define HChargedJetPairTagger_hh

# include "BottomTagger.hh"
# include "HQuartet31.hh"
# include "HTopSemiTagger.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief JetPair BDT tagger
 *
 */
class hanalysis::HChargedJetPairTagger : public Tagger
{

public:

    HChargedJetPairTagger();

    void SetTagger(const BottomTagger &NewBottomTagger, const HWSemiTagger &NewWSemiTagger, const HWHadronicTagger &NewWTagger, const HTopSemiTagger &NewTopSemiTagger, const HTopHadronicTagger &NewTopHadronicTagger);

    std::vector< HChargedJetPairBranch> GetBranches(HEvent &Event, const HObject::Tag Tag);

    std::vector< HQuartet31 > GetBdt(const std::vector< hanalysis::Triplet > &triplets, const Jets &jets, const hanalysis::Reader &JetPairReader);

    HChargedJetPairBranch GetBranch(const hanalysis::HQuartet31 &Quartet) const;

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
