# ifndef TripletJetPairTagger_hh
# define TripletJetPairTagger_hh

# include "BottomTagger.hh"
# include "Quartet31.hh"
# include "TopSemiTagger.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief JetPair BDT tagger
 *
 */
class analysis::TripletJetPairTagger : public Tagger
{

public:

    TripletJetPairTagger();

    void SetTagger(const BottomTagger &NewBottomTagger, const WSemiTagger &Neww_semi_tagger, const WHadronicTagger &NewWTagger, const TopSemiTagger &Newtop_semi_tagger, const TopHadronicTagger &Newtop_hadronic_tagger);

    std::vector< HChargedJetPairBranch> GetBranches(Event &event, const Object::Tag Tag);

    std::vector< Quartet31 > GetBdt(const std::vector< analysis::Triplet > &triplets, const Jets &jets, const analysis::Reader &JetPairReader);

    HChargedJetPairBranch GetBranch(const analysis::Quartet31 &quartet) const;

    BottomTagger bottom_tagger_;
    WHadronicTagger WTagger;
    WSemiTagger w_semi_tagger;
    TopHadronicTagger top_hadronic_tagger;
    TopSemiTagger top_semi_tagger;

    Reader BottomReader;
    Reader WReader;
    Reader WSemiReader;
    Reader TopHadronicReader;
    Reader TopSemiReader;

protected:

    virtual inline std::string ClassName() const {
        return "TripletJetPairTagger";
    }

private:

    void DefineVariables();

    analysis::Object::Tag GetTag(const analysis::Quartet31 &quartet);

    HChargedJetPairBranch Branch;

    JetTag jet_tag;

};

#endif
