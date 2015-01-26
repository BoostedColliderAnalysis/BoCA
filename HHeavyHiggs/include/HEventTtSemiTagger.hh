# ifndef HEventTtSemiTagger_hh
# define HEventTtSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HSextet.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HEventTtSemiTagger : public hanalysis::HMva
{

public:

    HEventTtSemiTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HJetPairTagger *const NewJetPairTagger, hanalysis::HWSemiTagger *const NewWSemiTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopSemiTagger *const NewTopSemiTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger, hanalysis::HHeavyHiggsSemiTagger *const NewHeavyHiggsMixedTagger);

    /**
    * @brief Destructor
    *
    */
    ~HEventTtSemiTagger();

    std::vector<HEventSemiBranch *> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const HSextet &Sextet);

    std::vector< HSextet > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, std::vector< fastjet::PseudoJet > &Jets, HEventStruct &EventStruct, const hanalysis::HReader & EventSemiReader);

    std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader);

    void FillBranch(hheavyhiggs::HEventSemiBranch *EventSemiBranch, const HSextet &Sextet);


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HHEventTtSemiTagger";
    }

private:

    HTag GetTag(const HSextet &Sextet);

    void DefineVariables();

    std::vector<HSextet> GetHeavyHiggsEvents(HJets &Jets);

    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HWSemiTagger *WSemiTagger;
    hanalysis::HWTagger *WTagger;
    hanalysis::HTopSemiTagger *TopSemiTagger;
    hanalysis::HTopHadronicTagger *TopHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger *HeavyHiggsSemiTagger;

    hanalysis::HReader BottomReader;
    hanalysis::HReader WSemiReader;
    hanalysis::HReader WReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopSemiReader;
    hanalysis::HReader HeavyHiggsSemiReader;

    HEventSemiBranch Branch;
    hanalysis::HJetTag JetTag;

};

# endif
