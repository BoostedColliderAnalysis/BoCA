# ifndef HChargedHadronicTagger_hh
# define HChargedHadronicTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HChargedHiggsHadronicTagger.hh"
# include "HOctet44.hh"

/**
 *
 * @brief Event BDT tagger for hadronic heavy higgs
 *
 */
class hheavyhiggs::HChargedHadronicTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedHadronicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopHadronicTagger *const NewTopTagger, hanalysis::HChargedHiggsHadronicTagger *const NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HChargedHadronicTagger();

    std::vector<hheavyhiggs::HChargedHadronicBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag);

    void FillBranch(const HOctet44 &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HChargedHadronicTagger";
    };


private:

  void FillBranch(hheavyhiggs::HChargedHadronicBranch *EventHadronicBranch, const HOctet44 &Octet);

    void DefineVariables();

    hanalysis::HBottomTagger *BottomTagger;

    hanalysis::HWTagger *WTagger;

    hanalysis::HTopHadronicTagger *TopHadronicTagger;

    hanalysis::HChargedHiggsHadronicTagger *ChargedHiggsHadronicTagger;

    hanalysis::HReader *BottomReader;

    hanalysis::HReader *WReader;

    hanalysis::HReader *TopHadronicReader;

    hanalysis::HReader *ChargedHiggsHadronicReader;

    hheavyhiggs::HChargedHadronicBranch *Branch;

};

# endif
