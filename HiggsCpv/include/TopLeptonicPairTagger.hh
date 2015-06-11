# pragma once

# include "Sextet.hh"
# include "TopLeptonicTagger.hh"
# include "BranchesHiggsCpv.hh"

namespace higgscpv
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopLeptonicPairTagger : public analysis::BranchTagger<TripletPairBranch>
{

public:

    TopLeptonicPairTagger();

    int Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Object::Tag tag);

    std::vector<analysis::Sextet> Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(analysis::Event &event, const TMVA::Reader &reader) {
        analysis::PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "higgscpv";
    }

    virtual inline std::string ClassName() const {
        return "TopLeptonicPairTagger";
    }

private:

    void DefineVariables();

    analysis::TopLeptonicTagger top_leptonic_tagger_;

    analysis::Reader top_leptonic_reader_;

};

}
