# ifndef HChargedEventSemiTagger_hh
# define HChargedEventSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HOctet44Event.hh"
# include "HChargedSignatureSemiTagger.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HChargedEventSemiTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedEventSemiTagger();

    void SetTagger(
        const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger, const hanalysis::HWSemiTagger &NewWSemiTagger, const hanalysis::WHadronicTagger &NewWTagger, const hanalysis::HTopSemiTagger &NewTopSemiTagger, const hanalysis::TopHadronicTagger &Newtop_hadronic_tagger, const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger, const hheavyhiggs::HChargedSignatureSemiTagger &NewChargedSignatureTagger);


    std::vector< HChargedSemiBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    HChargedSemiBranch GetBranch(const HEventMultiplet<HOctet44> &Event) const;

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);


    std::vector<HEventMultiplet<HOctet44>> GetBdt(
                                            const std::vector< HOctet44 > &Octets, Jets &jets, const Jets &SubJets, Jets &Leptons, HEventStruct &EventStruct, const hanalysis::Reader &EventSemiReader);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry);


    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::WHadronicTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::TopHadronicTagger top_hadronic_tagger;
    hanalysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    hanalysis::HChargedJetPairTagger ChargedJetPairTagger;
    HChargedSignatureSemiTagger SignatureSemiTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WSemiReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader TopSemiReader;
    hanalysis::Reader ChargedHiggsSemiReader;
    hanalysis::Reader ChargedJetPairReader;
    hanalysis::Reader SignatureSemiReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
      return "HChargedEventSemiTagger";
    }

private:

    void DefineVariables();

    HChargedSemiBranch Branch;

};

# endif
