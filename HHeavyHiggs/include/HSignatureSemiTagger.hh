# ifndef HSignatureSemiTagger_hh
# define HSignatureSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HJetPairTagger.hh"
# include "HOctet.hh"

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HSignatureSemiTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HSignatureSemiTagger();

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger,
        const analysis::HJetPairTagger &NewJetPairTagger,
        const analysis::HWSemiTagger &NewWSemiTagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::HTopSemiTagger &NewTopSemiTagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector<HOctetBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< HOctet > GetBdt(const std::vector< analysis::HSextet > &Sextets, const std::vector< analysis::Doublet > &doublets, const analysis::Reader &Reader);


    HOctetBranch GetBranch(const HOctet &Octet) const;

    analysis::BottomTagger bottom_tagger_;
    analysis::HWSemiTagger WSemiTagger;
    analysis::WHadronicTagger WTagger;
    analysis::HTopSemiTagger TopSemiTagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;
    analysis::HJetPairTagger JetPairTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader HeavyHiggsSemiReader;
    analysis::Reader JetPairReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HSignatureSemiTagger";
    }

private:

    Tag GetTag(const HOctet &);

    void DefineVariables();

    std::vector<HOctet> GetHeavyHiggsevents(Jets &jets);

    HOctetBranch Branch;
    analysis::HJetTag JetTag;

};

# endif
