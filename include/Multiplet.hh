/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "MultipletBase.hh"
#include "Singlet.hh"

namespace boca
{

class Multiplet : public MultipletBase
{

public:

    float LeptonPt = 0;

    float LeptonDeltaR = 0;

    boca::Singlet const& singlet() const override {
        if (!has_singlet_) SetSinglet();
        return singlet_;
    }

    fastjet::PseudoJet Jet() const final {
        if (!has_jet_) SetPlainJet();
        return jet_;
    }

protected:

    virtual float Ht() const override = 0;

    virtual int Charge() const override = 0;

    virtual float BottomBdt() const override = 0;

    virtual std::vector<fastjet::PseudoJet> Jets() const = 0;

    /**
     * @brief join the two jets
     *
     * @details this function becomes expensive very fast.
     *          save the result in an temporary variable
     *
     */
    boca::Singlet Singlet(boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const;

    fastjet::PseudoJet Jet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) const;

    Vector2 Pull() const override;

    Momentum DeltaPt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Ht(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaRap(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaPhi(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    boca::Mass DeltaM(const boca::MultipletBase& multiplets_1, const boca::MultipletBase& multiplets_2) const;

    float DeltaHt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Rho(MultipletBase const& jet_1, MultipletBase const& jet_2, fastjet::PseudoJet const& jet) const;

    float PullDifference(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float PullSum(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Dipolarity(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, boca::Singlet const& singlet) const;

    int Charge(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float BottomBdt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    void SetSinglet(boca::Singlet const& singlet) const;

    virtual void SetSinglet() const = 0;

    void SetPlainJet(fastjet::PseudoJet const& jet) const;

    virtual void SetPlainJet() const = 0;

    /**
     * @brief store intermediate results
     *
     */
    mutable boca::Singlet singlet_;

    mutable fastjet::PseudoJet jet_;

    mutable bool has_singlet_ = false;

    mutable bool has_jet_ = false;

private:

    float Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle Distance(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, fastjet::PseudoJet const& constituent, Angle delta_r) const;

    Angle Distance(Vector2 const& point_1, Vector2 const& point_2, Vector2 const& point_0, Angle delta_r) const;

};

}
