# ifndef HChargedHiggsSemiTagger_hh
# define HChargedHiggsSemiTagger_hh

# include "HQuartet31.hh"
# include "HTopSemiTagger.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class hanalysis::HChargedHiggsSemiTagger : public HMva
{

public:

  HChargedHiggsSemiTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger);

  HChargedHiggsSemiTagger();

    ~HChargedHiggsSemiTagger();

    std::vector< HChargedHiggsSemiBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const hanalysis::HQuartet31 &HQuartet);

    std::vector< HQuartet31 > GetBdt(std::vector< hanalysis::HTriplet > Triplets, std::vector< fastjet::PseudoJet > Siglets, const hanalysis::HReader & Reader);

    std::vector< HQuartet31 > GetQuartets(const hanalysis::HReader & Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsSemiTagger";
    }

private:

    void DefineVariables();

    void FillBranch(HChargedHiggsSemiBranch *ChargedHiggsBranch, const hanalysis::HQuartet31 &Quartet);

    HTag GetTag(const hanalysis::HQuartet31 &Quartet);

    HJetTag JetTag;

    HBottomTagger BottomTagger;
    HWSemiTagger WSemiTagger;
    HWTagger WTagger;
    HTopHadronicTagger TopHadronicTagger;
    HTopSemiTagger TopSemiTagger;

    HReader BottomReader;

    HReader WSemiReader;
    HReader WReader;

    HReader TopHadronicReader;
    HReader TopSemiReader;

    HChargedHiggsSemiBranch Branch;
};

#endif
