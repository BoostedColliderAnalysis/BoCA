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
class hheavyhiggs::EventHadronicTagger : public analysis::Tagger
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

    std::vector<hheavyhiggs::EventHadronicBranch *> GetBranches(analysis::Event &event, const Object::Tag Tag);

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

    analysis::BottomTagger bottom_tagger_;
    analysis::WHadronicTagger WTagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HHeavyHiggsHadronicTagger HeavyHiggsHadronicTagger;

    analysis::Reader BottomReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader HeavyHiggsHadronicReader;

    hheavyhiggs::EventHadronicBranch Branch;

};

# endif
