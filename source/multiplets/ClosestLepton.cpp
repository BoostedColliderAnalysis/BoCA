#include "boca/multiplets/ClosestLepton.hh"
#include "boca/generic/Vector.hh"
#include "boca/Event.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

ClosestLepton::ClosestLepton() {}

ClosestLepton::ClosestLepton(const Jet& jet)
{
    INFO0;
    SetJet(jet);
}

ClosestLepton::ClosestLepton(const Jet& jet, const std::vector<Lepton>& leptons)
{
    INFO0;
    SetJet(jet);
    AddLeptons(leptons);
}

ClosestLepton::ClosestLepton(const Jet& jet, Event const& event)
{
    INFO0;
    SetJet(jet);
    AddLeptons(event.Leptons());
}

void ClosestLepton::SetJet(const Jet& jet)
{
    INFO0;
    jet_ = jet;
    lepton_ = jet_ / 100;
}

void ClosestLepton::AddLeptons(const std::vector<Lepton>& leptons)
{
    INFO(leptons.size());
    for (auto const & lepton : leptons) AddLepton(lepton);
}

void ClosestLepton::AddLepton(const Lepton& lepton)
{
    INFO0;
    if (Close<Lepton>(lepton)(jet_) && lepton.Pt() > Pt()) lepton_ = lepton;
}

Angle ClosestLepton::DeltaR()
{
    INFO0;
    return jet_.DeltaRTo(lepton_);
}

Momentum ClosestLepton::Pt()
{
    INFO0;
    return lepton_.Pt();
}

}
