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

protected:

    virtual float Ht() const override = 0;

    virtual int Charge() const override = 0;

    virtual float BottomBdt() const override = 0;

    virtual std::vector<fastjet::PseudoJet> Jets() const = 0;

    virtual fastjet::PseudoJet Jet() const override = 0;

    fastjet::PseudoJet Jet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) const;

    Vector2 Pull() const override;

    float DeltaPt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Ht(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaRap(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaPhi(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaM(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaHt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Rho(MultipletBase const& jet_1, MultipletBase const& jet_2) const;

    float PullDifference(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float PullSum(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Dipolarity(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    int Charge(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float BottomBdt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    void SetResult(fastjet::PseudoJet const& jet) const {
      jet_ = jet;
      SetSinglet(jet);
      has_jet_ = true;
    }

    void SetSinglet(fastjet::PseudoJet const& jet) const {
      singlet_ = Singlet(jet);
    }


    /**
     * @brief store intermediate results
     *
     */
    mutable Singlet singlet_;

    mutable fastjet::PseudoJet jet_;

    mutable bool has_jet_ = false;

private:

    float Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Distance(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, Vector2 const& point_0) const;

};

}
