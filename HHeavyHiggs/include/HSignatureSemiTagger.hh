# ifndef HSignatureSemiTagger_hh
# define HSignatureSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HJetPairTagger.hh"
# include "HOctet.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HSignatureSemiTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HSignatureSemiTagger();

    void SetTagger(
        const hanalysis::BottomTagger &NewBottomTagger,
        const hanalysis::HJetPairTagger &NewJetPairTagger,
        const hanalysis::HWSemiTagger &NewWSemiTagger,
        const hanalysis::HWHadronicTagger &NewWTagger,
        const hanalysis::HTopSemiTagger &NewTopSemiTagger,
        const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
        const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector<HOctetBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector< HOctet > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, const hanalysis::Reader &Reader);


    HOctetBranch GetBranch(const HOctet &Octet) const;

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWHadronicTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;
    hanalysis::HJetPairTagger JetPairTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WSemiReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader TopSemiReader;
    hanalysis::Reader HeavyHiggsSemiReader;
    hanalysis::Reader JetPairReader;


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

    std::vector<HOctet> GetHeavyHiggsEvents(Jets &jets);

    HOctetBranch Branch;
    hanalysis::HJetTag JetTag;

};

# endif
