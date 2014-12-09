# ifndef HHadronicEventTagger_hh
# define HHadronicEventTagger_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HHadronicTopTagger.hh"
# include "HHeavyHiggsHadronicTagger.hh"
# include "HHeavyHiggsHadronicTagger.hh"
# include "HHeavyHiggsEvent.hh"



/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HHadronicEventTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HHadronicEventTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HHadronicTopTagger *const NewTopTagger, hanalysis::HHeavyHiggsHadronicTagger *const NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HHadronicEventTagger();

    std::vector<hheavyhiggs::HHadronicEventBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HState State);

    void FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &) {};

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *, TMVA::Reader *) {
        return 0;
    };

protected:


private:

    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    void FillBranch(hheavyhiggs::HHadronicEventBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent);

    void DefineVariables();


    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HWTagger *WTagger;
    hanalysis::HHadronicTopTagger *HadronicTopTagger;
    hanalysis::HHeavyHiggsHadronicTagger *HeavyHiggsTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *WReader;
    hanalysis::HReader *TopReader;
    hanalysis::HReader *HeavyHiggsReader;

    hheavyhiggs::HHadronicEventBranch *Branch;

    hanalysis::HJetTag *JetTag;

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HEventTagger";
    };


};

# endif
