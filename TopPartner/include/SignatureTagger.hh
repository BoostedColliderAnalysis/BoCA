# pragma once

# include "Quattuordecuplet.hh"
# include "TopPartnerPairTagger.hh"
# include "HiggsPairTagger.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureTagger : public analysis::BranchTagger<SignatureBranch>
{

public:

    SignatureTagger();

    int Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Object::Tag tag);

    std::vector<Quattuordecuplet> Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "EventTagger";
    }

private:

    void DefineVariables();

    TopPartnerPairTagger top_partner_pair_tagger_;

    HiggsPairTagger higgs_pair_tagger;

    analysis::Reader top_partner_pair_reader_;

    analysis::Reader higgs_pair_reader_;
};

}
