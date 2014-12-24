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

    HTopSemiTagger(hanalysis::HBottomTagger*const NewBottomTagger, hanalysis::HWSemiTagger*const NewWSemiTagger);

    ~HTopSemiTagger();

    std::vector<HTopSemiBranch *> GetBranches(HEvent *const Event, const HObject::HTag State);

    void FillBranch(const hanalysis::HTriplet &Triple);

    std::vector<HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet >& Doublets, const HJets& Jets, const hanalysis::HReader*const Reader);

//     std::vector<HTriplet> GetBdt(const HJets &Jets, HJets &Leptons, const fastjet::PseudoJet &MissingEt, const hanalysis::HReader *const Reader);

    std::vector<HTriplet>  GetTriplets(HReader *TopSemiReader){};

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

    HWSemiTagger *WSemiTagger;

    HReader *BottomReader;

    HReader *WSemiReader;

    HTopSemiBranch *Branch;

    HJetTag *JetTag;

};

#endif
