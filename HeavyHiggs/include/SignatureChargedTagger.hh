# pragma once

# include "ChargedHiggsSemiTagger.hh"
# include "TripletJetPairTagger.hh"
# include "Octet44.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureChargedTagger : public BranchTagger<OctetChargedBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    SignatureChargedTagger();

    int Train(Event &event, const Tag tag);

    std::vector<Octet44> Multiplets(Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "SignatureChargedTagger";
    }

private:

    ChargedHiggsSemiTagger charged_higgs_semi_tagger_;

    TripletJetPairTagger triplet_jet_pair_tagger_;

    Reader charged_higgs_semi_reader_;

    Reader triplet_jet_pair_reader_;


};

}

}
