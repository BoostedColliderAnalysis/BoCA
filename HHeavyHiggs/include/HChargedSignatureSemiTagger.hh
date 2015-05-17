# ifndef HChargedSignatureSemiTagger_hh
# define HChargedSignatureSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "TopHadronicTagger.hh"
# include "HChargedHiggsSemiTagger.hh"
# include "HChargedJetPairTagger.hh"
# include "HOctet44.hh"

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HChargedSignatureSemiTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedSignatureSemiTagger();

    void SetTagger(
      const analysis::BottomTagger &NewBottomTagger,
      const analysis::HChargedJetPairTagger &NewChargedJetPairTagger,
      const analysis::HWSemiTagger &NewWSemiTagger,
      const analysis::WHadronicTagger &NewWTagger,
      const analysis::HTopSemiTagger &NewTopSemiTagger,
      const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
      const analysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger);


    std::vector< HChargedOctetBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    HChargedOctetBranch GetBranch(const HOctet44 &Octet) const;

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);


    std::vector<HOctet44> GetBdt(
        const std::vector< analysis::HQuartet31 > &HiggsQuartets, const std::vector< analysis::HQuartet31 > &JetQuartets, const analysis::Reader &eventSemiReader);


    analysis::BottomTagger bottom_tagger_;
    analysis::HWSemiTagger WSemiTagger;
    analysis::WHadronicTagger WTagger;
    analysis::HTopSemiTagger TopSemiTagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    analysis::HChargedJetPairTagger ChargedJetPairTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader ChargedHiggsSemiReader;
    analysis::Reader ChargedJetPairReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HChargedSignatureSemiTagger";
    }

private:

    void DefineVariables();

    HChargedOctetBranch Branch;

};

# endif
