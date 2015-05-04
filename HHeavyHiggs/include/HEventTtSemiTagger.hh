# ifndef HEventTtSemiTagger_hh
# define HEventTtSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HJetPairTagger.hh"
# include "HSextetEvent.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HEventTtSemiTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventTtSemiTagger();

    void SetTagger(
        const hanalysis::HBottomTagger &NewBottomTagger,
        const hanalysis::HWSemiTagger &NewWSemiTagger,
        const hanalysis::HWTagger &NewWTagger,
        const hanalysis::HTopSemiTagger &NewTopSemiTagger,
        const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
        const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector< HEventTtSemiBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector< HSextetEvent > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, HJets &Jets, const HJets &Leptons, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry);

    HEventTtSemiBranch GetBranch(const HSextetEvent &Event) const;

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;

    hanalysis::HReader BottomReader;
    hanalysis::HReader WSemiReader;
    hanalysis::HReader WReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopSemiReader;
    hanalysis::HReader HeavyHiggsSemiReader;

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HHEventTtSemiTagger";
    }

private:

    void DefineVariables();

    std::vector<HSextetEvent> GetHeavyHiggsEvents(HJets &Jets);

    HEventTtSemiBranch Branch;

    hanalysis::HJetTag JetTag;

};

# endif
