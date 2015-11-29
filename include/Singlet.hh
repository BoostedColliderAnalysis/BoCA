/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "JetInfo.hh"
#include "MultipletBase.hh"

namespace boca
{

/**
 * @brief Thin wrapper to make Jet behave like a Multiplet. Additionally this class astracts away the JetInfo user_info().
 *
 */
class Singlet : public MultipletBase
{

public:

    Singlet() {};

    Singlet(fastjet::PseudoJet const& jet);

    Singlet(boca::Jet const& jet);

    boca::Jet Jet() const {
        return jet_;
    }

    boca::Jet ConstituentJet() const {
        return jet_;
    }

    std::vector<boca::Jet> Jets() const {
        return {Jet()};
    }

    bool Overlap(boca::Jet const& jet) const;

    bool Overlap(Singlet const& singlet) const;

    float VertexMass() const {
        return UserInfo().VertexMass() / GeV;
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
        return Radius(Jet()) / rad;
    }

    float Spread() const {
        return Spread(Jet());
    }

    float VertexRadius() const {
        return Radius(UserInfo().VertexJet()) / rad;
    }

    float VertexSpread() const {
        return Spread(UserInfo().VertexJet());
    }

    float EnergyFraction() const {
        return UserInfo().VertexEnergy() / Jet().Energy();
    }

    float EmRadius() const {
        return UserInfo().ElectroMagneticRadius(Jet()) / rad;
    }

    float TrackRadius() const {
        return UserInfo().TrackRadius(Jet()) / rad;
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
        return UserInfo().ClusterMass() / GeV;
    }

    float TrackMass() const {
        return UserInfo().TrackMass() / GeV;
    }

    float FlightPath() const {
        return log(UserInfo().MeanDisplacement());
    }

    float TrtHtFraction() const {
        return Spread(UserInfo().VertexJet());
    }

    boca::Tag Tag() const {
        return UserInfo().Tag();
    }

    float Bdt() const final {
        if (UserInfo().Bdt() != UserInfo().Bdt()) return -1;
        if (UserInfo().Bdt() != InitialValue()) return UserInfo().Bdt();
        return -1;
    }

    float Ht() const {
        return Jet().pt();
    }

    void SetBdt(float bdt) final;

    int Charge() const;

    Singlet const& singlet() const;

    JetInfo const& UserInfo() const;

    Vector2<AngleSquare> Pull() const override;

    boca::Jet& Jet() {
        return jet_;
    }

    float BottomBdt() const final {
        return Bdt();
    }

    float Rapidity() const {
        return Rap() / rad;
    }

private:

    float log(Length length) const;

    Angle Radius(boca::Jet const& jet) const;

    float Spread(boca::Jet const& jet) const;

    boca::Jet jet_;

    JetInfo jet_info_;

    // save expensive results in mutable member variables

    mutable Vector2<AngleSquare> pull_;

    mutable bool has_pull_ = false;

};


}

