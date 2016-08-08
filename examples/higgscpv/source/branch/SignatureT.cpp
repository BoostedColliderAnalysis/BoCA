#include "include/branch/SignatureT.hh"
#include "boca/OBSERVABLE.hh"

namespace higgscpv
{

namespace branch
{

SignatureT::SignatureT()
{
    Sphericity = InitialValue();
    Aplanarity = InitialValue();
}

Observables SignatureT::Variables()
{
    return OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity) + ThreeBody::Variables();
}

}

}

