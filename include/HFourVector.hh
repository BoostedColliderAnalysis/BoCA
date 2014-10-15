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
    PseudoJet GetPseudoJet(const TLorentzVector &) const;

    TLorentzVector GetConstituent(const TObject *const) const;

    PseudoJet GetConstituentJet(const TObject *const) const;

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByEnergy(const TParticle *const Particle) const {

        Print(3, "Get Lorentz Vector by Energy");

        TLorentzVector LorentzVector;

        const float Pt = Particle->PT;
        const float Eta = Particle->Eta;
        const float Phi = Particle->Phi;
        const float Energy = Particle->E;

        LorentzVector.SetPtEtaPhiE(Pt, Eta, Phi, Energy);

        if (CheckFourVectors) {

            if (LorentzVector.Pt() - Pt > Check) Print(0, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > Check) Print(0, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > Check) Print(0, "Phi", Phi, LorentzVector.Phi());
            if (LorentzVector.E() - Energy > Check) Print(0, "Energy", Energy, LorentzVector.E());

        }

        return LorentzVector;

    }

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByMass(const TParticle *const Particle, const float Mass) const {

        Print(3, "Get Lorentz Vector by Mass");

        TLorentzVector LorentzVector;

        const float Pt = Particle->PT;
        const float Eta = Particle->Eta;
        const float Phi = Particle->Phi;

        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.Pt() - Pt > Check) Print(0, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > Check) Print(0, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > Check) Print(0, "Phi", Phi, LorentzVector.Phi());

        }

        return LorentzVector;

    }

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByMass(const TParticle *const Particle) const {

        Print(3, "Get Lorentz Vector by Mass");

        const float Mass = Particle->Mass;

        const TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.M() - Mass > MassCheck) Print(0, "Mass", Mass, LorentzVector.M());

        }

        return LorentzVector;

    }

    template<typename Template>
    TLorentzVector GetLorentzVectorByM(const Template *const Particle) const {

        Print(3, "Get Lorentz Vector by Mass");

        const float Mass = Particle->M;

        const TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.M() - Mass > MassCheck) Print(0, "Mass", Mass, LorentzVector.M());

        }

        return LorentzVector;

    }




//     template<typename TParticle>
//     PseudoJet GetPseudoJetByEnergy(const TParticle *const Particle, const float Energy) const {
// 
//         Print(3, "Get Pseudo Jet by Energy");
// 
//         const float Pt = Particle->PT;
//         const float Eta = Particle->Eta;
//         const float Phi = Particle->Phi;
// 
//         const PseudoJet Jet = PseudoJet(Pt * cos(Phi), Pt * sin(Phi), Pt * sinh(Eta), Energy);
// 
//         if (CheckFourVectors) {
// 
//             if (Jet.pt() - Pt > Check) Print(0, "Pt", Pt, Jet.pt());
//             if (Jet.eta() - Eta > Check) Print(0, "Eta", Eta, Jet.eta());
//             if (Jet.phi_std() - Phi > Check) Print(0, "Phi", Phi, Jet.phi_std());
// 
//         }
// 
//         return Jet;
// 
//     }
// 
// 
//     template<typename TParticle>
//     PseudoJet GetPseudoJetByEnergy(const TParticle *const Particle) const {
// 
//         Print(3, "Get Pseudo Jet by Energy");
// 
//         const float Energy = Particle->E;
// 
//         const PseudoJet Jet = GetPseudoJetByEnergy(Particle, Energy);
// 
//         return Jet;
// 
//     }
// 
//     template<typename TParticle>
//     PseudoJet GetPseudoJetByMass(const TParticle *const Particle, const float Mass) const {
// 
//         Print(3, "Get Pseudo Jet by Mass");
// 
//         const float Pt = Particle->PT;
//         const float Eta = Particle->Eta;
//         const float Energy = sqrt(pow(Mass, 2) + pow(Pt * cosh(Eta), 2));
// 
//         const PseudoJet Jet = GetPseudoJetByEnergy(Particle, Energy);
// 
//         if (CheckFourVectors) {
// 
//             if (Jet.e() - Energy > Check) Print(0, "Energy", Energy, Jet.e());
// 
//         }
// 
//         return Jet;
// 
//     }
// 
//     template<typename TParticle>
//     PseudoJet GetPseudoJetByMass(const TParticle *const Particle) const {
// 
//         Print(3, "Get Pseudo Jet by Mass");
// 
//         const float Mass = Particle->Mass;
// 
//         const PseudoJet Jet = GetPseudoJetByMass(Particle, Mass);
// 
//         if (CheckFourVectors) {
// 
//             if (Jet.m() - Mass > MassCheck) Print(0, "Mass", Mass, Jet.m());
// 
//         }
// 
//         return Jet;
// 
//     }
// 
//     template<typename TParticle>
//     PseudoJet GetPseudoJetByM(const TParticle *const Particle) const {
// 
//         Print(3, "Get Pseudo Jet By Mass");
// 
//         const float Mass = Particle->M;
// 
//         const PseudoJet Jet = GetPseudoJetByMass(Particle, Mass);
// 
//         if (CheckFourVectors) {
// 
//             if (Jet.m() - Mass > MassCheck) Print(0, "Mass", Mass, Jet.m());
// 
//         }
// 
//         return Jet;
// 
//     }

    TLorentzVector GetLorentzVector(const TRootElectron *const) const;

    TLorentzVector GetLorentzVector(const TRootGenJet *const) const;

    TLorentzVector GetLorentzVector(const TRootGenParticle *const) const;

    TLorentzVector GetLorentzVector(const TRootJet *const) const;

    TLorentzVector GetLorentzVector(const TRootLHEFParticle *const) const;

    TLorentzVector GetLorentzVector(const TRootMuon *const) const;

    TLorentzVector GetLorentzVector(const TRootPhoton *const) const;

    TLorentzVector GetLorentzVector(const TRootTau *const) const;

    PseudoJet GetPseudoJet(const TRootElectron *const) const;

    PseudoJet GetPseudoJet(const TRootGenJet *const) const;

    PseudoJet GetPseudoJet(const TRootGenParticle *const) const;

    PseudoJet GetPseudoJet(const TRootJet *const) const;

    PseudoJet GetPseudoJet(const TRootLHEFParticle *const) const;

    PseudoJet GetPseudoJet(const TRootMuon *const) const;

    PseudoJet GetPseudoJet(const TRootPhoton *const) const;

    PseudoJet GetPseudoJet(const TRootTau *const) const;

    const bool CheckFourVectors;

    const float Check;

    const float MassCheck;

private:

    virtual string ClassName() const {

        return ("HFourVector");

    };

};

#endif
