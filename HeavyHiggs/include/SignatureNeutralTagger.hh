# pragma once

# include "HeavyHiggsSemiTagger.hh"
# include "JetPairTagger.hh"
# include "Octet62.hh"

namespace analysis
{

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureNeutralTagger : public BranchTagger<OctetNeutralBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    SignatureNeutralTagger();

    int Train(Event &event, const Tag tag);

    std::vector< Octet62 > Multiplets(Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "SignatureNeutralTagger";
    }

private:

    std::vector<Octet62> GetHeavyHiggsevents(Jets &jets);

    HeavyHiggsSemiTagger heavy_higgs_semi_tagger_;

    JetPairTagger jet_pair_tagger_;

    Reader heavy_higgs_semi_reader_;

    Reader jet_pair_reader_;

};

}

}
