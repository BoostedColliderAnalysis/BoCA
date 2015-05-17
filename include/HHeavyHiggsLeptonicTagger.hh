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
class analysis::HHeavyHiggsLeptonicTagger : public Tagger
{

public:

    HHeavyHiggsLeptonicTagger();

    HHeavyHiggsLeptonicTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HHeavyHiggsLeptonicTagger();

    std::vector< HHeavyHiggsLeptonicBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector<analysis::HSextet> GetBdt(const std::vector< analysis::Doublet > &doublets, const fastjet::PseudoJet &MissingEt, const analysis::Reader & Reader);

    HHeavyHiggsLeptonicBranch GetBranch(const analysis::HSextet &Sextet);


protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    void SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet);
    analysis::Object::Tag GetTag(const HQuartet &Quartet);

    inline fastjet::PseudoJet GetJet(const double Momentum[4]) const {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        fastjet::PseudoJet Jet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
        return Jet;
    }

    std::vector< HSextet > GetSextet(const analysis::HQuartet &Quartet, const fastjet::PseudoJet &MissingEt, const Jets &Neutrinos, const analysis::Object::Tag Tag);

    std::vector<HSextet> GetSextets(const analysis::HQuartet &Quartet, const fastjet::PseudoJet &MissingEt);

    event22 Structure;

    BottomTagger bottom_tagger_;

    HTopLeptonicTagger TopLeptonicTagger;

    Reader BottomReader;

    Reader TopLeptonicReader;

    HHeavyHiggsLeptonicBranch Branch;

    HJetTag JetTag;

};

#endif
