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

    HTopHadronicTagger();

    ~HTopHadronicTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWTagger &NewWTagger);

    std::vector<HTopHadronicBranch> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    std::vector<HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::HReader & TopHadronicReader);

    HBottomTagger BottomTagger;
    HWTagger WTagger;

    HReader  BottomReader;
    HReader  WReader;

    HTopHadronicBranch GetBranch(const hanalysis::HTriplet &Triplet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronicTagger";
    };

private:

    void DefineVariables();

    HTag GetTag(const hanalysis::HTriplet& Triplet);

    HTag GetTag(const fastjet::PseudoJet& Jet);

    HTopHadronicBranch Branch;
    hanalysis::HJetTag JetTag;

    float TopWindow ;
    float JetRadiusParameter;

};

#endif
