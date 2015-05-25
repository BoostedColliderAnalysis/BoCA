# pragma once

# include "Branch.hh"
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

    std::vector<OctetNeutralBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< Octet62 > Octets(analysis::Event& event, const TMVA::Reader& reader);

    std::vector< Octet62 > GetBdt(const std::vector< analysis::Sextet > &sextets, const std::vector< analysis::Doublet > &doublets, const analysis::Reader &Reader) {
      Print(kError,"get bdt","depreciaated");
      return std::vector< Octet62> {};
    }

    TClass &Class() const {
      return *OctetNeutralBranch::Class();
    }

    OctetNeutralBranch GetBranch(const Octet62 &octet) const;

    analysis::HeavyHiggsSemiTagger heavy_higgs_semi_tagger_;
    analysis::JetPairTagger jet_pair_tagger_;

    analysis::Reader heavy_higgs_semi_reader_;
    analysis::Reader jet_pair_reader_;


protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "SignatureNeutralTagger";
    }

private:

    void DefineVariables();

    std::vector<Octet62> GetHeavyHiggsevents(Jets &jets);

    OctetNeutralBranch branch_;

};

}
