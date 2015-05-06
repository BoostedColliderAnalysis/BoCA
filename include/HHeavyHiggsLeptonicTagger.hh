# ifndef HHeavyHiggsLeptonicTagger_hh
# define HHeavyHiggsLeptonicTagger_hh

# include "HQuartet.hh"
# include "HSextet.hh"
# include "HTopLeptonicTagger.hh"
# include "WIMPMASS.h"

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class hanalysis::HHeavyHiggsLeptonicTagger : public Tagger
{

public:

    HHeavyHiggsLeptonicTagger();

    HHeavyHiggsLeptonicTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HHeavyHiggsLeptonicTagger();

    std::vector< HHeavyHiggsLeptonicBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector<hanalysis::HSextet> GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const fastjet::PseudoJet &MissingEt, const hanalysis::Reader & Reader);

    HHeavyHiggsLeptonicBranch GetBranch(const hanalysis::HSextet &Sextet);


protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    void SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet);
    hanalysis::HObject::Tag GetTag(const HQuartet &Quartet);

    inline fastjet::PseudoJet GetJet(const double Momentum[4]) const {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        fastjet::PseudoJet Jet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
        return Jet;
    }

    std::vector< HSextet > GetSextet(const hanalysis::HQuartet &Quartet, const fastjet::PseudoJet &MissingEt, const HJets &Neutrinos, const hanalysis::HObject::Tag Tag);

    std::vector<HSextet> GetSextets(const hanalysis::HQuartet &Quartet, const fastjet::PseudoJet &MissingEt);

    event22 Structure;

    HBottomTagger BottomTagger;

    HTopLeptonicTagger TopLeptonicTagger;

    Reader BottomReader;

    Reader TopLeptonicReader;

    HHeavyHiggsLeptonicBranch Branch;

    HJetTag JetTag;

};

#endif
