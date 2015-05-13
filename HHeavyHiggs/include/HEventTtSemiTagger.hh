# ifndef EventTtSemiTagger_hh
# define EventTtSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HJetPairTagger.hh"
# include "HSextetEvent.hh"

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::EventTtSemiTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventTtSemiTagger();

    void SetTagger(
        const hanalysis::BottomTagger &NewBottomTagger,
        const hanalysis::HWSemiTagger &NewWSemiTagger,
        const hanalysis::WHadronicTagger &NewWTagger,
        const hanalysis::HTopSemiTagger &NewTopSemiTagger,
        const hanalysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector< EventTtSemiBranch > GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);

    std::vector< HSextetevent > GetBdt(const std::vector< hanalysis::HSextet > &Sextets, Jets &jets, const Jets &Leptons, EventStruct &eventStruct, const hanalysis::Reader &eventSemiReader);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventTtSemiBranch GetBranch(const HSextetevent &event) const;

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::WHadronicTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::TopHadronicTagger top_hadronic_tagger;
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
        return "HEventTtSemiTagger";
    }

private:

    void DefineVariables();

    std::vector<HSextetevent> GetHeavyHiggsevents(Jets &jets);

    EventTtSemiBranch Branch;

    hanalysis::HJetTag JetTag;

};

# endif
