#pragma once

#include "JetInfo.hh"
#include "Vector2.hh"
#include "Flag.hh"

namespace analysis
{

enum class Structure
{
    plain = 1,
    constituents = 1 << 1,
    vertices = 1 << 2
};

template<>
struct Flag<Structure> {
    static const bool enable = true;
};

/**
 * @brief Thin wrapper to make fastjet::PseudoJet behave like a Multiplet. Additionally this class astracts away the JetInfo user_info().
 *
 */
class Singlet : public Identification
{

public:

    Singlet() {};

    Singlet(const fastjet::PseudoJet& jet);

    fastjet::PseudoJet& Jet(Structure) const {
        return jet_;
    }

    fastjet::PseudoJet& Jet() const {
        return jet_;
    }

    analysis::Jets Jets() const{
      return {Jet()};
    }

    bool Overlap(const fastjet::PseudoJet& jet) const;

    bool Overlap(const Singlet& singlet) const;

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

    float Radius() const {
        return Radius(Jet());
    }

    float Spread() const {
        return Spread(Jet());
    }

    float VertexRadius() const {
        return Radius(UserInfo().VertexJet());
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

    analysis::Tag Tag() const {
        return UserInfo().Tag();
    }

    float Bdt() const final {
        return UserInfo().Bdt();
    }

    float Ht() const {
        return Jet().pt();
    }

    void SetBdt(float bdt) final;

    float Rapidity() const;

    int Charge() const;

    Singlet singlet() const;

    Singlet singlet(Structure structure) const;

    const JetInfo& UserInfo() const;

    Vector2 Pull() const;

    /**
     * @brief calculate Reference vector for other - this
     * @return Vector2 reference vector
     *
     */
    Vector2 Reference(const fastjet::PseudoJet& reference) const;

private:

    float log(float number) const;

    float Radius(const fastjet::PseudoJet& jet) const;

    float Spread(const fastjet::PseudoJet& jet) const;

    mutable fastjet::PseudoJet jet_;

    JetInfo jet_info_;

};


}

