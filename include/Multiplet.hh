/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "MultipletBase.hh"
#include "Singlet.hh"
#include "Line2.hh"

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

    boca::Jet Jet() const final {
        if (!has_jet_) SetPlainJet();
        return jet_;
    }

protected:

    virtual float Ht() const override = 0;

    virtual int Charge() const override = 0;

    virtual float BottomBdt() const override = 0;

    virtual std::vector<boca::Jet> Jets() const = 0;

    /**
     * @brief join the two jets
     *
     * @details this function becomes expensive very fast.
     *          save the result in an temporary variable
     *
     */
    boca::Singlet Singlet(boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const;

    boca::Jet Jet(boca::Jet const& jet_1, boca::Jet const& jet_2) const;

    Vector2<float> Pull() const override;

    Momentum DeltaPt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Ht(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaRap(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaPhi(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    boca::Mass DeltaM(const boca::MultipletBase& multiplets_1, const boca::MultipletBase& multiplets_2) const;

    float DeltaHt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Rho(MultipletBase const& jet_1, MultipletBase const& jet_2, boca::Jet const& jet) const;

    Angle PullDifference(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle PullSum(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Dipolarity(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, boca::Singlet const& singlet) const;

    int Charge(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float BottomBdt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    void SetSinglet(boca::Singlet const& singlet) const;

    virtual void SetSinglet() const = 0;

    void SetPlainJet(boca::Jet const& jet) const;

    virtual void SetPlainJet() const = 0;

    /**
     * @brief store intermediate results
     *
     */
    mutable boca::Singlet singlet_;

    mutable boca::Jet jet_;

    mutable bool has_singlet_ = false;

    mutable bool has_jet_ = false;

private:

    Angle Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Vector2<float> Point2(Vector2<float> const& point_1, MultipletBase const& multiplets_2) const;

    float Distance(Line2<float> const& line, boca::Jet const& constituent) const;

};

}
