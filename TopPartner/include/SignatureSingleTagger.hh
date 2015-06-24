# pragma once

# include "Decuplet.hh"
# include "TopPartnerHiggsPairTagger.hh"
# include "TopHadronicTagger.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSingleTagger : public BranchTagger<SignatureBranch>
{

public:

    SignatureSingleTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    std::vector<Decuplet73> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

protected:

    virtual  std::string ClassName() const {
        return "SignatureSingleTagger";
    }

private:

    TopPartnerHiggsPairTagger top_partner_higgs_pair_tagger_;

    TopHadronicTagger top_hadronic_tagger_;

    Reader top_partner_higgs_pair_reader_;

    Reader top_hadronic_reader_;
};

}

}
