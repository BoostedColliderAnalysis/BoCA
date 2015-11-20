#pragma once

#include "Singlet.hh"
#include "Multiplet.hh"
#include "Vector.hh"

namespace analysis
{

template <typename Multiplet_1, typename Multiplet_2>
class TwoBody : public Multiplet
{

public:

    TwoBody() {};

    TwoBody(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2) {
        SetMultiplets(multiplet_1, multiplet_2);
    }

    TwoBody(const fastjet::PseudoJet& jet) {
        SetJet(jet);
    }

    void SetMultiplets(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        if (multiplet_1.Bdt() != initial_value() && multiplet_2.Bdt() != initial_value()) SetBdt(multiplet_1.Bdt(), multiplet_2.Bdt());
        else if (multiplet_1.Bdt() != initial_value()) SetBdt(multiplet_1.Bdt());
        else if (multiplet_2.Bdt() != initial_value()) SetBdt(multiplet_2.Bdt());
    }

    void SetJet(const fastjet::PseudoJet& jet) {
        static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetSubStructure(false);
        multiplet_1_ = Multiplet_1(jet / 2);
        multiplet_2_ = Multiplet_2(jet / 2);
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt()) / 2);
    }
  
    Multiplet_1& Multiplet1() {
        return multiplet_1_;
    }

    const Multiplet_1& Multiplet1() const {
        return multiplet_1_;
    }

    Multiplet_2& Multiplet2() {
        return multiplet_2_;
    }

    const Multiplet_2& Multiplet2() const {
        return multiplet_2_;
    }

    template <typename Multiplet3>
    bool Overlap(const Multiplet3& multiplet) const {
        return (multiplet.Overlap(multiplet_1_) || multiplet.Overlap(multiplet_2_));
    }

    bool Overlap(const analysis::Singlet& singlet) const {
        return (multiplet_1_.Overlap(singlet) || multiplet_2_.Overlap(singlet));
    }

    bool Overlap(const fastjet::PseudoJet& jet) const {
        return (multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet));
    }

    bool Overlap() const {
        return multiplet_1_.Overlap(multiplet_2_);
    }

    /**
     * @brief join the pieces of the multiplets to one jet
     *
     * @return fastjet::PseudoJet
     */
    fastjet::PseudoJet Jet() const {
        if (!has_jet_) SetResult(Multiplet::Jet(Multiplet1().Jet(), Multiplet2().Jet()));
        return jet_;
    }

    analysis::Jets Jets() const {
        return Join(Multiplet1().Jets(), Multiplet2().Jets());
    }

    float DeltaPt() const {
        return Multiplet1().Jet().pt() - Multiplet2().Jet().pt();
    }

    float Ht() const {
        return Multiplet::Ht(Multiplet1(), Multiplet2());
    }

    float DeltaRap() const {
        return Multiplet::DeltaRap(Multiplet1(), Multiplet2());
    }

    float DeltaPhi() const {
        return Multiplet::DeltaPhi(Multiplet1(), Multiplet2());
    }

    float DeltaR() const {
        return Multiplet::DeltaR(Multiplet1(), Multiplet2());
    }

    float DeltaM() const {
        return Multiplet::DeltaM(Multiplet1(), Multiplet2());
    }

    float DeltaHt() const {
        return Multiplet::DeltaHt(Multiplet1(), Multiplet2());
    }

    float Rho() const {
        return Multiplet::Rho(Multiplet1(), Multiplet2());
    }

    float MassDifferenceTo(Id id) const {
        return std::abs(Jet().m() - Mass(id));
    }

    int Charge() const {
        return Multiplet::Charge(Multiplet1(), Multiplet2());
    }

    const analysis::Singlet& singlet() const {
        if (!has_jet_)SetSinglet(Jet());
        return singlet_;
    }

    float PullDifference() const {
        return Multiplet::PullDifference(Multiplet1(), Multiplet2());
    }

    float PullSum() const {
        return Multiplet::PullSum(Multiplet1(), Multiplet2());
    }
    
    float Dipolarity() const {
        return Multiplet::Dipolarity(Multiplet1(), Multiplet2());
    }

    float BottomBdt() const final {
        return Multiplet::BottomBdt(Multiplet1(), Multiplet2());
    };
    
    analysis::Jets RestJets() const {
      return RestJetsM;
    }
    
    inline void AddRestJet(const fastjet::PseudoJet &NewJet)
    {
      RestJetsM.push_back(NewJet);
      std::sort(RestJetsM.begin(), RestJetsM.end(), SortByBdt());
    }
    
    float BdtRatio1(const int Number) const {
      if (unsigned(Number) > RestJetsM.size()) return 0;
      return (multiplet_1_.Bdt()+1) / (RestJetsM.at(Number - 1).template user_info<JetInfo>().Bdt()+1);
    }
    
    float BdtRatio2(const int Number)const {
      if (unsigned(Number) > RestJetsM.size()) return 0;
      return (multiplet_2_.Bdt()+1) / (RestJetsM.at(Number - 1).template user_info<JetInfo>().Bdt()+1);
    }
    
protected:

    void SetMultiplet1(const Multiplet_1 multiplet_1) {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(const Multiplet_2 multiplet_2) {
        multiplet_2_ = multiplet_2;
    }

private:

    Multiplet_1 multiplet_1_;

    Multiplet_2 multiplet_2_;
    
    analysis::Jets RestJetsM;

};

}
