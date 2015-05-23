# ifndef HHeavyHiggsSemiTagger_hh
# define HHeavyHiggsSemiTagger_hh

# include "Sextet.hh"
# include "TopSemiTagger.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class analysis::HHeavyHiggsSemiTagger : public Tagger
{

public:

    HHeavyHiggsSemiTagger();

    void SetTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::WSemiTagger &Neww_semi_tagger, const analysis::WHadronicTagger &NewWTagger, const analysis::TopSemiTagger &Newtop_semi_tagger, const analysis::TopHadronicTagger &Newtop_hadronic_tagger);

    std::vector< HHeavyHiggsSemiBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag, const float pre_cut = 0);

    std::vector<analysis::Sextet>  GetBdt(const std::vector< Triplet > &tripletsSemi, const std::vector<Triplet > &tripletsHadronic, const Reader & Reader);

    std::vector<analysis::Sextet>  GetBdt(const std::vector< analysis::Triplet > &tripletsSemi, const std::vector< analysis::Triplet > &tripletsHadronic, const analysis::Reader & Reader, const int Mass);

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

    HHeavyHiggsSemiBranch GetBranch(const analysis::Sextet& sextet) const;


protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsSemiTagger";
    }

private:

    void DefineVariables();

    Tag GetTag(const Sextet &sextet);

    JetTag jet_tag;
    HHeavyHiggsSemiBranch Branch;
};

#endif
