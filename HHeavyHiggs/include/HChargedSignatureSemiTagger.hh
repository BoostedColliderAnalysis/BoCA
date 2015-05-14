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
class hheavyhiggs::HChargedSignatureSemiTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedSignatureSemiTagger();

    void SetTagger(
      const hanalysis::BottomTagger &NewBottomTagger,
      const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger,
      const hanalysis::HWSemiTagger &NewWSemiTagger,
      const hanalysis::WHadronicTagger &NewWTagger,
      const hanalysis::HTopSemiTagger &NewTopSemiTagger,
      const hanalysis::TopHadronicTagger &Newtop_hadronic_tagger,
      const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger);


    std::vector< HChargedOctetBranch > GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);

    HChargedOctetBranch GetBranch(const HOctet44 &Octet) const;

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);


    std::vector<HOctet44> GetBdt(
        const std::vector< hanalysis::HQuartet31 > &HiggsQuartets, const std::vector< hanalysis::HQuartet31 > &JetQuartets, const hanalysis::Reader &eventSemiReader);


    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::WHadronicTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::TopHadronicTagger top_hadronic_tagger;
    hanalysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    hanalysis::HChargedJetPairTagger ChargedJetPairTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WSemiReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader TopSemiReader;
    hanalysis::Reader ChargedHiggsSemiReader;
    hanalysis::Reader ChargedJetPairReader;


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
