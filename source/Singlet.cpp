# include "Singlet.hh"

analysis::Singlet::Singlet(const fastjet::PseudoJet &singlet)
{
    Print(kInformation, "Constructor");
    singlet_ = singlet;
}

float analysis::Singlet::GetDeltaR(const fastjet::PseudoJet &jet) const
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

float analysis::Singlet::GetSpread(const fastjet::PseudoJet &jet) const
{
  Print(kInformation, "spread");
  if (!jet.has_constituents()) return 0;
  float delta_r = GetDeltaR(jet);
  if (delta_r == 0) return 0;
  float spread = 0;
  for (const auto & constituent : jet.constituents()) {
    const float constituent_delta_r = jet.delta_R(constituent);
    if (constituent_delta_r > 100) continue;
    spread += constituent_delta_r * constituent.pt();
  }
  return spread / jet.pt() / delta_r;
}
