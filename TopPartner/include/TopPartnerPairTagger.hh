# pragma once

# include "Decuplet.hh"
# include "TopPartnerHadronicTagger.hh"
# include "TopPartnerSemiTagger.hh"
# include "BranchesTopPartner.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerPairTagger : public BranchTagger<MultiBranch>
{

public:

    TopPartnerPairTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    std::vector<Decuplet55> Multiplets(Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "TopPartnerPairTagger";
    }

private:

    TopPartnerHadronicTagger top_partner_hadronic_tagger_;

    TopPartnerSemiTagger top_partner_semi_tagger_;

    Reader top_partner_hadronic_reader_;

    Reader top_partner_semi_reader_;
};

}

}
