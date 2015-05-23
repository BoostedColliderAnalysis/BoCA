# pragma once

# include "Branch.hh"
# include "HHeavyHiggsHadronicTagger.hh"
# include "Octet62.hh"

namespace heavyhiggs
{

/**
 *
 * @brief event BDT tagger for hadronic heavy higgs
 *
 */
class EventHadronicTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventHadronicTagger();

    EventHadronicTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::WHadronicTagger &NewWTagger, const analysis::TopHadronicTagger &NewTopTagger,const  analysis::HHeavyHiggsHadronicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~EventHadronicTagger();

    std::vector<EventHadronicBranch *> GetBranches(analysis::Event &event, const Object::Tag Tag);

    void FillBranch(const Octet62 &octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
      return "EventHadronicTagger";
    };


private:

    void FillBranch(EventHadronicBranch *eventHadronicBranch, const Octet62 &octet);

    void DefineVariables();

    analysis::BottomTagger bottom_tagger_;
    analysis::WHadronicTagger WTagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HHeavyHiggsHadronicTagger HeavyHiggsHadronicTagger;

    analysis::Reader BottomReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader HeavyHiggsHadronicReader;

    EventHadronicBranch Branch;

};

  
}
