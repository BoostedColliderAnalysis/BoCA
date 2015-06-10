# pragma once

# include "HiggsTagger.hh"
# include "TopLeptonicPairTagger.hh"
# include "Octet62.hh"

namespace higgscpv {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureTagger : public analysis::BranchTagger<higgscpv::OctetBranch>
{

public:

    SignatureTagger();

    int Train(analysis::Event &event, const Tag tag);

    std::vector< analysis::Octet62 > Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "higgscpv";
    }

    virtual inline std::string ClassName() const {
        return "SignatureTagger";
    }

private:

    void DefineVariables();

    analysis::HiggsTagger higgs_tagger_;

//     TopSemiPairTagger triplet_pair_tagger_;
    TopLeptonicPairTagger triplet_pair_tagger_;

    analysis::Reader higgs_reader_;

    analysis::Reader triplet_pair_reader_;

};

}
