# ifndef HTopHadronicTagger_hh
# define HTopHadronicTagger_hh

# include "HTriplet.hh"
# include "HBottomTagger.hh"
# include "HWTagger.hh"

#include "fastjet/contrib/MeasureFunction.hh"

/**
 * @brief Hadronic top BDT tagger
 *
 */
class hanalysis::HTopHadronicTagger : public HMva
{

public:

    HTopHadronicTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWTagger &NewWTagger);

    std::vector<HTopHadronicBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag, float pre_cut = 0);

    std::vector<HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::HReader & TopHadronicReader);

    HTriplet GetBdt(hanalysis::HTriplet &Triplet, const hanalysis::HReader &TopHadronicReader);

    std::vector<HTriplet> GetBdt(const HJets &Jets, const hanalysis::HReader &TopHadronicReader, hanalysis::HWTagger &WTagger, hanalysis::HReader &WReader, hanalysis::HBottomTagger &BottomTagger, hanalysis::HReader &BottomReader);

//     std::vector<HTriplet> GetBdt(HJets &Jets, const HReader &TopHadronicReader);


    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HTopHadronicBranch *) EventClonesArray.At(Entry))->Bdt;
    }

    HBottomTagger BottomTagger;
    HWTagger WTagger;

    HReader  BottomReader;
    HReader  WReader;

    HTopHadronicBranch GetBranch(const hanalysis::HTriplet &triplet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronicTagger";
    };

private:

    void DefineVariables();

    HTag GetTag(const hanalysis::HTriplet &);

    HTag GetTag(const fastjet::PseudoJet& Jet);

    void GetBottomInfo(HTopHadronicBranch &TopHadronicBranch, const fastjet::PseudoJet jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTopHadronicBranch Branch;
    hanalysis::HJetTag JetTag;

    float TopWindow ;
    float WMassWindow ;

    //     float JetRadiusParameter;
    void NSubJettiness(HTriplet& triplet);
    SubJettiness NSubJettiness(const fastjet::PseudoJet & jet);
//     void BasicNSubJettiness(const std::vector<fastjet::PseudoJet> & input_particles);
//     void AdvancedNSubJettiness(const std::vector<fastjet::PseudoJet> & input_particles);
//
//
//     void PrintJets(const std::vector <fastjet::PseudoJet>& jets, bool commentOut = false){};
//     void PrintJets(const std::vector <fastjet::PseudoJet>& jets, fastjet::contrib::TauComponents components, bool showTotal = true){};

};

#endif
