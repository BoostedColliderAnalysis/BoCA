# ifndef HMixedEventTagger_hh
# define HMixedEventTagger_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HHadronicTopTagger.hh"
# include "HTopLeptonicTagger.hh"
# include "HHeavyHiggsMixedTagger.hh"
# include "HHeavyHiggsEvent.hh"



/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HMixedEventTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HMixedEventTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HHadronicTopTagger *const NewTopHadronicTagger, hanalysis::HTopLeptonicTagger *const NewTopLeptonicTagger, hanalysis::HHeavyHiggsMixedTagger *const NewHeavyHiggsMixedTagger);

    /**
    * @brief Destructor
    *
    */
    ~HMixedEventTagger();

    std::vector<hheavyhiggs::HMixedEventBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HState State);

    void FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &) {};

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *, TMVA::Reader *) {
        return 0;
    };

protected:


private:

    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(HJets &Jets);

    void FillBranch(hheavyhiggs::HMixedEventBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent);

    void DefineVariables();


    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HWTagger *WTagger;
    hanalysis::HHadronicTopTagger *TopHadronicTagger;
    hanalysis::HTopLeptonicTagger *TopLeptonicTagger;
    hanalysis::HHeavyHiggsMixedTagger *HeavyHiggsTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *WReader;
    hanalysis::HReader *TopHadronicReader;
    hanalysis::HReader *TopLeptonicReader;
    hanalysis::HReader *HeavyHiggsReader;

    hheavyhiggs::HMixedEventBranch *Branch;

    hanalysis::HJetTag *JetTag;

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HHhMixEventTagger";
    };


};

# endif
