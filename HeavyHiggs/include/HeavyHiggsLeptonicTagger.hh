# pragma once

# include "Quartet22.hh"
# include "Sextet.hh"
# include "TopLeptonicTagger.hh"
# include "Branch.hh"

namespace heavyhiggs
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsLeptonicTagger : public analysis::BranchTagger<HeavyHiggsLeptonicBranch>
{

public:

    HeavyHiggsLeptonicTagger();

    int Train(analysis::Event &event, const analysis::Object::Tag tag);

    std::vector<analysis::Sextet> Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "HeavyHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    analysis::TopLeptonicTagger top_leptonic_tagger_;

    analysis::Reader top_leptonic_reader_;

};

}
