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
class hheavyhiggs::HSignatureSemiTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HSignatureSemiTagger();

    /**
    * @brief Destructor
    *
    */
    ~HSignatureSemiTagger();

    void SetTagger(
        const hanalysis::HBottomTagger &NewBottomTagger,
        const hanalysis::HJetPairTagger &NewJetPairTagger,
        const hanalysis::HWSemiTagger &NewWSemiTagger,
        const hanalysis::HWTagger &NewWTagger,
        const hanalysis::HTopSemiTagger &NewTopSemiTagger,
        const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
        const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector<HOctetBranch> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    std::vector< HOctet > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, const hanalysis::HReader &Reader);

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);

    HOctetBranch GetBranch(const HOctet &Octet) const;

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;
    hanalysis::HJetPairTagger JetPairTagger;

    hanalysis::HReader BottomReader;
    hanalysis::HReader WSemiReader;
    hanalysis::HReader WReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopSemiReader;
    hanalysis::HReader HeavyHiggsSemiReader;
    hanalysis::HReader JetPairReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HSignatureSemiTagger";
    }

private:

    HTag GetTag(const HOctet &Octet);

    void DefineVariables();

    std::vector<HOctet> GetHeavyHiggsEvents(HJets &Jets);

    HOctetBranch Branch;
    hanalysis::HJetTag JetTag;

};

# endif