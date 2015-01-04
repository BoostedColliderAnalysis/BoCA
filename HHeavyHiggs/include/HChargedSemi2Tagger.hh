# ifndef HChargedSemi2Tagger_hh
# define HChargedSemi2Tagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HTopSemiTagger.hh"
# include "HChargedHiggsHadronicTagger.hh"
# include "HOctet44.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HChargedSemi2Tagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedSemi2Tagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWSemiTagger *const NewWSemiTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopSemiTagger *const NewTopSemiTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger, hanalysis::HChargedHiggsHadronicTagger *const NewChargedHiggsHadronicTagger);

    HChargedSemi2Tagger();

    /**
    * @brief Destructor
    *
    */
    ~HChargedSemi2Tagger();

    std::vector< HChargedSemi2Branch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const HOctet44 &Octet);

    std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader);


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HChargedSemi2Tagger";
    }

private:

    void FillBranch(hheavyhiggs::HChargedSemi2Branch *EventSemiBranch, const HOctet44 &Octet);

    void DefineVariables();

//     std::vector<HOctet44> GetHeavyHiggsEvents(HJets &Jets);

    hanalysis::HBottomTagger *BottomTagger;

    hanalysis::HWSemiTagger *WSemiTagger;

    hanalysis::HWTagger *WTagger;

    hanalysis::HTopSemiTagger *TopSemiTagger;

    hanalysis::HTopHadronicTagger *TopHadronicTagger;

    hanalysis::HChargedHiggsHadronicTagger *ChargedHiggsHadronicTagger;

    hanalysis::HReader *BottomReader;

    hanalysis::HReader *WSemiReader;

    hanalysis::HReader *WReader;

    hanalysis::HReader *TopHadronicReader;

    hanalysis::HReader *TopSemiReader;

    hanalysis::HReader *ChargedHiggsSemiReader;

    HChargedSemi2Branch *Branch;

};

# endif
