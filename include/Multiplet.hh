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
        if (multiplet_1.Bdt() != initial_value() && multiplet_2.Bdt() != initial_value()) SetBdt(multiplet_1.Bdt(), multiplet_2.Bdt());
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

    /**
     * @brief join the pieces of the multiplets to one jet
     *
     * @return fastjet::PseudoJet
     */
    fastjet::PseudoJet Jet(Structure structure) const {
        if (structure == Structure::vertices) structure |= Structure::plain;
        fastjet::PseudoJet jet;
        fastjet::PseudoJet jet_1 = Multiplet1().Jet(structure);
        fastjet::PseudoJet jet_2 = Multiplet2().Jet(structure);
        if (is(structure, Structure::plain)) jet = fastjet::join(jet_1, jet_2);
        if (is(structure, Structure::constituents)) {
            analysis::Jets constituents;
            if (jet_1.has_constituents()) constituents = Join(constituents, jet_1.constituents());
            if (jet_2.has_constituents()) constituents = Join(constituents, jet_2.constituents());
            jet = fastjet::join(constituents);
        }
        if (is(structure, Structure::vertices)) {
            std::vector<Constituent> constituents;
            std::vector<Constituent> displaced_constituents;
            if (jet_1.has_user_info<JetInfo>()) {
                constituents = Join(constituents, jet_1.user_info<JetInfo>().constituents());
                displaced_constituents = Join(displaced_constituents, jet_1.user_info<JetInfo>().displaced_constituents());
            }
            if (jet_2.has_user_info<JetInfo>()) {
                constituents = Join(constituents, jet_2.user_info<JetInfo>().constituents());
                displaced_constituents = Join(displaced_constituents, jet_2.user_info<JetInfo>().displaced_constituents());
            }
            jet.set_user_info(new JetInfo(constituents, displaced_constituents));
        }
        return jet;
    }

    analysis::Jets Jets() const{
      return Join(Multiplet1().Jets(),Multiplet2().Jets());
    }

    fastjet::PseudoJet Jet() const {
        return Jet(Structure::plain);
    }

    float DeltaPt() const {
        return Multiplet1().Jet().pt() - Multiplet2().Jet().pt();
    }

    float Ht() const {
        return Multiplet1().Ht() + Multiplet2().Ht();
    }

    float DeltaRap() const {
        float delta_rap = Multiplet1().Jet().rap() - Multiplet2().Jet().rap();
        if (std::abs(delta_rap) > 100) return 0;
        return delta_rap;
    }

    float DeltaPhi() const {
        return Multiplet1().Jet().delta_phi_to(Multiplet2().Jet());
    }

    float DeltaR() const {
        float delta_r = Multiplet1().Jet().delta_R(Multiplet2().Jet());
        if (std::abs(delta_r) > 100) delta_r = 0;
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

    float MassDifferenceTo(Id id) const {
        return std::abs(Jet().m() - Mass(id));
    }

    int Charge() const {
        return sgn(Multiplet1().Charge() + Multiplet2().Charge());
    }

    analysis::Singlet singlet(Structure structure) const {
        return Singlet(Jet(structure));
    }

    analysis::Singlet singlet() const {
      return Singlet(Jet(Structure::vertices));
    }

    float Pull1() const {
        Vector2 pull = Multiplet1().singlet(Structure::constituents).Pull() - Multiplet1().Reference(Multiplet2().Jet());
        return std::atan2(pull.Y(), pull.X());
    }

    float Pull2() const {
        Vector2 pull = Multiplet2().singlet(Structure::constituents).Pull() - Multiplet2().Reference(Multiplet1().Jet());
        return std::atan2(pull.Y(), pull.X());
    }

    float PullDifference() const {
        return RestrictPhi(analysis::DeltaPhi(Pull1(), Pull2()) - M_PI);
    }

    float PullSum() const {
        return RestrictPhi(Pull1() + Pull2());
    }

    float Dipolarity() const {
        if (DeltaR() == 0) return 0;
        fastjet::PseudoJet jet = Jet(Structure::constituents);
        if (jet.pt() == 0) return 0;
        float dipolarity = 0;
        if (!jet.has_constituents()) return 0;
        for (const auto & constituent : jet.constituents()) {
            if (constituent.pt() > jet.pt()) continue;

            float phi = constituent.phi_std();
            float distance_1 = Distance(Vector2(constituent.rap(), phi));

            if (phi < 0) phi += 2 * M_PI;
            else  phi -= 2 * M_PI;
            float distance_2 =  Distance(Vector2(constituent.rap(), phi));

            float distance = std::min(distance_1, distance_2);
            if (distance > DeltaR()) continue;
            dipolarity += constituent.pt() * sqr(distance);
        }
        return dipolarity / jet.pt() / sqr(DeltaR());
    }

    /**
     * @brief calculate Reference vector for other - this
     * @return Vector2 reference vector
     *
     */
    Vector2 Reference(const fastjet::PseudoJet& vector) const {
        return Vector2(vector.rap() - Jet().rap(), Jet().delta_phi_to(vector));
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

    float Distance(const Vector2& point_0) const {
        Vector2 point_1(Multiplet1().Jet().rap(), Multiplet1().Jet().phi_std());
        Vector2 point_2(Multiplet2().Jet().rap(), Multiplet2().Jet().phi_std());
        return std::abs(point_2.Y() - point_1.Y() * point_0.X() - (point_2.X() - point_1.X()) * point_0.Y() + point_2.X() * point_1.Y() - point_2.Y() * point_1.X()) / DeltaR();
    }

};

}
