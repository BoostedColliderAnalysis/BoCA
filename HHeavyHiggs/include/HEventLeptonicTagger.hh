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
class hheavyhiggs::EventLeptonicTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventLeptonicTagger();

    EventLeptonicTagger(
      const analysis::BottomTagger &NewBottomTagger,
      const analysis::HJetPairTagger &NewJetPairTagger,
      const analysis::HTopLeptonicTagger &NewTopTagger,
      const analysis::HHeavyHiggsLeptonicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~EventLeptonicTagger();

    std::vector<hheavyhiggs::EventLeptonicBranch *> GetBranches(analysis::Event &event, const analysis::Object::Tag tag);

    std::vector< HOctet > GetBdt(const std::vector< analysis::HSextet > &Sextets, const std::vector< analysis::Doublet > &doublets, std::vector< fastjet::PseudoJet > &Jets, EventStruct &event_struct, const analysis::Reader & eventSemiReader);

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

    analysis::BottomTagger bottom_tagger_;
    analysis::HJetPairTagger JetPairTagger;
    analysis::HTopLeptonicTagger TopLeptonicTagger;
    analysis::HHeavyHiggsLeptonicTagger HeavyHiggsLeptonicTagger;
    analysis::Reader BottomReader;
    analysis::Reader JetPairReader;
    analysis::Reader TopLeptonicReader;
    analysis::Reader HeavyHiggsLeptonicReader;
    hheavyhiggs::EventLeptonicBranch Branch;
    analysis::HJetTag JetTag;

};

# endif
