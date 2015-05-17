# ifndef HHeavyHiggsSemiTagger_hh
# define HHeavyHiggsSemiTagger_hh

# include "HSextet.hh"
# include "HTopSemiTagger.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class analysis::HHeavyHiggsSemiTagger : public Tagger
{

public:

    HHeavyHiggsSemiTagger();

    void SetTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::HWSemiTagger &NewWSemiTagger, const analysis::WHadronicTagger &NewWTagger, const analysis::HTopSemiTagger &NewTopSemiTagger, const analysis::TopHadronicTagger &Newtop_hadronic_tagger);

    std::vector< HHeavyHiggsSemiBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag, const float pre_cut = 0);

    std::vector<analysis::HSextet>  GetBdt(const std::vector< Triplet > &tripletsSemi, const std::vector<Triplet > &tripletsHadronic, const Reader & Reader);

    std::vector<analysis::HSextet>  GetBdt(const std::vector< analysis::Triplet > &tripletsSemi, const std::vector< analysis::Triplet > &tripletsHadronic, const analysis::Reader & Reader, const int Mass);

    BottomTagger bottom_tagger_;
    WHadronicTagger WTagger;
    HWSemiTagger WSemiTagger;
    TopHadronicTagger top_hadronic_tagger;
    HTopSemiTagger TopSemiTagger;

    Reader BottomReader;
    Reader WReader;
    Reader WSemiReader;
    Reader TopHadronicReader;
    Reader TopSemiReader;

    HHeavyHiggsSemiBranch GetBranch(const analysis::HSextet& Sextet) const;


protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsSemiTagger";
    }

private:

    void DefineVariables();

    Tag GetTag(const HSextet &Sextet);

    HJetTag JetTag;
    HHeavyHiggsSemiBranch Branch;
};

#endif
