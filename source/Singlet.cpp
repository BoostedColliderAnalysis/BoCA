# include "Singlet.hh"

namespace analysis {

Singlet::Singlet(const fastjet::PseudoJet &jet)
{
    Print(kInformation, "Constructor");
    jet_ = jet;
}

bool Singlet::Overlap(const fastjet::PseudoJet &jet) const
{
    return (Jet().delta_R(jet) < DetectorGeometry().JetConeSize);
}

bool Singlet::Overlap(const Singlet &singlet) const
{
    return Overlap(singlet.Jet());
}

float Singlet::Radius(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "Delta R");
    if (!jet.has_constituents()) return 0;
    float delta_r = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        Print(kDebug, "Delta R", constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float Singlet::Spread(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "spread");
    if (!jet.has_constituents()) return 0;
    float delta_r = Radius(jet);
    if (delta_r == 0) return 0;
    float spread = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        spread += constituent_delta_r * constituent.pt();
    }
    return spread / jet.pt() / delta_r;
}

void Singlet::SetBdt(const float bdt)
{
    if (jet_.has_user_info<JetInfo>()) static_cast<JetInfo &>(*jet_.user_info_shared_ptr().get()).SetBdt(bdt);
}

const JetInfo &Singlet::UserInfo() const
{
    if (!Jet().has_user_info<JetInfo>()) return jet_info_;
    return Jet().user_info<JetInfo>();
}

float Singlet::log(const float number) const
{
    if (number > 0) return std::log10(number);
    else return std::log10(DetectorGeometry().TrackerDistanceMin / 10);
}

}
