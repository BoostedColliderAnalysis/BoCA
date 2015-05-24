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

//     void SetTagger(
//         const analysis::BottomTagger &NewBottomTagger,
//         const analysis::JetPairTagger &Newjet_pair_tagger,
//         const analysis::WSemiTagger &Neww_semi_tagger,
//         const analysis::WHadronicTagger &NewWTagger,
//         const analysis::TopSemiTagger &Newtop_semi_tagger,
//         const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
//         const analysis::HeavyHiggsSemiTagger &Newheavy_higgs_semi_tagger);

    std::vector<OctetNeutralBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< Octet62 > Octets(analysis::Event& event, const TMVA::Reader& reader);

    std::vector< Octet62 > GetBdt(const std::vector< analysis::Sextet > &sextets, const std::vector< analysis::Doublet > &doublets, const analysis::Reader &Reader) {
      Print(kError,"get bdt","depreciaated");
      return std::vector< Octet62> {};
    }



    OctetNeutralBranch GetBranch(const Octet62 &octet) const;

//     analysis::BottomTagger bottom_tagger_;
//     analysis::WSemiTagger w_semi_tagger;
//     analysis::WHadronicTagger WTagger;
//     analysis::TopSemiTagger top_semi_tagger;
//     analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HeavyHiggsSemiTagger heavy_higgs_semi_tagger_;
    analysis::JetPairTagger jet_pair_tagger_;

//     analysis::Reader BottomReader;
//     analysis::Reader WSemiReader;
//     analysis::Reader WReader;
//     analysis::Reader TopHadronicReader;
//     analysis::Reader TopSemiReader;
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
