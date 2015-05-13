# ifndef HChargedHadronicTagger_hh
# define HChargedHadronicTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HChargedHiggsHadronicTagger.hh"
# include "HOctet44.hh"

/**
 *
 * @brief event BDT tagger for hadronic heavy higgs
 *
 */
class hheavyhiggs::HChargedHadronicTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedHadronicTagger(
      const hanalysis::BottomTagger &NewBottomTagger,
      const hanalysis::WHadronicTagger &NewWTagger,
      const hanalysis::TopHadronicTagger &NewTopTagger,
      const hanalysis::HChargedHiggsHadronicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HChargedHadronicTagger();

    std::vector<hheavyhiggs::HChargedHadronicBranch *> GetBranches(hanalysis::Event &event, const HObject::Tag Tag);

    void FillBranch(const HOctet44 &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HChargedHadronicTagger";
    };


private:

  void FillBranch(hheavyhiggs::HChargedHadronicBranch *eventHadronicBranch, const HOctet44 &Octet);

    void DefineVariables();

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::WHadronicTagger WTagger;
    hanalysis::TopHadronicTagger top_hadronic_tagger;
    hanalysis::HChargedHiggsHadronicTagger ChargedHiggsHadronicTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader ChargedHiggsHadronicReader;

    hheavyhiggs::HChargedHadronicBranch Branch;

};

# endif
