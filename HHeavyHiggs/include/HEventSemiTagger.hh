# ifndef HEventSemiTagger_hh
# define HEventSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HJetPairTagger.hh"
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
    HEventSemiTagger();

    HEventSemiTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HJetPairTagger *const NewJetPairTagger, hanalysis::HWSemiTagger *const NewWSemiTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopSemiTagger *const NewTopSemiTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger, hanalysis::HHeavyHiggsSemiTagger *const NewHeavyHiggsMixedTagger);

    /**
    * @brief Destructor
    *
    */
    ~HEventSemiTagger();

    std::vector<HEventSemiBranch *> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const HOctet &Octet);

    std::vector< HOctet > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, std::vector< fastjet::PseudoJet > &Jets, HEventStruct &EventStruct, const hanalysis::HReader *const EventSemiReader);

    std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader);

    void FillBranch(hheavyhiggs::HEventSemiBranch *EventSemiBranch, const HOctet &Octet);


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HHEventSemiTagger";
    }

private:

    HTag GetTag(const HOctet &Octet);

    void DefineVariables();

    std::vector<HOctet> GetHeavyHiggsEvents(HJets &Jets);

    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HWSemiTagger *WSemiTagger;
    hanalysis::HWTagger *WTagger;
    hanalysis::HTopSemiTagger *TopSemiTagger;
    hanalysis::HTopHadronicTagger *TopHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger *HeavyHiggsSemiTagger;
    hanalysis::HJetPairTagger *JetPairTagger;

    hanalysis::HReader *BottomReader;
    hanalysis::HReader *WSemiReader;
    hanalysis::HReader *WReader;
    hanalysis::HReader *TopHadronicReader;
    hanalysis::HReader *TopSemiReader;
    hanalysis::HReader *HeavyHiggsSemiReader;
    hanalysis::HReader *JetPairReader;

    HEventSemiBranch *Branch;
    hanalysis::HJetTag *JetTag;

};

# endif
