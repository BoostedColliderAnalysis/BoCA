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

    Singlet(const fastjet::PseudoJet &singlet);

    fastjet::PseudoJet Jet() const {
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

protected:

    virtual inline std::string ClassName() const {
        return "Singlet";
    }

private:

    JetInfo UserInfo() const {
        Jet().user_info<JetInfo>();
    }

    float log(const float Number) const {
        DetectorGeometry detector_geometry;
        if (Number > 0) return std::log10(Number);
        else return std::log10(detector_geometry.TrackerDistanceMin / 10);
    }

    float DeltaR(const fastjet::PseudoJet &jet) const;

    float Spread(const fastjet::PseudoJet &jet) const;

    fastjet::PseudoJet jet_;

};


}

