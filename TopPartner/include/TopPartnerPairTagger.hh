# pragma once

# include "Decuplet.hh"
# include "TopPartnerHadronicTagger.hh"
# include "TopPartnerSemiTagger.hh"
# include "BranchesTopPartner.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerPairTagger : public analysis::BranchTagger<HiggsPairBranch>
{

public:

    TopPartnerPairTagger();

    int Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Object::Tag tag);

    std::vector<Decuplet> Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "TopPartnerPairTagger";
    }

private:

    void DefineVariables();

    TopPartnerHadronicTagger top_partner_hadronic_tagger_;

    TopPartnerSemiTagger top_partner_semi_tagger_;

    analysis::Reader top_partner_hadronic_reader_;

    analysis::Reader top_partner_semi_reader_;
};

}
