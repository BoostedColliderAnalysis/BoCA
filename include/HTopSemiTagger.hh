# ifndef HTopSemiTagger_hh
# define HTopSemiTagger_hh

# include "HTriplet.hh"
# include "HBottomTagger.hh"
# include "HWSemiTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HTopSemiTagger : public Tagger
{

public:

    HTopSemiTagger();

//     ~HTopSemiTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger);

    std::vector<HTopSemiBranch> GetBranches(HEvent &Event, const HObject::Tag State, float pre_cut = 0);

    std::vector<HTriplet> GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::HReader & Reader);

    HTopSemiBranch GetBranch(const hanalysis::HTriplet &Triplet) const;

    HBottomTagger BottomTagger;

    HWSemiTagger WSemiTagger;

    HReader BottomReader;

    HReader WSemiReader;

    void GetBottomInfo(HTopSemiBranch &TopHadronicBranch, const fastjet::PseudoJet jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HTopSemiTagger";
    };

private:

  bool Boost = false;

    void DefineVariables();

    Tag GetTag(const HTriplet &Triplet) const;

    HJets GetNeutrinos(const hanalysis::HTriplet &Triplet)const;

    HTopSemiBranch Branch;

    HJetTag JetTag;

    float TopWindow;

};

#endif
