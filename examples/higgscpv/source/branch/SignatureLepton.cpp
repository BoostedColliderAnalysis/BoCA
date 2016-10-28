#include "higgscpv/branch/SignatureLepton.hh"
#include "boca/Settings.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace higgscpv
{

namespace branch
{

SignatureLepton::SignatureLepton()
{
    Mass12 = InitialValue();
    Mass23 = InitialValue();
    Mass13 = InitialValue();
    DeltaPt23 = InitialValue();
    DeltaPt13 = InitialValue();
    Pt12 = InitialValue();
    Pt23 = InitialValue();
    Pt13 = InitialValue();
    Ht12 = InitialValue();
    Ht23 = InitialValue();
    Ht13 = InitialValue();
    Rho23 = InitialValue();
    Rho13 = InitialValue();
    DeltaRap23 = InitialValue();
    DeltaRap13 = InitialValue();
    DeltaPhi23 = InitialValue();
    DeltaPhi13 = InitialValue();
    DeltaR23 = InitialValue();
    DeltaR13 = InitialValue();
    DeltaM23 = InitialValue();
    DeltaM13 = InitialValue();
    DeltaHt23 = InitialValue();
    DeltaHt13 = InitialValue();
    Pull23 = InitialValue();
    Pull13 = InitialValue();
    DeltaPull23 = InitialValue();
    DeltaPull13 = InitialValue();
//     Dipolarity23 = InitialValue();
//     Dipolarity13 = InitialValue();
    Sphericity = InitialValue();
    Aplanarity = InitialValue();
}

Observables SignatureLepton::Variables()
{
    auto substructure = boca::Settings::SubStructure() ? OBSERVABLE(Pull23) + OBSERVABLE(Pull13) + OBSERVABLE(DeltaPull13) /*+ OBSERVABLE(Dipolarity23) + OBSERVABLE(Dipolarity13)*/ : boca::Observables{};
    return boca::branch::Multi::Variables() + OBSERVABLE(Mass12) + OBSERVABLE(Mass23) + OBSERVABLE(Mass13) + OBSERVABLE(Pt12) + OBSERVABLE(Pt23) + OBSERVABLE(Pt13) + OBSERVABLE(DeltaPt23) + OBSERVABLE(DeltaPt13) + OBSERVABLE(Ht12) + OBSERVABLE(Ht23) + OBSERVABLE(Ht13) + OBSERVABLE(Rho23) + OBSERVABLE(Rho13) + OBSERVABLE(DeltaRap23) + OBSERVABLE(DeltaRap13) + OBSERVABLE(DeltaPhi23) + OBSERVABLE(DeltaPhi13) + OBSERVABLE(DeltaR23) + OBSERVABLE(DeltaR13) + OBSERVABLE(DeltaM23) + OBSERVABLE(DeltaM13) + OBSERVABLE(DeltaHt23) + OBSERVABLE(DeltaHt13) + OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity) + substructure;
}

}

}

