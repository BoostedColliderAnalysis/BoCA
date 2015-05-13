# ifndef EventSemiTagger_hh
# define EventSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HOctet.hh"
# include "HOctet44Event.hh"
# include "HSignatureSemiTagger.hh"

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::EventSemiTagger : public hanalysis::Tagger
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
        const hanalysis::BottomTagger &NewBottomTagger,
        const hanalysis::HJetPairTagger &NewJetPairTagger,
        const hanalysis::HWSemiTagger &NewWSemiTagger,
        const hanalysis::WHadronicTagger &NewWTagger,
        const hanalysis::HTopSemiTagger &NewTopSemiTagger,
        const hanalysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger,
        const HSignatureSemiTagger &NewSignatureSemiTagger);

    std::vector<EventSemiBranch> GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);

    std::vector< EventMultiplet< HOctet > > GetBdt(const std::vector< HOctet > &Octets, const Jets &jets, const Jets &SubJets, const Jets &Leptons, EventStruct &eventStruct, const hanalysis::Reader &eventSemiReader);

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventSemiBranch GetBranch(const EventMultiplet< HOctet > &Octet) const;

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::WHadronicTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::TopHadronicTagger top_hadronic_tagger;
    hanalysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;
    hanalysis::HJetPairTagger JetPairTagger;
    HSignatureSemiTagger SignatureSemiTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WSemiReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader TopSemiReader;
    hanalysis::Reader HeavyHiggsSemiReader;
    hanalysis::Reader JetPairReader;
    hanalysis::Reader SignatureSemiReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HEventSemiTagger";
    }

private:

    void DefineVariables();

    std::vector<HOctet> GetHeavyHiggsevents(Jets &jets);

    EventSemiBranch Branch;
    hanalysis::HJetTag JetTag;

};

# endif
