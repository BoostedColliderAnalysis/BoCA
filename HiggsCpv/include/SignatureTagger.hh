# pragma once

# include "BranchesHiggsCpv.hh"
# include "HiggsTagger.hh"
# include "TripletPairTagger.hh"
# include "Octet62.hh"
# include "Branch.hh"

namespace higgscpv {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureTagger : public analysis::Tagger
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

    TClass &Class() const {
      return *higgscpv::OctetBranch::Class();
    }

    void DefineVariables();

    higgscpv::OctetBranch branch_;

    analysis::HiggsTagger higgs_tagger_;

    TripletPairTagger triplet_pair_tagger_;

    analysis::Reader higgs_reader_;

    analysis::Reader triplet_pair_reader_;

};

}
