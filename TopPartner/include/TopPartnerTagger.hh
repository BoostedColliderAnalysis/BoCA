# pragma once

# include "Quintet.hh"
# include "TopHadronicTagger.hh"
# include "ZHadronicTagger.hh"
# include "Branches.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerTagger : public analysis::BranchTagger<TopPartnerBranch>
{

public:

    TopPartnerTagger();

    int Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Object::Tag tag);

    std::vector<analysis::Quintet> Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "TopPartnerTagger";
    }

private:

    void DefineVariables();

    analysis::TopHadronicTagger top_tagger_;

    analysis::ZHadronicTagger z_hadronic_tagger;

    analysis::Reader top_reader_;

    analysis::Reader z_hadronic_reader_;
};

}
