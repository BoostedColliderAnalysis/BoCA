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

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWTagger &NewWTagger);

    std::vector<HTopHadronicBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);

    std::vector<HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::HReader & TopHadronicReader);

    HTriplet GetBdt(hanalysis::HTriplet &Triplet, const hanalysis::HReader &TopHadronicReader);

    std::vector<HTriplet> GetBdt(HJets &Jets, const HReader &TopHadronicReader);


    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HTopHadronicBranch *) EventClonesArray.At(Entry))->Bdt;
    }

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

//     float JetRadiusParameter;

};

#endif
