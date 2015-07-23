#pragma once

#include "Singlet.hh"
#include "DetectorGeometry.hh"
#include "Predicate.hh"

namespace analysis
{

template <typename Multiplet_1, typename Multiplet_2>
class Multiplet : public Identification
{

public:

    Multiplet() {};

    Multiplet(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2) {
        SetMultiplets(multiplet_1, multiplet_2);
    }

    Multiplet(const fastjet::PseudoJet& jet) {
        SetJet(jet);
    }

    void SetMultiplets(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        if (multiplet_1.Bdt() != initial_value() && multiplet_2.Bdt() != initial_value()) SetBdt((multiplet_1.Bdt() + multiplet_2.Bdt()) / 2);
        else if (multiplet_1.Bdt() != initial_value()) SetBdt(multiplet_1.Bdt());
        else if (multiplet_2.Bdt() != initial_value()) SetBdt(multiplet_2.Bdt());
    }

    void SetJet(const fastjet::PseudoJet& jet) {
        multiplet_1_ = Multiplet_1(jet / 2);
        multiplet_2_ = Multiplet_2(jet / 2);
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt()) / 2);
    }

    Multiplet_1& Multiplet1() const {
        return multiplet_1_;
    }

    Multiplet_2& Multiplet2() const {
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

    bool Coincides(const fastjet::PseudoJet& jet) const {
        return Close(jet)(Jet());
    }

    // TODO clean this mess up; and figure out why the cases are necessary
    fastjet::PseudoJet EffectiveJet() const {
        fastjet::PseudoJet jet = Jet();
        fastjet::PseudoJet jet_1 = Multiplet1().EffectiveJet();
        fastjet::PseudoJet jet_2 = Multiplet2().EffectiveJet();
        if (jet_1.has_user_info<JetInfo>() && jet_2.has_user_info<JetInfo>())
            jet.set_user_info(new JetInfo(Join(jet_1.user_info<JetInfo>().constituents(), jet_2.user_info<JetInfo>().constituents()), Join(jet_1.user_info<JetInfo>().displaced_constituents(), jet_2.user_info<JetInfo>().displaced_constituents())));
        else if (jet_1.has_user_info<JetInfo>())
            jet.set_user_info(new JetInfo(jet_1.user_info<JetInfo>().constituents(), jet_1.user_info<JetInfo>().displaced_constituents()));
        else if (jet_2.has_user_info<JetInfo>())
            jet.set_user_info(new JetInfo(jet_2.user_info<JetInfo>().constituents(), jet_2.user_info<JetInfo>().displaced_constituents()));
//         if(jet_1.has_constituents() && jet_2.has_constituents()) jet = fastjet::join(Join(jet_1.constituents(), jet_2.constituents()));
//         else if(jet_1.has_constituents()) jet = fastjet::join(jet_1.constituents());
//         else if(jet_2.has_constituents()) jet = fastjet::join(jet_2.constituents());
//         if (jet_1.has_user_info<JetInfo>() && jet_2.has_user_info<JetInfo>())
//         jet.set_user_info(new JetInfo(Join(jet_1.user_info<JetInfo>().constituents(), jet_2.user_info<JetInfo>().constituents())));
//         else if (jet_1.has_user_info<JetInfo>()) jet.set_user_info(new JetInfo(jet_1.user_info<JetInfo>().constituents()));
//         else if (jet_2.has_user_info<JetInfo>()) jet.set_user_info(new JetInfo(jet_2.user_info<JetInfo>().constituents()));
//         else jet.set_user_info(new JetInfo);
        return jet;
    }

    fastjet::PseudoJet Jet() const {
        return fastjet::join(Multiplet1().Jet(), Multiplet2().Jet());
    }

    float DeltaPt() const {
        return Multiplet1().Jet().pt() - Multiplet2().Jet().pt();
    }

    float Ht() const {
        return Multiplet1().Ht() + Multiplet2().Ht();
    }

    float DeltaRap() const {
        float delta_rap = Multiplet1().Jet().rap() - Multiplet2().Jet().rap();
        if (std::abs(delta_rap) > 100)
            return 0;
        return delta_rap;
    }

    float DeltaPhi() const {
        return Multiplet1().Jet().delta_phi_to(Multiplet2().Jet());
    }

    float DeltaR() const {
        float delta_r = Multiplet1().Jet().delta_R(Multiplet2().Jet());
        if (std::abs(delta_r) > 100)
            delta_r = 0;
//         if (delta_r < DetectorGeometry::MinCellResolution()) delta_r = Singlet(Jet()).DeltaR();
        return delta_r;
    }

    float DeltaM() const {
        return Multiplet1().Jet().m() - Multiplet2().Jet().m();
    }

    float DeltaHt() const {
        return Multiplet1().Ht() - Multiplet2().Ht();
    }

    float Rho() const {
        if (Jet().pt() < DetectorGeometry::MinCellPt() || DeltaR() < DetectorGeometry::MinCellResolution())
            return 0;
        return Jet().m() / Jet().pt() / DeltaR() * 2;
    }

    float MassDifferenceTo(const Id id) const {
        return std::abs(Jet().m() - Mass(id));
    }

    int Charge() const {
        return sgn(Multiplet1().Charge() + Multiplet2().Charge());
    }

    analysis::Singlet singlet() const {
        return Singlet(EffectiveJet());
    }

protected:

    void SetMultiplet1(const Multiplet_1 multiplet_1) {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(const Multiplet_2 multiplet_2) {
        multiplet_2_ = multiplet_2;
    }

private:

    mutable Multiplet_1 multiplet_1_;

    mutable Multiplet_2 multiplet_2_;

};

}
