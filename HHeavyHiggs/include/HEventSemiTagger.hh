# ifndef EventSemiTagger_hh
# define EventSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "Octet62.hh"
# include "MultipletEvent.hh"
# include "HSignatureSemiTagger.hh"

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::EventSemiTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventSemiTagger();

    /**
    * @brief Destructor
    *
    */
    ~EventSemiTagger();

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger,
        const analysis::HJetPairTagger &NewJetPairTagger,
        const analysis::WSemiTagger &Neww_semi_tagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::TopSemiTagger &Newtop_semi_tagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger,
        const HSignatureSemiTagger &NewSignatureSemiTagger);

    std::vector<EventSemiBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< analysis::MultipletEvent< Octet62 > > GetBdt(const std::vector< Octet62 > &octets, const Jets &jets, const Jets &SubJets, const Jets &Leptons, analysis::GlobalObservables &global_observables, const analysis::Reader &eventSemiReader);

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventSemiBranch GetBranch(const analysis::MultipletEvent< Octet62 > &octet) const;

    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger WTagger;
    analysis::TopSemiTagger top_semi_tagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;
    analysis::HJetPairTagger JetPairTagger;
    HSignatureSemiTagger SignatureSemiTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader HeavyHiggsSemiReader;
    analysis::Reader JetPairReader;
    analysis::Reader SignatureSemiReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HEventSemiTagger";
    }

private:

    void DefineVariables();

    std::vector<Octet62> GetHeavyHiggsevents(Jets &jets);

    EventSemiBranch Branch;
    analysis::HJetTag JetTag;

};

# endif
