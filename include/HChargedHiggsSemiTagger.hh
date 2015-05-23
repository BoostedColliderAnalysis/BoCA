# ifndef HChargedHiggsSemiTagger_hh
# define HChargedHiggsSemiTagger_hh

# include "Quartet31.hh"
# include "TopSemiTagger.hh"
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
        const analysis::WSemiTagger &Neww_semi_tagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::TopSemiTagger &Newtop_semi_tagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger);

    std::vector< HChargedHiggsSemiBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    HChargedHiggsSemiBranch GetBranch(const analysis::Quartet31 &quartet) const;

    std::vector< Quartet31 > GetBdt(
        const std::vector< analysis::Triplet > triplets, const std::vector< fastjet::PseudoJet > Siglets, const analysis::Reader &Reader);

    std::vector< Quartet31 > Getquartets(const analysis::Reader &Reader);

    BottomTagger bottom_tagger_;
    WSemiTagger w_semi_tagger;
    WHadronicTagger WTagger;
    TopHadronicTagger top_hadronic_tagger;
    TopSemiTagger top_semi_tagger;

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

    Tag GetTag(const analysis::Quartet31 &);

    JetTag jet_tag;

    HChargedHiggsSemiBranch Branch;
};

#endif
