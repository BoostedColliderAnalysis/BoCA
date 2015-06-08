# pragma once

# include "HeavyHiggsSemiTagger.hh"
# include "JetPairTagger.hh"
# include "Octet62.hh"

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureNeutralTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    SignatureNeutralTagger();

    int Train(analysis::Event &event, const Tag tag);

    std::vector< analysis::Octet62 > Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "SignatureNeutralTagger";
    }

private:

    TClass &Class() const {
      return *OctetNeutralBranch::Class();
    }

    void DefineVariables();

    std::vector<analysis::Octet62> GetHeavyHiggsevents(analysis::Jets &jets);

    OctetNeutralBranch branch_;

    HeavyHiggsSemiTagger heavy_higgs_semi_tagger_;

    analysis::JetPairTagger jet_pair_tagger_;

    analysis::Reader heavy_higgs_semi_reader_;

    analysis::Reader jet_pair_reader_;

};

}
