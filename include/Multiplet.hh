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

    virtual fastjet::PseudoJet ConstituentJet() const = 0;

    /**
     * @brief join the two jets
     *
     * @details this function becomes expensive very fast.
     *          save the result in an temporary variable
     *
     */
    fastjet::PseudoJet ConstituentJet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) const;

    fastjet::PseudoJet Jet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) const;


    Vector2 Pull() const override;

    float DeltaPt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Ht(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaRap(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaPhi(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaM(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float DeltaHt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Rho(MultipletBase const& jet_1, MultipletBase const& jet_2, fastjet::PseudoJet const& jet) const;

    float PullDifference(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float PullSum(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Dipolarity(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, fastjet::PseudoJet const& jet) const;

    int Charge(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float BottomBdt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    void SetConstituentJet(fastjet::PseudoJet const& jet) const;

    void SetPlainJet(fastjet::PseudoJet const& jet) const;

//     void SetSinglet(fastjet::PseudoJet const& jet) const;

    /**
     * @brief store intermediate results
     *
     */
    mutable Singlet singlet_;

//     mutable fastjet::PseudoJet constiuent_jet_;

    mutable fastjet::PseudoJet jet_;

    mutable bool has_singlet_ = false;

    mutable bool has_jet_= false;

private:

    float Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const;

    float Distance(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, Vector2 const& point_0) const;

};

}
