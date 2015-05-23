# pragma once

# include "Branch.hh"
# include "HHeavyHiggsSemiTagger.hh"
# include "HJetPairTagger.hh"
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

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger,
        const analysis::HJetPairTagger &NewJetPairTagger,
        const analysis::WSemiTagger &Neww_semi_tagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::TopSemiTagger &Newtop_semi_tagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger);

    std::vector<OctetNeutralBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< Octet62 > GetBdt(const std::vector< analysis::Sextet > &sextets, const std::vector< analysis::Doublet > &doublets, const analysis::Reader &Reader);


    OctetNeutralBranch GetBranch(const Octet62 &octet) const;

    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger WTagger;
    analysis::TopSemiTagger top_semi_tagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;
    analysis::HJetPairTagger JetPairTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader HeavyHiggsSemiReader;
    analysis::Reader JetPairReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "SignatureNeutralTagger";
    }

private:

    Tag GetTag(const Octet62 &);

    void DefineVariables();

    std::vector<Octet62> GetHeavyHiggsevents(Jets &jets);

    OctetNeutralBranch Branch;
    analysis::JetTag jet_tag;

};

}
