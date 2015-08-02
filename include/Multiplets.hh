#pragma once

#include "Object.hh"

namespace analysis
{

class Multiplets : public Object
{

public:

  Vector2 Pull() const override;

    fastjet::PseudoJet Jet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, Structure structure) const;

    virtual fastjet::PseudoJet Jet(Structure) const override = 0;

    virtual fastjet::PseudoJet Jet() const override = 0;

    virtual float Ht() const override = 0;

    float DeltaPt(const Multiplets& multiplets_1, const Multiplets& multiplets_2) const;

    float Ht(const analysis::Object& multiplets_1, const analysis::Object& multiplets_2) const;

    float DeltaRap(const analysis::Object& multiplets_1, const analysis::Object& multiplets_2) const;

    float DeltaPhi(const Object& multiplets_1, const Object& multiplets_2) const;

    float DeltaR(const Object& multiplets_1, const Object& multiplets_2) const;

    float DeltaM(const Object& multiplets_1, const Object& multiplets_2) const;

    float DeltaHt(const analysis::Object& multiplets_1, const analysis::Object& multiplets_2) const;

    float Rho(const Object& jet_1, const Object& jet_2) const;

    float Pull(const Object& multiplets_1, const Object& multiplets_2) const;

    float PullDifference(const Object& multiplets_1, const Object& multiplets_2) const;

    float PullSum(const Object& multiplets_1, const Object& multiplets_2) const;

    float Dipolarity(const Object& multiplets_1, const Object& multiplets_2) const;

    /**
     * @brief calculate Reference vector for other - this
     * @return Vector2 reference vector
     *
     */
    Vector2 Reference(const fastjet::PseudoJet& vector) const override;

protected:

    float Distance(const Object& multiplets_1, const Object& multiplets_2, const Vector2& point_0) const;

private:

};

}
