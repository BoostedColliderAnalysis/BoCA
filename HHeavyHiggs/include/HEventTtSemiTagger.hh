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
        const hanalysis::BottomTagger &NewBottomTagger,
        const hanalysis::HWSemiTagger &NewWSemiTagger,
        const hanalysis::HWHadronicTagger &NewWTagger,
        const hanalysis::HTopSemiTagger &NewTopSemiTagger,
        const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
        const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector< HEventTtSemiBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector< HSextetEvent > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, Jets &jets, const Jets &Leptons, HEventStruct &EventStruct, const hanalysis::Reader &EventSemiReader);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry);

    HEventTtSemiBranch GetBranch(const HSextetEvent &Event) const;

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWHadronicTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WSemiReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader TopSemiReader;
    hanalysis::Reader HeavyHiggsSemiReader;

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HHEventTtSemiTagger";
    }

private:

    void DefineVariables();

    std::vector<HSextetEvent> GetHeavyHiggsEvents(Jets &jets);

    HEventTtSemiBranch Branch;

    hanalysis::HJetTag JetTag;

};

# endif
