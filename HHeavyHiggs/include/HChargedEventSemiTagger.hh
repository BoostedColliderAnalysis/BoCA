# ifndef HChargedEventSemiTagger_hh
# define HChargedEventSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HOctet44Event.hh"
# include "HChargedSignatureSemiTagger.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HChargedEventSemiTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedEventSemiTagger();

    /**
    * @brief Destructor
    *
    */
    ~HChargedEventSemiTagger();

    void SetTagger(
        const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger, const hanalysis::HWSemiTagger &NewWSemiTagger, const hanalysis::HWTagger &NewWTagger, const hanalysis::HTopSemiTagger &NewTopSemiTagger, const hanalysis::HTopHadronicTagger &NewTopHadronicTagger, const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger, const hheavyhiggs::HChargedSignatureSemiTagger &NewChargedSignatureTagger);


    std::vector< HChargedSemiBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);

    HChargedSemiBranch GetBranch(const HEventMultiplet<HOctet44> &Event) const;

    std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);


    std::vector<HEventMultiplet<HOctet44>> GetBdt(
        const std::vector< HOctet44 > &Octets, HJets &Jets, HJets &Leptons, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader);


    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    hanalysis::HChargedJetPairTagger ChargedJetPairTagger;
    HChargedSignatureSemiTagger SignatureSemiTagger;

    hanalysis::HReader BottomReader;
    hanalysis::HReader WSemiReader;
    hanalysis::HReader WReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopSemiReader;
    hanalysis::HReader ChargedHiggsSemiReader;
    hanalysis::HReader ChargedJetPairReader;
    hanalysis::HReader SignatureSemiReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
      return "HChargedEventSemiTagger";
    }

private:

    void DefineVariables();

    HChargedSemiBranch Branch;

};

# endif
