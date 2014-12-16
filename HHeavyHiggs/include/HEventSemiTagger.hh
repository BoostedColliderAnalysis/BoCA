# ifndef HEventSemiTagger_hh
# define HEventSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HOctet.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HEventSemiTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventSemiTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopSemiTagger *const NewTopLeptonicTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger, hanalysis::HHeavyHiggsSemiTagger *const NewHeavyHiggsMixedTagger);

    /**
    * @brief Destructor
    *
    */
    ~HEventSemiTagger();

    std::vector<HEventSemiBranch *> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const HOctet &Octet);

    std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader);


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HHhEventSemiTagger";
    }

private:

    void FillBranch(hheavyhiggs::HEventSemiBranch *EventSemiBranch, const HOctet &Octet);

    void DefineVariables();

    std::vector<HOctet> GetHeavyHiggsEvents(HJets &Jets);

    hanalysis::HBottomTagger *BottomTagger;

    hanalysis::HWTagger *WTagger;

    hanalysis::HTopSemiTagger *TopSemiTagger;

    hanalysis::HTopHadronicTagger *TopHadronicTagger;

    hanalysis::HHeavyHiggsSemiTagger *HeavyHiggsSemiTagger;

    hanalysis::HReader *BottomReader;

    hanalysis::HReader *WReader;

    hanalysis::HReader *TopHadronicReader;

    hanalysis::HReader *TopSemiReader;

    hanalysis::HReader *HeavyHiggsSemiReader;

    HEventSemiBranch *Branch;

};

# endif
