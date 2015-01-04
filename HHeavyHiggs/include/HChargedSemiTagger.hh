# ifndef HChargedSemiTagger_hh
# define HChargedSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HTopHadronicTagger.hh"
# include "HChargedHiggsSemiTagger.hh"
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
    HChargedSemiTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWSemiTagger *const NewWSemiTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopSemiTagger *const NewTopSemiTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger, hanalysis::HChargedHiggsSemiTagger *const NewChargedHiggsMixedTagger);

    HChargedSemiTagger();

    /**
    * @brief Destructor
    *
    */
    ~HChargedSemiTagger();

    std::vector< HChargedSemiBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const HOctet44 &Octet);

    std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader);


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HChargedSemiTagger";
    }

private:

    void FillBranch(hheavyhiggs::HChargedSemiBranch *EventSemiBranch, const HOctet44 &Octet);

    void DefineVariables();

//     std::vector<HOctet44> GetHeavyHiggsEvents(HJets &Jets);

    hanalysis::HBottomTagger *BottomTagger;

    hanalysis::HWSemiTagger *WSemiTagger;

    hanalysis::HWTagger *WTagger;

    hanalysis::HTopSemiTagger *TopSemiTagger;

    hanalysis::HTopHadronicTagger *TopHadronicTagger;

    hanalysis::HChargedHiggsSemiTagger *ChargedHiggsSemiTagger;

    hanalysis::HReader *BottomReader;

    hanalysis::HReader *WSemiReader;

    hanalysis::HReader *WReader;

    hanalysis::HReader *TopHadronicReader;

    hanalysis::HReader *TopSemiReader;

    hanalysis::HReader *ChargedHiggsSemiReader;

    HChargedSemiBranch *Branch;

};

# endif
