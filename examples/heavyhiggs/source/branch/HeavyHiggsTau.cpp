#include "heavyhiggs/branch/HeavyHiggsTau.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace heavyhiggs
{

namespace branch
{

HeavyHiggsTau::HeavyHiggsTau()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables HeavyHiggsTau::Variables()
{
    return Particle::Variables() + OBSERVABLE(LeptonPt) + OBSERVABLE(NeutrinoPt);
}

}

}

