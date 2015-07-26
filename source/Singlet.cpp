#include "Singlet.hh"
#include "DetectorGeometry.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

Singlet::Singlet(const fastjet::PseudoJet& jet)
{
    Info();
    jet_ = jet;
}

bool Singlet::Overlap(const fastjet::PseudoJet& jet) const
{
    return (Close(jet)(Jet()));
}

bool Singlet::Overlap(const Singlet& singlet) const
{
    return Overlap(singlet.Jet());
}

float Singlet::Radius(const fastjet::PseudoJet& jet) const
{
    Info();
    if (!jet.has_constituents()) return 0;
    float delta_r = 0;
    for (const auto& constituent : jet.constituents()) {
        float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        Debug(constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float Singlet::Spread(const fastjet::PseudoJet& jet) const
{
    Info();
    if (!jet.has_constituents())
        return 0;
//     float delta_r = Radius(jet);
    float delta_r = 0;
    float spread = 0;
    for (const auto& constituent : jet.constituents()) {
        float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        spread += constituent_delta_r * constituent.pt();
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    if (delta_r == 0) return 0;
    return spread / jet.pt() / delta_r;
}

void Singlet::SetBdt(float bdt)
{
    if (jet_.has_user_info<JetInfo>()) static_cast<JetInfo&>(*jet_.user_info_shared_ptr().get()).SetBdt(bdt);
}

const JetInfo& Singlet::UserInfo() const
{
    if (!Jet().has_user_info<JetInfo>()) return jet_info_;
    return Jet().user_info<JetInfo>();
}

float Singlet::log(float number) const
{
    if (number > 0) return std::log10(number);
    else return std::log10(DetectorGeometry::TrackerDistanceMin() / 10);
}

int Singlet::Charge() const
{
//       return UserInfo().Charge();
    return sgn(UserInfo().Charge());
}

Vector2 Singlet::Pull() const
{
    if(!jet_.has_constituents()) return Vector2();
    Vector2 vector;
    for (const auto & constituent : jet_.constituents()) vector += Reference(constituent) * constituent.pt() / jet_.pt() * constituent.delta_R(jet_);
    return vector;
}

/**
 * @brief calculate Reference vector for other - this
 * @return Vector2 reference vector
 *
 */
Vector2 Singlet::Reference(const fastjet::PseudoJet& vector) const
{
  return Vector2(vector.rap() - jet_.rap(), jet_.delta_phi_to(vector));
}

/**
 * @brief calculate Reference vector for other - this
 * @return Vector2 reference vector
 *
 */
// Vector2 Singlet::Reference(const Singlet& vector) const
// {
//     return Reference(vector.Jet());
// }

float Singlet::Rapidity() const
{
    if (Jet().rap() == fastjet::pseudojet_invalid_rap) return 0;
    if (Jet().rap() > 100) return 0;
    return Jet().rap();
}

Singlet Singlet::singlet() const
{
    return *this;
}

Singlet Singlet::singlet(Structure) const
{
  return *this;
}

}
