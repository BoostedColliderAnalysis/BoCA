# ifndef HLeptonicEventTagger_hh
# define HLeptonicEventTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsLeptonicTagger.hh"
# include "HJetPairTagger.hh"
# include "HOctet.hh"
# include "HOctet44Event.hh"

/**
 *
 * @brief Event BDT Tagger for leptonic heavy higgs
 *
 */
class hheavyhiggs::HEventLeptonicTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventLeptonicTagger();

    HEventLeptonicTagger(
      const hanalysis::HBottomTagger &NewBottomTagger,
      const hanalysis::HJetPairTagger &NewJetPairTagger,
      const hanalysis::HTopLeptonicTagger &NewTopTagger,
      const hanalysis::HHeavyHiggsLeptonicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HEventLeptonicTagger();

    std::vector<hheavyhiggs::HEventLeptonicBranch *> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector< HOctet > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, std::vector< fastjet::PseudoJet > &Jets, HEventStruct &EventStruct, const hanalysis::HReader & EventSemiReader);

    std::vector< int > ApplyBdt2(const ExRootTreeReader*const TreeReader, const std::string TreeName, const TFile*const ExportFile);

    void FillBranch(const HOctet &Octet);

    void FillBranch(hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch, const HOctet &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HEventLeptonicTagger";
    };


private:
  Tag GetTag(const HOctet &Octet);

    void SetBranch(const TObject *Object) {
        (Branch) = *((HEventLeptonicBranch *) Object); // this used to be (*Branch)
    };

    void DefineVariables();

    std::vector<HOctet> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HJetPairTagger JetPairTagger;
    hanalysis::HTopLeptonicTagger TopLeptonicTagger;
    hanalysis::HHeavyHiggsLeptonicTagger HeavyHiggsLeptonicTagger;
    hanalysis::HReader BottomReader;
    hanalysis::HReader JetPairReader;
    hanalysis::HReader TopLeptonicReader;
    hanalysis::HReader HeavyHiggsLeptonicReader;
    hheavyhiggs::HEventLeptonicBranch Branch;
    hanalysis::HJetTag JetTag;

};

# endif
