# ifndef HEventHadronicTagger_hh
# define HEventHadronicTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HHeavyHiggsHadronicTagger.hh"
# include "HOctet.hh"

/**
 *
 * @brief Event BDT tagger for hadronic heavy higgs
 *
 */
class hheavyhiggs::HEventHadronicTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventHadronicTagger();

    HEventHadronicTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWHadronicTagger &NewWTagger, const hanalysis::HTopHadronicTagger &NewTopTagger,const  hanalysis::HHeavyHiggsHadronicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HEventHadronicTagger();

    std::vector<hheavyhiggs::HEventHadronicBranch *> GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag);

    void FillBranch(const HOctet &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
      return "HEventHadronicTagger";
    };


private:

    void FillBranch(hheavyhiggs::HEventHadronicBranch *EventHadronicBranch, const HOctet &Octet);

    void DefineVariables();

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWHadronicTagger WTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HHeavyHiggsHadronicTagger HeavyHiggsHadronicTagger;

    hanalysis::HReader BottomReader;
    hanalysis::HReader WReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader HeavyHiggsHadronicReader;

    hheavyhiggs::HEventHadronicBranch Branch;

};

# endif
