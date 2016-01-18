/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "multiplets/Singlet.hh"
#include "Line2.hh"

namespace boca
{

class Multiplet : public MultipletBase
{

public:

    void SetLeptonPt(Momentum const& lepton_pt);

    void SetLeptonDeltaR(Angle const& lepton_delta_r);

    Momentum LeptonPt() const;

    Angle LeptonDeltaR() const;

    boca::Singlet const& singlet() const override;

    boca::Jet Jet() const final;

protected:

    virtual Momentum Ht() const override = 0;

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

    Momentum DeltaPt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Momentum Ht(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaRap(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaPhi(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    Angle DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    boca::Mass DeltaM(const boca::MultipletBase& multiplets_1, const boca::MultipletBase& multiplets_2) const;

    Momentum DeltaHt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Rho(MultipletBase const& jet_1, MultipletBase const& jet_2, boca::Jet const& jet) const;

    Angle Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

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

    Momentum lepton_pt_ = 0;

    Angle lepton_delta_r_ = 0;

    Vector2<Angle> Point2(Vector2<Angle> const& point_1, MultipletBase const& multiplets_2) const;

    Angle Distance(Line2<Angle> const& line, boca::Jet const& constituent) const;

};

}
