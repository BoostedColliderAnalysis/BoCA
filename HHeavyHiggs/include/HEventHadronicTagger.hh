# ifndef EventHadronicTagger_hh
# define EventHadronicTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsHadronicTagger.hh"
# include "HOctet.hh"

/**
 *
 * @brief event BDT tagger for hadronic heavy higgs
 *
 */
class hheavyhiggs::EventHadronicTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventHadronicTagger();

    EventHadronicTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::WHadronicTagger &NewWTagger, const hanalysis::TopHadronicTagger &NewTopTagger,const  hanalysis::HHeavyHiggsHadronicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~EventHadronicTagger();

    std::vector<hheavyhiggs::EventHadronicBranch *> GetBranches(hanalysis::Event &event, const HObject::Tag Tag);

    void FillBranch(const HOctet &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
      return "EventHadronicTagger";
    };


private:

    void FillBranch(hheavyhiggs::EventHadronicBranch *eventHadronicBranch, const HOctet &Octet);

    void DefineVariables();

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::WHadronicTagger WTagger;
    hanalysis::TopHadronicTagger top_hadronic_tagger;
    hanalysis::HHeavyHiggsHadronicTagger HeavyHiggsHadronicTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader HeavyHiggsHadronicReader;

    hheavyhiggs::EventHadronicBranch Branch;

};

# endif
