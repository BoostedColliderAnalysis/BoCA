#include "boca/Event.hh"
#include "boca/Isolation.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

Isolation::Isolation(Event& event, boca::TreeReader const& tree_reader) :
    Leptons(tree_reader),
    event_(event)
{
    INFO0;
}

std::vector<Lepton> Isolation::leptons() const
{
    INFO0;
    return event_.IsolatedLeptons();
}

std::vector<Lepton> Isolation::Electrons() const
{
    INFO0;
    return event_.leptons_->Electrons();
}

std::vector<Lepton> Isolation::Muons() const
{
    INFO0;
    return event_.leptons_->Muons();
}

std::vector<Lepton> Isolation::Photons() const
{
    INFO0;
    return event_.leptons_->Photons();
}

}
