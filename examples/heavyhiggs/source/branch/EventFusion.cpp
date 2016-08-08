#include "include/branch/EventFusion.hh"
#include "boca/OBSERVABLE.hh"

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

