# ifndef EventTtSemiTagger_hh
# define EventTtSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HJetPairTagger.hh"
# include "SextetEvent.hh"

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::EventTtSemiTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventTtSemiTagger();

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger,
        const analysis::HWSemiTagger &NewWSemiTagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::HTopSemiTagger &NewTopSemiTagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector< EventTtSemiBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< SextetEvent > GetBdt(const std::vector< analysis::HSextet > &Sextets, Jets &jets, const Jets &Leptons, EventStruct &event_struct, const analysis::Reader &eventSemiReader);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventTtSemiBranch GetBranch(const SextetEvent &event) const;

    analysis::BottomTagger bottom_tagger_;
    analysis::HWSemiTagger WSemiTagger;
    analysis::WHadronicTagger WTagger;
    analysis::HTopSemiTagger TopSemiTagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader HeavyHiggsSemiReader;

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HEventTtSemiTagger";
    }

private:

    void DefineVariables();

    std::vector<SextetEvent> GetHeavyHiggsevents(Jets &jets);

    EventTtSemiBranch Branch;

    analysis::HJetTag JetTag;

};

# endif
