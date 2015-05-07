# ifndef HChargedHiggsSemiTagger_hh
# define HChargedHiggsSemiTagger_hh

# include "HQuartet31.hh"
# include "HTopSemiTagger.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class hanalysis::HChargedHiggsSemiTagger : public Tagger
{

public:

    HChargedHiggsSemiTagger();

    void SetTagger(
        const hanalysis::BottomTagger &NewBottomTagger,
        const hanalysis::HWSemiTagger &NewWSemiTagger,
        const hanalysis::HWHadronicTagger &NewWTagger,
        const hanalysis::HTopSemiTagger &NewTopSemiTagger,
        const hanalysis::HTopHadronicTagger &NewTopHadronicTagger);

    std::vector< HChargedHiggsSemiBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    HChargedHiggsSemiBranch GetBranch(const hanalysis::HQuartet31 &Quartet) const;

    std::vector< HQuartet31 > GetBdt(
        const std::vector< hanalysis::HTriplet > Triplets, const std::vector< fastjet::PseudoJet > Siglets, const hanalysis::Reader &Reader);

    std::vector< HQuartet31 > GetQuartets(const hanalysis::Reader &Reader);

    BottomTagger bottom_tagger_;
    HWSemiTagger WSemiTagger;
    HWHadronicTagger WTagger;
    HTopHadronicTagger TopHadronicTagger;
    HTopSemiTagger TopSemiTagger;

    Reader BottomReader;
    Reader WSemiReader;
    Reader WReader;
    Reader TopHadronicReader;
    Reader TopSemiReader;

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsSemiTagger";
    }

private:

    void DefineVariables();

    Tag GetTag(const hanalysis::HQuartet31 &);

    HJetTag JetTag;

    HChargedHiggsSemiBranch Branch;
};

#endif
