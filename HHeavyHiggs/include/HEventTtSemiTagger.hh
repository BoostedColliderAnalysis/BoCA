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
        const analysis::WSemiTagger &Neww_semi_tagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::TopSemiTagger &Newtop_semi_tagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector< EventTtSemiBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< SextetEvent > GetBdt(const std::vector< analysis::Sextet > &sextets, Jets &jets, const Jets &Leptons, GlobalObservables &global_observables, const analysis::Reader &eventSemiReader);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventTtSemiBranch GetBranch(const SextetEvent &event) const;

    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger WTagger;
    analysis::TopSemiTagger top_semi_tagger;
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
