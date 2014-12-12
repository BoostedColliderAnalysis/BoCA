# ifndef HLeptonicEventTagger_hh
# define HLeptonicEventTagger_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HHeavyHiggsLeptonicTagger.hh"
# include "HHeavyHiggsEvent.hh"



/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HEventLeptonicTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventLeptonicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HTopLeptonicTagger *const NewTopTagger, hanalysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HEventLeptonicTagger();

    std::vector<hheavyhiggs::HEventLeptonicBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HState State);

    void FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &ReaderStruct) {return ReaderStruct;}

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *, TMVA::Reader *) {
        return 0;
    };

protected:


private:

    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    void FillBranch(hheavyhiggs::HEventLeptonicBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent);

    void DefineVariables();


    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HTopLeptonicTagger *LeptonicTopTagger;
    hanalysis::HHeavyHiggsLeptonicTagger *HeavyHiggsTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *TopReader;
    hanalysis::HReader *HeavyHiggsReader;

    hheavyhiggs::HEventLeptonicBranch *Branch;

    hanalysis::HJetTag *JetTag;

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HEventTagger";
    };


};

# endif
