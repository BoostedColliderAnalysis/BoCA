# ifndef HLeptoniceventTagger_hh
# define HLeptoniceventTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsLeptonicTagger.hh"
# include "HJetPairTagger.hh"
# include "HOctet.hh"
# include "HOctet44Event.hh"

/**
 *
 * @brief event BDT Tagger for leptonic heavy higgs
 *
 */
class hheavyhiggs::EventLeptonicTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventLeptonicTagger();

    EventLeptonicTagger(
      const hanalysis::BottomTagger &NewBottomTagger,
      const hanalysis::HJetPairTagger &NewJetPairTagger,
      const hanalysis::HTopLeptonicTagger &NewTopTagger,
      const hanalysis::HHeavyHiggsLeptonicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~EventLeptonicTagger();

    std::vector<hheavyhiggs::EventLeptonicBranch *> GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag tag);

    std::vector< HOctet > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::Doublet > &doublets, std::vector< fastjet::PseudoJet > &Jets, EventStruct &eventStruct, const hanalysis::Reader & eventSemiReader);

    std::vector< int > ApplyBdt2(const ExRootTreeReader*const TreeReader, const std::string TreeName, const TFile*const ExportFile);

    void FillBranch(const HOctet &Octet);

    void FillBranch(hheavyhiggs::EventLeptonicBranch *eventLeptonicBranch, const HOctet &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "EventLeptonicTagger";
    };


private:
  Tag GetTag(const HOctet &Octet);

    void SetBranch(const TObject *Object) {
        (Branch) = *((EventLeptonicBranch *) Object); // this used to be (*Branch)
    };

    void DefineVariables();

    std::vector<HOctet> GetHeavyHiggsevents(const Jets &jets, const Jets &Leptons);

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HJetPairTagger JetPairTagger;
    hanalysis::HTopLeptonicTagger TopLeptonicTagger;
    hanalysis::HHeavyHiggsLeptonicTagger HeavyHiggsLeptonicTagger;
    hanalysis::Reader BottomReader;
    hanalysis::Reader JetPairReader;
    hanalysis::Reader TopLeptonicReader;
    hanalysis::Reader HeavyHiggsLeptonicReader;
    hheavyhiggs::EventLeptonicBranch Branch;
    hanalysis::HJetTag JetTag;

};

# endif
