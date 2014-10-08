# ifndef HFourVector_hh
# define HFourVector_hh

# include "HObject.hh"
# include "ExRootAnalysis/ExRootClasses.h"
# include "classes/DelphesClasses.h"

class HFourVector : virtual public HObject
{

public:

    HFourVector();

    ~HFourVector();


protected:
    
    /**
     * @brief Get a PseudoJet from a TLorentzVector
     *
     * @param  TLorentzVector
     * @return fastjet::PseudoJet
     */
    PseudoJet GetPseudoJet(const TLorentzVector&) const;
    
    TLorentzVector GetConstituent(const TObject&) const;
    
    PseudoJet GetConstituentJet(const TObject&) const;

    template<typename Template>
    TLorentzVector GetLorentzVectorByEnergy(const Template *Particle) {

        Print(3, "Get Lorentz Vector by Energy");

        TLorentzVector LorentzVector;

        float Pt = Particle->PT;
        float Eta = Particle->Eta;
        float Phi = Particle->Phi;
        float Energy = Particle->E;

        LorentzVector.SetPtEtaPhiE(Pt, Eta, Phi, Energy);

        if (CheckFourVectors) {

            if (LorentzVector.Pt() - Pt > Check) Print(0, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > Check) Print(0, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > Check) Print(0, "Phi", Phi, LorentzVector.Phi());
            if (LorentzVector.E() - Energy > Check) Print(0, "Energy", Energy, LorentzVector.E());

        }

        return LorentzVector;

    }

    template<typename Template>
    TLorentzVector GetLorentzVectorByMass(const Template *Particle, float Mass) {

        Print(3, "Get Lorentz Vector by Mass");

        TLorentzVector LorentzVector;

        float Pt = Particle->PT;
        float Eta = Particle->Eta;
        float Phi = Particle->Phi;

        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.Pt() - Pt > Check) Print(0, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > Check) Print(0, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > Check) Print(0, "Phi", Phi, LorentzVector.Phi());

        }

        return LorentzVector;

    }

    template<typename Template>
    TLorentzVector GetLorentzVectorByMass(const Template *Particle) {

        Print(3, "Get Lorentz Vector by Mass");

        float Mass = Particle->Mass;

        TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.M() - Mass > MassCheck) Print(0, "Mass", Mass, LorentzVector.M());

        }

        return LorentzVector;

    }

    template<typename Template>
    TLorentzVector GetLorentzVectorByM(const Template *Particle) {

        Print(3, "Get Lorentz Vector by Mass");

        float Mass = Particle->M;

        TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.M() - Mass > MassCheck) Print(0, "Mass", Mass, LorentzVector.M());

        }

        return LorentzVector;

    }




    template<typename Template>
    PseudoJet GetPseudoJetByEnergy(const Template *Particle, float Energy) {

        Print(3, "Get Pseudo Jet by Energy");

        float Pt = Particle->PT;
        float Eta = Particle->Eta;
        float Phi = Particle->Phi;

        PseudoJet Jet = PseudoJet(Pt * cos(Phi), Pt * sin(Phi), Pt * sinh(Eta), Energy);

        if (CheckFourVectors) {

            if (Jet.pt() - Pt > Check) Print(0, "Pt", Pt, Jet.pt());
            if (Jet.eta() - Eta > Check) Print(0, "Eta", Eta, Jet.eta());
            if (Jet.phi_std() - Phi > Check) Print(0, "Phi", Phi, Jet.phi_std());

        }

        return Jet;

    }


    template<typename Template>
    PseudoJet GetPseudoJetByEnergy(const Template *Particle) {

        Print(3, "Get Pseudo Jet by Energy");

        float Energy = Particle->E;

        PseudoJet Jet = GetPseudoJetByEnergy(Particle, Energy);

        return Jet;

    }

    template<typename Template>
    PseudoJet GetPseudoJetByMass(const Template *Particle, float Mass) {

        Print(3, "Get Pseudo Jet by Mass");

        float Pt = Particle->PT;
        float Eta = Particle->Eta;
//         float Energy = sqrt((2 * pow(Mass, 2) + pow(Pt, 2) * (1 + cosh(2 * Eta))) / 2);
        float Energy = sqrt(pow(Mass, 2) + pow(Pt * cosh(Eta), 2));

        PseudoJet Jet = GetPseudoJetByEnergy(Particle, Energy);

        if (CheckFourVectors) {

            if (Jet.e() - Energy > Check) Print(0, "Energy", Energy, Jet.e());

        }

        return Jet;

    }

    template<typename Template>
    PseudoJet GetPseudoJetByMass(const Template *Particle) {

        Print(3, "Get Pseudo Jet by Mass");

        float Mass = Particle->Mass;

        PseudoJet Jet = GetPseudoJetByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (Jet.m() - Mass > MassCheck) Print(0, "Mass", Mass, Jet.m());

        }

        return Jet;

    }

    template<typename Template>
    PseudoJet GetPseudoJetByM(const Template *Particle) {

        Print(3, "Get Pseudo Jet By Mass");

        float Mass = Particle->M;

        PseudoJet Jet = GetPseudoJetByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (Jet.m() - Mass > MassCheck) Print(0, "Mass", Mass, Jet.m());

        }

        return Jet;

    }

    TLorentzVector GetLorentzVector(TRootElectron *);

    TLorentzVector GetLorentzVector(TRootGenJet *);

    TLorentzVector GetLorentzVector(TRootGenParticle *);

    TLorentzVector GetLorentzVector(TRootJet *);

    TLorentzVector GetLorentzVector(TRootLHEFParticle *);

    TLorentzVector GetLorentzVector(TRootMuon *);

    TLorentzVector GetLorentzVector(TRootPhoton *);

    TLorentzVector GetLorentzVector(TRootTau *);

    PseudoJet GetPseudoJet(TRootElectron *);

    PseudoJet GetPseudoJet(TRootGenJet *);

    PseudoJet GetPseudoJet(TRootGenParticle *);

    PseudoJet GetPseudoJet(TRootJet *);

    PseudoJet GetPseudoJet(TRootLHEFParticle *);

    PseudoJet GetPseudoJet(TRootMuon *);

    PseudoJet GetPseudoJet(TRootPhoton *);

    PseudoJet GetPseudoJet(TRootTau *);

    const bool CheckFourVectors;

    const float Check;

    const float MassCheck;

private:

    virtual string ClassName() const {
        
        return ("HFourVector");
        
    };

};

#endif
