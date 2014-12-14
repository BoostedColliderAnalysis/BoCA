# ifndef HTopSemiTagger_hh
# define HTopSemiTagger_hh

# include "HTriplet.hh"
# include "HBottomTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HTopSemiTagger : public HMva
{

public:

    HTopSemiTagger(HBottomTagger *const NewBottomTagger);

    ~HTopSemiTagger();

    std::vector<HTopSemiBranch *> GetBranches(HEvent *const Event, const HObject::HTag State);

    void FillBranch(const hanalysis::HTriplet &Triple);

    std::vector<HTriplet>  GetBdt(const HJets &Jets, HJets &Leptons, const fastjet::PseudoJet &MissingEt, const hanalysis::HReader *const Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HTopSemiTagger";
    };

private:

    void DefineVariables();

    void FillBranch(HTopSemiBranch *const TopSemiBranch, const hanalysis::HTriplet &Triplet);

    HTag GetTag(const HTriplet &Triplet) const;

    HJets GetNeutrinos(const hanalysis::HTriplet &Triplet)const;

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HTopSemiBranch *Branch;

    HJetTag *JetTag;

};

#endif
