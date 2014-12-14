# ifndef HHadronicEventTagger_hh
# define HHadronicEventTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsHadronicTagger.hh"
# include "HOctet.hh"

/**
 *
 * @brief Event BDT tagger for hadronic heavy higgs
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

    std::vector<hheavyhiggs::HEventHadronicBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag);

    void FillBranch(const HOctet &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HHhHadEventTagger";
    };


private:

    void FillBranch(hheavyhiggs::HEventHadronicBranch *EventHadronicBranch, const HOctet &Octet);

    void DefineVariables();

    hanalysis::HBottomTagger *BottomTagger;

    hanalysis::HWTagger *WTagger;

    hanalysis::HTopHadronicTagger *TopHadronicTagger;

    hanalysis::HHeavyHiggsHadronicTagger *HeavyHiggsHadronicTagger;

    hanalysis::HReader *BottomReader;

    hanalysis::HReader *WReader;

    hanalysis::HReader *TopHadronicReader;

    hanalysis::HReader *HeavyHiggsHadronicReader;

    hheavyhiggs::HEventHadronicBranch *Branch;

};

# endif
