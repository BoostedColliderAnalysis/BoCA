#include "multiplets/ClosestLepton.hh"
#include "Vector.hh"
#include "Event.hh"

namespace boca
{

ClosestLepton::ClosestLepton() {}

ClosestLepton::ClosestLepton(const Jet& jet)
{
    SetJet(jet);
}

ClosestLepton::ClosestLepton(const Jet& jet, const std::vector<Lepton>& leptons)
{
    SetJet(jet);
    AddLeptons(leptons);
}

ClosestLepton::ClosestLepton(const Jet& jet, const Event& event)
{
  SetJet(jet);
  AddLeptons(event.Leptons().leptons());
}

void ClosestLepton::SetJet(const Jet& jet)
{
    jet_ = jet;
}

void ClosestLepton::AddLeptons(const std::vector<Lepton>& leptons)
{
    for (auto const & lepton : leptons) AddLepton(lepton);
}

void ClosestLepton::AddLepton(const Lepton& lepton)
{
    if (Close<Lepton>(lepton)(jet_) && lepton.Pt() > Pt()) lepton_ = lepton;
}

Angle ClosestLepton::DeltaR()
{
    return jet_.DeltaRTo(lepton_);
}

Momentum ClosestLepton::Pt()
{
    return lepton_.Pt();
}

}
