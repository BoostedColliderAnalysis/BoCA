#pragma once

#include "MultipletBase.hh"
#include "Singlet.hh"

namespace analysis
{

class Multiplet : public MultipletBase
{

public:

  float LeptonPt = 0;

  float LeptonDeltaR = 0;
  
  float Pull(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;
  
protected:

    virtual float Ht() const override = 0;

    virtual int Charge() const override = 0;

    virtual float BottomBdt() const override = 0;

    virtual std::vector<fastjet::PseudoJet> Jets() const = 0;

    virtual fastjet::PseudoJet Jet() const override = 0;

    fastjet::PseudoJet Jet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2) const;

    Vector2 Pull() const override;

    float DeltaPt(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const;

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

    void SetResult(const fastjet::PseudoJet& jet) const {
      jet_ = jet;
      SetSinglet(jet);
      has_jet_ = true;
    }

    void SetSinglet(const fastjet::PseudoJet& jet) const {
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

  float Distance(const Vector2& point_1, const Vector2& point_2, const Vector2& point_0, float delta_r) const;

};

}
