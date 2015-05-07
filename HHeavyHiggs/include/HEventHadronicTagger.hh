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

    HEventHadronicTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::HWHadronicTagger &NewWTagger, const hanalysis::HTopHadronicTagger &NewTopTagger,const  hanalysis::HHeavyHiggsHadronicTagger &NewHeavyHiggsTagger);

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

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWHadronicTagger WTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HHeavyHiggsHadronicTagger HeavyHiggsHadronicTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader HeavyHiggsHadronicReader;

    hheavyhiggs::HEventHadronicBranch Branch;

};

# endif
