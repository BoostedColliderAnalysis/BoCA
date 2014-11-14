# ifndef HFourVector_hh
# define HFourVector_hh

# include "ExRootAnalysis/ExRootClasses.h"

# include "classes/DelphesClasses.h"

# include "HObject.hh"

/**
 * @brief converts Clones to LorentzVectors and fastjet::PseudoJets
 *
 */
class hanalysis::HFourVector : virtual public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HFourVector();

    /**
     * @brief Destructor
     *
     */
    ~HFourVector();


protected:

    /**
     * @brief Get a fastjet::PseudoJet from a TLorentzVector
     *
     * @param  TLorentzVector
     * @return fastjet::PseudoJet
     */
    fastjet::PseudoJet GetPseudoJet(const TLorentzVector &) const;

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByEnergy(const TParticle *const Particle) const {

        Print(HDebug, "Get Lorentz Vector by Energy");

        TLorentzVector LorentzVector;

        const float Pt = Particle->PT;
        const float Eta = Particle->Eta;
        const float Phi = Particle->Phi;
        const float Energy = Particle->E;

        LorentzVector.SetPtEtaPhiE(Pt, Eta, Phi, Energy);

        if (CheckFourVectors) {

            if (LorentzVector.Pt() - Pt > Check) Print(HError, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > Check) Print(HError, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > Check) Print(HError, "Phi", Phi, LorentzVector.Phi());
            if (LorentzVector.E() - Energy > Check) Print(HError, "Energy", Energy, LorentzVector.E());

        }

        return LorentzVector;

    }

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByMass(const TParticle *const Particle, const float Mass) const {

        Print(HDebug, "Get Lorentz Vector by Mass");

        TLorentzVector LorentzVector;

        const float Pt = Particle->PT;
        const float Eta = Particle->Eta;
        const float Phi = Particle->Phi;

        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.Pt() - Pt > Check) Print(HError, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > Check) Print(HError, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > Check) Print(HError, "Phi", Phi, LorentzVector.Phi());

        }

        return LorentzVector;

    }

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByMass(const TParticle *const Particle) const {

        Print(HDebug, "Get Lorentz Vector by Mass");

        const float Mass = Particle->Mass;

        const TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.M() - Mass > MassCheck) Print(HError, "Mass", Mass, LorentzVector.M());

        }

        return LorentzVector;

    }

    template<typename Template>
    TLorentzVector GetLorentzVectorByM(const Template *const Particle) const {

        Print(HDebug, "Get Lorentz Vector by Mass");

        const float Mass = Particle->M;

        const TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.M() - Mass > MassCheck) Print(HError, "Mass", Mass, LorentzVector.M());

        }

        return LorentzVector;

    }

    TLorentzVector GetLorentzVector(const TRootElectron *const) const;

    TLorentzVector GetLorentzVector(const TRootGenJet *const) const;

    TLorentzVector GetLorentzVector(const TRootGenParticle *const) const;

    TLorentzVector GetLorentzVector(const TRootJet *const) const;

    TLorentzVector GetLorentzVector(const TRootLHEFParticle *const) const;

    TLorentzVector GetLorentzVector(const TRootMuon *const) const;

    TLorentzVector GetLorentzVector(const TRootPhoton *const) const;

    TLorentzVector GetLorentzVector(const TRootTau *const) const;

    fastjet::PseudoJet GetPseudoJet(const TRootElectron *const) const;

    fastjet::PseudoJet GetPseudoJet(const TRootGenJet *const) const;

    fastjet::PseudoJet GetPseudoJet(const TRootGenParticle *const) const;

    fastjet::PseudoJet GetPseudoJet(const TRootJet *const) const;

    fastjet::PseudoJet GetPseudoJet(const TRootLHEFParticle *const) const;

    fastjet::PseudoJet GetPseudoJet(const TRootMuon *const) const;

    fastjet::PseudoJet GetPseudoJet(const TRootPhoton *const) const;

    fastjet::PseudoJet GetPseudoJet(const TRootTau *const) const;

    const bool CheckFourVectors;

    const float Check;

    const float MassCheck;

private:

    virtual inline std::string ClassName() const {
        return "HFourVector";
    };

};

#endif
