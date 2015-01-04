# ifndef HChargedHiggsLeptonicTagger_hh
# define HChargedHiggsLeptonicTagger_hh

# include "HTriplet.hh"
// # include "HQuartet31.hh"
# include "HTopLeptonicTagger.hh"
// # include "WIMPMASS.h"

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class hanalysis::HChargedHiggsLeptonicTagger : public HMva
{

public:

    HChargedHiggsLeptonicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HTopLeptonicTagger *const NewTopLeptonicTagger);

    ~HChargedHiggsLeptonicTagger();

    std::vector< HChargedHiggsLeptonicBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const hanalysis::HTriplet &Quartet);

    std::vector<hanalysis::HTriplet> GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const std::vector<fastjet::PseudoJet> Jets, const hanalysis::HReader *const Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

//     void SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet);

    void FillBranch(HChargedHiggsLeptonicBranch *ChargedHiggsBranch, const hanalysis::HTriplet &Triplet);

    hanalysis::HObject::HTag GetTag(const hanalysis::HTriplet &Triplet);

//     inline fastjet::PseudoJet GetJet(const double Momentum[4]) const {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
//         fastjet::PseudoJet Jet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
//         return Jet;
//     }

//     std::vector< HQuartet31 > GetQuartet(const hanalysis::HQuartet &Quartet, const fastjet::PseudoJet &MissingEt, const HJets &Neutrinos, const hanalysis::HObject::HTag Tag);

//     std::vector<HQuartet31> GetQuartets(const hanalysis::HQuartet &Quartet, const fastjet::PseudoJet &MissingEt);

//     event22 Structure;

    HBottomTagger *BottomTagger;

    HTopLeptonicTagger *TopLeptonicTagger;

    HReader *BottomReader;

    HReader *TopLeptonicReader;

    HChargedHiggsLeptonicBranch *Branch;

    HJetTag *JetTag;

};

#endif
