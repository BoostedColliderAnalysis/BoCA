# ifndef HTopSemiTagger_hh
# define HTopSemiTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HTriplet.hh"

/**
 * @brief Bdt leptonic top tagger
 *
 */
class hanalysis::HTopSemiTagger : public HMva
{

public:

    HTopSemiTagger(HBottomTagger *const NewBottomTagger);

    ~HTopSemiTagger();

    std::vector<HTopSemiBranch*> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HTriplet &Triple);

    HJets GetNeutrinos(const hanalysis::HTriplet &Triplet)const;

    std::vector<HTriplet>  GetTopSemiBdt(HJets Jets, HJets Leptons,fastjet::PseudoJet MissingEt, const HReader * const TopSemiReader, const HState State);


private:

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HTopSemiBranch *Branch;

    HJetTag *JetTag;
    HState GetTripletTag(const hanalysis::HTriplet& Triplet);

    void DefineVariables();
    void FillBranch(HTopSemiBranch *const TopSemiBranch, const hanalysis::HTriplet &Triplet);


    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HTopSemiTagger";
    };

};

#endif
