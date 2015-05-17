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
class hheavyhiggs::HChargedHadronicTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedHadronicTagger(
      const analysis::BottomTagger &NewBottomTagger,
      const analysis::WHadronicTagger &NewWTagger,
      const analysis::TopHadronicTagger &NewTopTagger,
      const analysis::HChargedHiggsHadronicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HChargedHadronicTagger();

    std::vector<hheavyhiggs::HChargedHadronicBranch *> GetBranches(analysis::Event &event, const Object::Tag Tag);

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

    analysis::BottomTagger bottom_tagger_;
    analysis::WHadronicTagger WTagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HChargedHiggsHadronicTagger ChargedHiggsHadronicTagger;

    analysis::Reader BottomReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader ChargedHiggsHadronicReader;

    hheavyhiggs::HChargedHadronicBranch Branch;

};

# endif
