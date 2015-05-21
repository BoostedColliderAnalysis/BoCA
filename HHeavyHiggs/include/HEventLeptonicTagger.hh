# ifndef HLeptoniceventTagger_hh
# define HLeptoniceventTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsLeptonicTagger.hh"
# include "HJetPairTagger.hh"
# include "Octet62.hh"
# include "MultipletEvent.hh"

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

    std::vector< Octet62 > GetBdt(const std::vector< analysis::Sextet > &sextets, const std::vector< analysis::Doublet > &doublets, Jets &jets, analysis::GlobalObservables &, const analysis::Reader &eventLeptonicReader);

    std::vector< int > ApplyBdt2(const ExRootTreeReader*const TreeReader, const std::string TreeName, const TFile*const ExportFile);

    void FillBranch(const Octet62 &octet);

    void FillBranch(hheavyhiggs::EventLeptonicBranch *eventLeptonicBranch, const Octet62 &octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "EventLeptonicTagger";
    };


private:
  Tag GetTag(const Octet62 &octet);

    void SetBranch(const TObject *Object) {
        (Branch) = *((EventLeptonicBranch *) Object); // this used to be (*Branch)
    };

    void DefineVariables();

    std::vector<Octet62> GetHeavyHiggsevents(const Jets &jets, const Jets &Leptons);

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
