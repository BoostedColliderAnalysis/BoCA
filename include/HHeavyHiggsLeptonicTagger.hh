# pragma once

# include "Quartet22.hh"
# include "Sextet.hh"
# include "HTopLeptonicTagger.hh"
# include "WIMPMASS.h"

namespace analysis {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HHeavyHiggsLeptonicTagger : public Tagger
{

public:

    HHeavyHiggsLeptonicTagger();

    HHeavyHiggsLeptonicTagger(const BottomTagger &NewBottomTagger, const HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HHeavyHiggsLeptonicTagger();

    std::vector< HHeavyHiggsLeptonicBranch > GetBranches(Event &event, const Object::Tag Tag);

    std::vector<Sextet> GetBdt(const std::vector< Doublet > &doublets, const fastjet::PseudoJet &MissingEt, const Reader & Reader);

    HHeavyHiggsLeptonicBranch GetBranch(const Sextet &sextet);


protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    void SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet);
    Object::Tag GetTag(const Quartet22 &quartet);

    inline fastjet::PseudoJet GetJet(const double Momentum[4]) const {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        fastjet::PseudoJet Jet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
        return Jet;
    }

    std::vector< Sextet > Getsextet(const Quartet22 &quartet, const fastjet::PseudoJet &MissingEt, const Jets &Neutrinos, const Object::Tag Tag);

    std::vector<Sextet> Getsextets(const Quartet22 &quartet, const fastjet::PseudoJet &MissingEt);

    event22 Structure;

    BottomTagger bottom_tagger_;

    HTopLeptonicTagger TopLeptonicTagger;

    Reader BottomReader;

    Reader TopLeptonicReader;

    HHeavyHiggsLeptonicBranch Branch;

    JetTag jet_tag;

};

}
