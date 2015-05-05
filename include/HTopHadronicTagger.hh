# ifndef HTopHadronicTagger_hh
# define HTopHadronicTagger_hh

# include "HTriplet.hh"
# include "HBottomTagger.hh"
# include "HWHadronicTagger.hh"

#include "fastjet/contrib/MeasureFunction.hh"

/**
 * @brief Hadronic top BDT tagger
 *
 */
class hanalysis::HTopHadronicTagger : public Tagger
{

public:

    HTopHadronicTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWHadronicTagger &NewWTagger);

    std::vector<HTopHadronicBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, float pre_cut = 0);

    std::vector<HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::HReader & TopHadronicReader);

    HTriplet GetBdt(hanalysis::HTriplet &Triplet, const hanalysis::HReader &TopHadronicReader);

    std::vector<HTriplet> GetBdt(const HJets &Jets, const hanalysis::HReader &TopHadronicReader, hanalysis::HWHadronicTagger &WTagger, hanalysis::HReader &WReader, hanalysis::HBottomTagger &BottomTagger, hanalysis::HReader &BottomReader);

//     std::vector<HTriplet> GetBdt(HJets &Jets, const HReader &TopHadronicReader);


    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HTopHadronicBranch *) EventClonesArray.At(Entry))->Bdt;
    }

    HBottomTagger BottomTagger;
    HWHadronicTagger WTagger;

    HReader  BottomReader;
    HReader  WReader;

    HTopHadronicBranch GetBranch(const hanalysis::HTriplet &triplet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronicTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const hanalysis::HTriplet &);

    Tag GetTag(const fastjet::PseudoJet& Jet);

    void GetBottomInfo(HTopHadronicBranch &TopHadronicBranch, const fastjet::PseudoJet jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTopHadronicBranch Branch;
    hanalysis::HJetTag JetTag;

    float TopWindow ;
    float WMassWindow ;

    bool Boost = false;

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
