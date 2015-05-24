# pragma once

# include "Branch.hh"
# include "HeavyHiggsSemiTagger.hh"
# include "JetPairTagger.hh"
# include "MultipletEvent.hh"

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusionTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventFusionTagger();

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger,
        const analysis::WSemiTagger &Neww_semi_tagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::TopSemiTagger &Newtop_semi_tagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const analysis::HeavyHiggsSemiTagger &Newheavy_higgs_semi_tagger);

    std::vector< EventFusionBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< analysis::MultipletEvent<analysis::Sextet> > GetBdt(const std::vector< analysis::Sextet > &sextets, Jets &jets, const Jets &Leptons, analysis::GlobalObservables &global_observables, const analysis::Reader &eventSemiReader);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventFusionBranch GetBranch(const analysis::MultipletEvent<analysis::Sextet> &event) const;

    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger WTagger;
    analysis::TopSemiTagger top_semi_tagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HeavyHiggsSemiTagger heavy_higgs_semi_tagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader HeavyHiggsSemiReader;

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventFusionTagger";
    }

private:

    void DefineVariables();

    std::vector<analysis::MultipletEvent<analysis::Sextet>> GetHeavyHiggsevents(Jets &jets);

    EventFusionBranch Branch;

    analysis::JetTag jet_tag;

};

}
