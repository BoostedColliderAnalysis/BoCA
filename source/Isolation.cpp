#include "Event.hh"
#include "Isolation.hh"
// #define INFORMATION
#include "Debug.hh"

namespace analysis
{

Isolation::Isolation(Event &event) : event_(event)
{
    Info();
}

Jets Isolation::leptons() const {
    Info();
    return event_.IsolatedLeptons();
}

Jets Isolation::Electrons() const
{
    Info();
    return event_.leptons_->Electrons();
}

Jets Isolation::Muons() const
{
    Info();
    return event_.leptons_->Muons();
}

}
