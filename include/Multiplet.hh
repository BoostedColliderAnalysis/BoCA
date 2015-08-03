#pragma once

#include "MultipletBase.hh"

namespace analysis
{

class Multiplet : public MultipletBase
{

public:

protected:

    virtual float Ht() const override = 0;

    virtual int Charge() const override = 0;

    virtual float BottomBdt() const override = 0;

    virtual std::vector<fastjet::PseudoJet> Jets() const = 0;

    virtual fastjet::PseudoJet Jet() const override = 0;

    fastjet::PseudoJet Jet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2) const;

    Vector2 Pull() const override;

    float DeltaPt(const Multiplet& multiplets_1, const Multiplet& multiplets_2) const;

    float Ht(const analysis::MultipletBase& multiplets_1, const analysis::MultipletBase& multiplets_2) const;

    float DeltaRap(const analysis::MultipletBase& multiplets_1, const analysis::MultipletBase& multiplets_2) const;

    float DeltaPhi(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

    float DeltaR(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

    float DeltaM(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

    float DeltaHt(const analysis::MultipletBase& multiplets_1, const analysis::MultipletBase& multiplets_2) const;

    float Rho(const MultipletBase& jet_1, const MultipletBase& jet_2) const;

    float PullDifference(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

    float PullSum(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

    float Dipolarity(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

    int Charge(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

    float BottomBdt(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

private:

    float Pull(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

    float Distance(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2, const Vector2& point_0) const;

};

}
