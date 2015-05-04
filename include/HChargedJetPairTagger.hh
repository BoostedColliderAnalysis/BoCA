# ifndef HChargedJetPairTagger_hh
# define HChargedJetPairTagger_hh

# include "HBottomTagger.hh"
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

    void SetTagger(const HBottomTagger &NewBottomTagger, const HWSemiTagger &NewWSemiTagger, const HWTagger &NewWTagger, const HTopSemiTagger &NewTopSemiTagger, const HTopHadronicTagger &NewTopHadronicTagger);

    std::vector< HChargedJetPairBranch> GetBranches(HEvent &Event, const HObject::Tag Tag);

    std::vector< HQuartet31 > GetBdt(const std::vector< hanalysis::HTriplet > &Triplets, const HJets &Jets, const hanalysis::HReader &JetPairReader);

    HChargedJetPairBranch GetBranch(const hanalysis::HQuartet31 &Quartet) const;

    HBottomTagger BottomTagger;
    HWTagger WTagger;
    HWSemiTagger WSemiTagger;
    HTopHadronicTagger TopHadronicTagger;
    HTopSemiTagger TopSemiTagger;

    HReader BottomReader;
    HReader WReader;
    HReader WSemiReader;
    HReader TopHadronicReader;
    HReader TopSemiReader;

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
