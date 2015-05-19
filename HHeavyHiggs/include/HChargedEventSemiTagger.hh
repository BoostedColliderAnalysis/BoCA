# ifndef HChargedeventSemiTagger_hh
# define HChargedeventSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HOctet44Event.hh"
# include "HChargedSignatureSemiTagger.hh"

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HChargedeventSemiTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedeventSemiTagger();

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger, const analysis::HChargedJetPairTagger &NewChargedJetPairTagger, const analysis::WSemiTagger &Neww_semi_tagger, const analysis::WHadronicTagger &NewWTagger, const analysis::TopSemiTagger &Newtop_semi_tagger, const analysis::TopHadronicTagger &Newtop_hadronic_tagger, const analysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger, const hheavyhiggs::HChargedSignatureSemiTagger &NewChargedSignatureTagger);


    std::vector< HChargedSemiBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    HChargedSemiBranch GetBranch(const EventMultiplet<HOctet44> &event) const;

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);


    std::vector<EventMultiplet<HOctet44>> GetBdt(
                                            const std::vector< HOctet44 > &Octets, Jets &jets, const Jets &SubJets, Jets &Leptons, EventStruct &event_struct, const analysis::Reader &eventSemiReader);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);


    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger WTagger;
    analysis::TopSemiTagger top_semi_tagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    analysis::HChargedJetPairTagger ChargedJetPairTagger;
    HChargedSignatureSemiTagger SignatureSemiTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader ChargedHiggsSemiReader;
    analysis::Reader ChargedJetPairReader;
    analysis::Reader SignatureSemiReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
      return "HChargedeventSemiTagger";
    }

private:

    void DefineVariables();

    HChargedSemiBranch Branch;

};

# endif
