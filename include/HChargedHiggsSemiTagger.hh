# ifndef HChargedHiggsSemiTagger_hh
# define HChargedHiggsSemiTagger_hh

# include "HQuartet31.hh"
# include "HTopSemiTagger.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class analysis::HChargedHiggsSemiTagger : public Tagger
{

public:

    HChargedHiggsSemiTagger();

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger,
        const analysis::HWSemiTagger &NewWSemiTagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::HTopSemiTagger &NewTopSemiTagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger);

    std::vector< HChargedHiggsSemiBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    HChargedHiggsSemiBranch GetBranch(const analysis::HQuartet31 &Quartet) const;

    std::vector< HQuartet31 > GetBdt(
        const std::vector< analysis::Triplet > triplets, const std::vector< fastjet::PseudoJet > Siglets, const analysis::Reader &Reader);

    std::vector< HQuartet31 > GetQuartets(const analysis::Reader &Reader);

    BottomTagger bottom_tagger_;
    HWSemiTagger WSemiTagger;
    WHadronicTagger WTagger;
    TopHadronicTagger top_hadronic_tagger;
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

    Tag GetTag(const analysis::HQuartet31 &);

    HJetTag JetTag;

    HChargedHiggsSemiBranch Branch;
};

#endif
