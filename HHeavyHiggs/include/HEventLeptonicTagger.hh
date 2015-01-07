# ifndef HLeptonicEventTagger_hh
# define HLeptonicEventTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsLeptonicTagger.hh"
# include "HOctet.hh"

/**
 *
 * @brief Event BDT Tagger for leptonic heavy higgs
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

    HEventLeptonicTagger();

    /**
    * @brief Destructor
    *
    */
    ~HEventLeptonicTagger();

    std::vector<hheavyhiggs::HEventLeptonicBranch *> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    std::vector< int > ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader);

    void FillBranch(const HOctet &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HEventLeptonicTagger";
    };


private:

    void SetBranch(const TObject *Object) {
        (*Branch) = *((HEventLeptonicBranch *) Object);
    };

    void DefineVariables();

    void FillBranch(hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch, const HOctet &Octet);

    std::vector<HOctet> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HTopLeptonicTagger *TopLeptonicTagger;
    hanalysis::HHeavyHiggsLeptonicTagger *HeavyHiggsLeptonicTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *TopLeptonicReader;
    hanalysis::HReader *HeavyHiggsLeptonicReader;
    hheavyhiggs::HEventLeptonicBranch *Branch;

};

# endif
