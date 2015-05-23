# pragma once

# include "HChargedHiggsHadronicTagger.hh"
# include "Octet44.hh"
# include "Branch.hh"

namespace heavyhiggs{

/**
 *
 * @brief event BDT tagger for hadronic heavy higgs
 *
 */
class HChargedHadronicTagger : public analysis::Tagger
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

    std::vector<HChargedHadronicBranch *> GetBranches(analysis::Event &event, const Object::Tag Tag);

    void FillBranch(const Octet44 &octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HChargedHadronicTagger";
    };


private:

  void FillBranch(HChargedHadronicBranch *eventHadronicBranch, const Octet44 &octet);

    void DefineVariables();

    analysis::BottomTagger bottom_tagger_;
    analysis::WHadronicTagger WTagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HChargedHiggsHadronicTagger ChargedHiggsHadronicTagger;

    analysis::Reader BottomReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader ChargedHiggsHadronicReader;

    HChargedHadronicBranch Branch;

};

}
