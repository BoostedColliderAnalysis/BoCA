# ifndef HHadronicEventTagger_hh
# define HHadronicEventTagger_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HHeavyHiggsHadronicTagger.hh"
# include "HHeavyHiggsEvent.hh"
# include "HSextet.hh"


/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HEventHadronicTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventHadronicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopHadronicTagger *const NewTopTagger, hanalysis::HHeavyHiggsHadronicTagger *const NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HEventHadronicTagger();

    std::vector<hheavyhiggs::HEventHadronicBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HState State);

    void FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &ReaderStruct) {return ReaderStruct;};

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *, TMVA::Reader *) {
        return 0;
    };

protected:


private:

    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(HJets &Jets);

    void FillBranch(hheavyhiggs::HEventHadronicBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent);

    void DefineVariables();


    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HWTagger *WTagger;
    hanalysis::HTopHadronicTagger *TopHadronicTagger;
    hanalysis::HHeavyHiggsHadronicTagger *HeavyHiggsTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *WReader;
    hanalysis::HReader *TopHadronicReader;
    hanalysis::HReader *HeavyHiggsReader;

    hheavyhiggs::HEventHadronicBranch *Branch;

    hanalysis::HJetTag *JetTag;

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HHhHadEventTagger";
    };


};

# endif
