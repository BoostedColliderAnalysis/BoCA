# pragma once

# include "JetInfo.hh"

namespace analysis
{

/**
 * @brief Thin wrapper to make fastjet::PseudoJet behave like a Multiplet. Especially astracts away the JetInfo user_info().
 *
 */
class Singlet : public Identification
{

public:

    Singlet() {};

    Singlet(const fastjet::PseudoJet &jet);

    fastjet::PseudoJet &Jet() const {
        return jet_;
    }

    bool Overlap(const fastjet::PseudoJet &jet) const;

    bool Overlap(const Singlet &singlet) const;

    float VertexMass() const {
        return UserInfo().VertexMass();
    }

    float MaxDisplacement() const {
        return log(UserInfo().MaxDisplacement());
    }

    float MeanDisplacement() const {
        return log(UserInfo().MeanDisplacement());
    }

    float SumDisplacement() const {
        return log(UserInfo().SumDisplacement());
    }

    float Multiplicity() const {
        return UserInfo().VertexNumber();
    }

    float DeltaR() const {
        return DeltaR(Jet());
    }

    float Spread() const {
        return Spread(Jet());
    }

    float VertexDeltaR() const {
        return DeltaR(UserInfo().VertexJet());
    }

    float VertexSpread() const {
        return Spread(UserInfo().VertexJet());
    }

    float EnergyFraction() const {
        return UserInfo().VertexEnergy() / Jet().e();
    }

    float EmRadius() const {
        return UserInfo().ElectroMagneticRadius(Jet());
    }

    float TrackRadius() const {
        return UserInfo().TrackRadius(Jet());
    }

    float MomentumFraction() const {
        return UserInfo().LeadingTrackMomentumFraction();
    }

    float CoreEnergyFraction() const {
        return UserInfo().CoreEnergyFraction(Jet());
    }

    float EmFraction() const {
        return UserInfo().ElectroMagneticFraction();
    }

    float ClusterMass() const {
        return UserInfo().ClusterMass();
    }

    float TrackMass() const {
        return UserInfo().TrackMass();
    }

    float FlightPath() const {
        return log(UserInfo().MeanDisplacement());
    }

    float TrtHtFraction() const {
        return Spread(UserInfo().VertexJet());
    }

    float Tag() const {
        return UserInfo().Tag();
    }

    float Bdt() const {
        return UserInfo().Bdt();
    }

    float Ht() const {
        return Jet().pt();
    }

    void SetBdt(const float bdt);

    float Rapidity() const {
        float rap = Jet().rap();
        if (rap > 100) return 0;
        return rap;
    }

    int Charge()const {
//       return UserInfo().Charge();
      return sgn(UserInfo().Charge());
    }

protected:

    virtual  std::string ClassName() const {
        return "Singlet";
    }

private:

    const JetInfo &UserInfo() const;

    float log(const float number) const;

    float DeltaR(const fastjet::PseudoJet &jet) const;

    float Spread(const fastjet::PseudoJet &jet) const;

    mutable fastjet::PseudoJet jet_;

};


}

