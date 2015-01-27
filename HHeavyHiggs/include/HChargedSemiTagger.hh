# ifndef HChargedSemiTagger_hh
# define HChargedSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HTopHadronicTagger.hh"
# include "HChargedHiggsSemiTagger.hh"
# include "HChargedJetPairTagger.hh"
# include "HOctet44.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HChargedSemiTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedSemiTagger();

    /**
    * @brief Destructor
    *
    */
    ~HChargedSemiTagger();

    void SetTagger(
      const hanalysis::HBottomTagger &NewBottomTagger,
      const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger,
      const hanalysis::HWSemiTagger &NewWSemiTagger,
      const hanalysis::HWTagger &NewWTagger,
      const hanalysis::HTopSemiTagger &NewTopSemiTagger,
      const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
      const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger);


    std::vector< HChargedSemiBranch > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    HChargedSemiBranch GetBranch(const HOctet44 &Octet) const;

    std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader);


    std::vector<HOctet44> GetBdt(
        const std::vector< hanalysis::HQuartet31 > &HiggsQuartets, const std::vector< hanalysis::HQuartet31 > &JetQuartets, HJets &Jets, HChargedEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader);


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HChargedSemiTagger";
    }

private:

    void DefineVariables();


    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    hanalysis::HChargedJetPairTagger ChargedJetPairTagger;

    hanalysis::HReader BottomReader;
    hanalysis::HReader WSemiReader;
    hanalysis::HReader WReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopSemiReader;
    hanalysis::HReader ChargedHiggsSemiReader;
    hanalysis::HReader ChargedJetPairReader;

    HChargedSemiBranch Branch;

};

# endif
