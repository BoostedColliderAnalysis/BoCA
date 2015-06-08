# pragma once

# include "Triplet.hh"
# include "BottomTagger.hh"
# include "WSemiTagger.hh"

namespace analysis
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class TopSemiTagger : public Tagger
{

public:

    TopSemiTagger();

    int Train(Event &event,PreCuts &pre_cuts, const Object::Tag tag);

    int Train(Event &event, const Object::Tag tag) {
        PreCuts pre_cuts;
        Train(event,pre_cuts,tag);
    }

    std::vector<Triplet> CleanTriplets(const analysis::Triplet& triplet, analysis::Jets TopQuarks, analysis::PreCuts& pre_cut, const analysis::Object::Tag tag);

    std::vector<Triplet> CleanTriplet(const analysis::Triplet& triplet, fastjet::PseudoJet TopQuark, analysis::PreCuts& pre_cut, const analysis::Object::Tag tag);

    int GetBdt(Event &event, const TMVA::Reader &reader) {
        return SaveEntries<TopSemiBranch>(Multiplets(event,reader));
    }

    std::vector<Triplet> Multiplets(Event &event, const TMVA::Reader &reader);

    int TopSemiId(Event &event) {
        return sgn(w_semi_tagger_.WSemiId(event)) * std::abs(TopId);
    }

protected:

    virtual inline std::string ClassName() const {
        return "TopSemiTagger";
    }

private:

    TClass &Class() const {
        return *TopSemiBranch::Class();
    }

    bool boost_ = false;

    void DefineVariables();

    TopSemiBranch branch_;

    float top_mass_window_;

    BottomTagger bottom_tagger_;

    WSemiTagger w_semi_tagger_;

    Reader bottom_reader_;

    Reader w_semi_reader_;

};

}
