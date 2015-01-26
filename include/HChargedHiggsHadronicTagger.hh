# ifndef HChargedHiggsHadronicTagger_hh
# define HChargedHiggsHadronicTagger_hh

# include "HQuartet31.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HChargedHiggsHadronicTagger : public HMva
{

public:

  HChargedHiggsHadronicTagger();

    HChargedHiggsHadronicTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWTagger &NewWTagger, const hanalysis::HTopHadronicTagger &NewTopTagger);

    ~HChargedHiggsHadronicTagger();

    std::vector<HChargedHiggsHadronicBranch *> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const hanalysis::HQuartet31 &Quartet);

    std::vector< HQuartet31 > GetBdt(std::vector< hanalysis::HTriplet > Triplets, std::vector< fastjet::PseudoJet > Jets, const hanalysis::HReader &Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsHadronicTagger";
    }

private:

    void DefineVariables();

    void FillBranch(HChargedHiggsHadronicBranch *ChargedHiggsHadronicBranch, const hanalysis::HQuartet31 &Quartet);

    HTag GetTag(const hanalysis::HQuartet31 &Quartet);

    HBottomTagger BottomTagger;
    HWTagger WTagger;
    HTopHadronicTagger TopHadronicTagger;

    HReader BottomReader;
    HReader WReader;
    HReader TopHadronicReader;

    HChargedHiggsHadronicBranch Branch;
    HJetTag JetTag;

};

#endif
