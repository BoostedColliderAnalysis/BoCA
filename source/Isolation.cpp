#include "Event.hh"
#include "Isolation.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

Isolation::Isolation(Event& event, boca::TreeReader const& tree_reader) :
    event_(event),
    Leptons(tree_reader)
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
