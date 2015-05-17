# ifndef HFourVector_hh
# define HFourVector_hh

# include "ExRootAnalysis/ExRootClasses.h"

# include "Object.hh"
# include "ClonesArrays.hh"
# include "HJetTag.hh"
# include "JetInfo.hh"

# include "HDelphes.hh"

// namespace delphes{
// # include "classes/DelphesClasses.h"
// }
/**
 * @brief converts Clones to LorentzVectors and fastjet::PseudoJets
 *
 */
class analysis::HFourVector : virtual public Object
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


    void Newevent(const ClonesArrays &NewClonesArrays);

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByEnergy(const TParticle &Particle) const {

        Print(kDebug, "Get Lorentz Vector by Energy");

        TLorentzVector LorentzVector;

        const float Pt = Particle.PT;
        const float Eta = Particle.Eta;
        const float Phi = Particle.Phi;
        const float Energy = Particle.E;

        LorentzVector.SetPtEtaPhiE(Pt, Eta, Phi, Energy);

        if (CheckFourVectors) {

            if (LorentzVector.Pt() - Pt > Check) Print(kError, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > Check) Print(kError, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > Check) Print(kError, "Phi", Phi, LorentzVector.Phi());
            if (LorentzVector.E() - Energy > Check) Print(kError, "Energy", Energy, LorentzVector.E());

        }

        return LorentzVector;

    }

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByMass(const TParticle &Particle, const float Mass) const {

        Print(kDebug, "Get Lorentz Vector by Mass");

        TLorentzVector LorentzVector;

        const float Pt = Particle.PT;
        const float Eta = Particle.Eta;
        const float Phi = Particle.Phi;

        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.Pt() - Pt > Check) Print(kError, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > Check) Print(kError, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > Check) Print(kError, "Phi", Phi, LorentzVector.Phi());

        }

        return LorentzVector;

    }

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByMass(const TParticle &Particle) const {

        Print(kDebug, "Get Lorentz Vector by Mass");

        const float Mass = Particle.Mass;

        const TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.M() - Mass > MassCheck) Print(kError, "Mass", Mass, LorentzVector.M());

        }

        return LorentzVector;

    }

    template<typename TParticle>
    TLorentzVector GetLorentzVectorByM(const TParticle &Particle) const {

        Print(kDebug, "Get Lorentz Vector by Mass");

        const float Mass = Particle.M;

        const TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, Mass);

        if (CheckFourVectors) {

            if (LorentzVector.M() - Mass > MassCheck) Print(kError, "Mass", Mass, LorentzVector.M());

        }

        return LorentzVector;

    }
//     TLorentzVector GetLorentzVector(const MissingET *const Particle) const;

    TLorentzVector GetLorentzVector(const TRootElectron &Particle) const;
    TLorentzVector GetLorentzVector(const TRootGenJet &Particle) const;
    TLorentzVector GetLorentzVector(const TRootGenParticle &Particle) const;
    TLorentzVector GetLorentzVector(const TRootJet &Particle) const;
    TLorentzVector GetLorentzVector(const TRootLHEFParticle &Particle) const;
    TLorentzVector GetLorentzVector(const TRootMuon &Particle) const;
    TLorentzVector GetLorentzVector(const TRootPhoton &Particle) const;
    TLorentzVector GetLorentzVector(const TRootTau &Particle) const;
//     fastjet::PseudoJet GetPseudoJet(const MissingET & Particle) const;
    fastjet::PseudoJet GetPseudoJet(const TRootElectron &Particle) const;
    fastjet::PseudoJet GetPseudoJet(const TRootGenJet &Particle) const;
    fastjet::PseudoJet GetPseudoJet(const TRootGenParticle &Particle) const;
    fastjet::PseudoJet GetPseudoJet(const TRootJet &Particle) const;
    fastjet::PseudoJet GetPseudoJet(const TRootLHEFParticle &Particle) const;
    fastjet::PseudoJet GetPseudoJet(const TRootMuon &Particle) const;
    fastjet::PseudoJet GetPseudoJet(const TRootPhoton &Particle) const;
    fastjet::PseudoJet GetPseudoJet(const TRootTau &Particle) const;

    Family GetBranchFamily(const TObject &Object);

    Family GetBranchFamily(Family &BranchId, int Position);

    template<typename TData>
    void PrintCell(TData const Data) const {

        std::cout << std::right << std::setw(9) << std::setfill(' ') << Data;

    }

    void PrintTruthLevel(const int severity) const;

    std::string PrintParticle(const int Position) const;

    const ClonesArrays& clones_arrays() const{
      return *clones_arrays_;
    }

    /**
     * @brief Clones Arrays
     *
     */
    const ClonesArrays *clones_arrays_;

    std::vector<Family> Topology;

    int Source;

    HJetTag *JetTag;

    enum HJetDetails {Plain, Tagging, Isolation, Structure, TaggingIsolation, TaggingStructure};

    const bool CheckFourVectors;

    const float Check;

    const float MassCheck;

private:

    virtual inline std::string ClassName() const {
        return "HFourVector";
    };

};

#endif
