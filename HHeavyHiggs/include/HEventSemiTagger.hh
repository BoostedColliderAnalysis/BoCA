# ifndef HEventSemiTagger_hh
# define HEventSemiTagger_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HOctet.hh"



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

    void FillBranch(const HOctet &HeavyHiggsEvent);


protected:


private:

    std::vector<HOctet> GetHeavyHiggsEvents(HJets &Jets);

    void FillBranch(HEventSemiBranch *EventBranch, const HOctet &HeavyHiggsEvent);

    void DefineVariables();


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

    hanalysis::HJetTag *JetTag;

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HHhEventSemiTagger";
    };


};

# endif
