# ifndef HTopSemiTagger_hh
# define HTopSemiTagger_hh

# include "HTriplet.hh"
# include "HBottomTagger.hh"
# include "HWSemiTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HTopSemiTagger : public HMva
{

public:

    HTopSemiTagger();

//     ~HTopSemiTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger);

    std::vector<HTopSemiBranch> GetBranches(HEvent &Event, const HObject::HTag State);

    std::vector<HTriplet> GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::HReader & Reader);

    HTopSemiBranch GetBranch(const hanalysis::HTriplet &Triplet) const;

    HBottomTagger BottomTagger;

    HWSemiTagger WSemiTagger;

    HReader BottomReader;

    HReader WSemiReader;

protected:

    virtual inline std::string ClassName() const {
        return "HTopSemiTagger";
    };

private:

    void DefineVariables();

    HTag GetTag(const HTriplet &Triplet) const;

    HJets GetNeutrinos(const hanalysis::HTriplet &Triplet)const;

    HTopSemiBranch Branch;

    HJetTag JetTag;

    float TopWindow;

};

#endif
