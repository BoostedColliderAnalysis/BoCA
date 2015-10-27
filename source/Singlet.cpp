/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Singlet.hh"

#include "DetectorGeometry.hh"
#include "Vector.hh"
#include "Math.hh"
#include "Debug.hh"

namespace boca {

Singlet::Singlet(fastjet::PseudoJet const& jet)
{
    Info();
    jet_ = jet;
}

bool Singlet::Overlap(fastjet::PseudoJet const& jet) const
{
    return Close(jet)(Jet());
}

bool Singlet::Overlap(Singlet const& singlet) const
{
    return Overlap(singlet.Jet());
}

float Singlet::Radius(fastjet::PseudoJet const& jet) const
{
    Info();
    if (!jet.has_constituents()) return 0;
    float delta_r = 0;
    for (auto const& constituent : jet.constituents()) {
        float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        Debug(constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float Singlet::Spread(fastjet::PseudoJet const& jet) const
{
    Info();
    if (!jet.has_constituents()) return 0;
//     float delta_r = Radius(jet);
    float delta_r = 0;
    float spread = 0;
    for (auto const& constituent : jet.constituents()) {
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

JetInfo const& Singlet::UserInfo() const
{
    if (!Jet().has_user_info<JetInfo>()) return jet_info_;
    return Jet().user_info<JetInfo>();
}

float Singlet::log(Length length) const
{
    if (length > 0. * mm) return std::log10(length / mm);
    else return std::log10(DetectorGeometry::TrackerDistanceMin() / 10. / mm);
}

int Singlet::Charge() const
{
//       return UserInfo().Charge();
    return sgn(UserInfo().Charge());
}

Vector2 Singlet::Pull() const
{
    if (has_pull_) return pull_;
    if(!jet_.has_constituents()) return pull_;
    boca::Jets constituents = jet_.constituents();
    if(constituents.size() < 3) return pull_;
    for (auto const& constituent : constituents) pull_ += Reference(constituent) * constituent.pt() * constituent.delta_R(jet_);
    pull_ /= jet_.pt();
    Info(pull_.Y(),pull_.X(), constituents.size());
    has_pull_ = true;
    return pull_;
}

float Singlet::Rapidity() const
{
    if (Jet().rap() == fastjet::pseudojet_invalid_rap) return 0;
    if (Jet().rap() > 100) return 0;
    return Jet().rap();
}

const Singlet &Singlet::singlet() const
{
    return *this;
}

}
