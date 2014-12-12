# ifndef HMixedEventTagger_hh
# define HMixedEventTagger_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HHeavyHiggsEvent.hh"



/**
 *
 * @brief Prepares multivariant analysis
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

    std::vector<HEventSemiBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HState State);

    void FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &ReaderStruct) {return ReaderStruct;};

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *, TMVA::Reader *) {
        return 0;
    };

protected:


private:

    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(HJets &Jets);

    void FillBranch(HEventSemiBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent);

    void DefineVariables();


    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HWTagger *WTagger;
    hanalysis::HTopSemiTagger *TopSemiTagger;
    hanalysis::HTopHadronicTagger *TopHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger *HeavyHiggsTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *WReader;
    hanalysis::HReader *TopHadronicReader;
    hanalysis::HReader *TopLeptonicReader;
    hanalysis::HReader *HeavyHiggsReader;

    HEventSemiBranch *Branch;

    hanalysis::HJetTag *JetTag;

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HHhMixEventTagger";
    };


};

# endif
