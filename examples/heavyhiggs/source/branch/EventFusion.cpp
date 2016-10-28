#include "heavyhiggs/branch/EventFusion.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

EventFusion::EventFusion()
{
    HiggsMass = InitialValue();
}

Observables EventFusion::Variables()
{
    return Event::Variables() + OBSERVABLE(HiggsMass);
}

}

}

