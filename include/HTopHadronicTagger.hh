# ifndef HTopHadronicTagger_hh
# define HTopHadronicTagger_hh

# include "HTriplet.hh"
# include "HBottomTagger.hh"
# include "HWTagger.hh"

/**
 * @brief Hadronic top BDT tagger
 *
 */
class hanalysis::HTopHadronicTagger : public HMva
{

public:

    HTopHadronicTagger(hanalysis::HBottomTagger*const NewBottomTagger, hanalysis::HWTagger*const NewWTagger);

    ~HTopHadronicTagger();

    void FillBranch(const hanalysis::HTriplet &Triplet);

    std::vector<HTopHadronicBranch*> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    std::vector<HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::HReader *const TopHadronicReader);

//     std::vector<HTriplet>  GetTriplets(HReader *TopHadronicReader){};


    HBottomTagger *BottomTagger;
    HWTagger *WTagger;

    HReader  *BottomReader;
    HReader  *WReader;


    void FillBranch(HTopHadronicBranch *TopHadronicBranch, const hanalysis::HTriplet &Triplet);


protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronicTagger";
    };

private:

    void DefineVariables();

    HTag GetTag(const hanalysis::HTriplet& Triplet);


    HTag GetTag(const fastjet::PseudoJet& Jet);
//     std::vector<HTriplet> GetSubJets(const HJets &Jets,const int SubJetNumber, const HTag Tag);

    HTopHadronicBranch *Branch;
    hanalysis::HJetTag *JetTag;

    float TopWindow ;
    float JetRadiusParameter;

};

#endif
