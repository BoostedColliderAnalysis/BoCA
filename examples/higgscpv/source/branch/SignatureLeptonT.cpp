#include "higgscpv/branch/SignatureLeptonT.hh"
#include "boca/Settings.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace higgscpv
{

namespace branch
{

Observables SignatureLeptonT::Variables()
{
//     auto substructure = boca::Settings::SubStructure() ? OBSERVABLE(Pull23) + OBSERVABLE(Pull13) + OBSERVABLE(Pull32) + OBSERVABLE(Pull31) /*+ OBSERVABLE(Dipolarity23) + OBSERVABLE(Dipolarity13)*/ : boca::Observables{};
//     return OBSERVABLE(Ht, "H_{T}") + OBSERVABLE(DeltaPt, "\\Delta P_{T}") + OBSERVABLE(DeltaM, "\\Delta m") + OBSERVABLE(DeltaRap, "\\Delta \\eta") + OBSERVABLE(DeltaPhi, "\\Delta \\phi") + OBSERVABLE(DeltaR, "\\Delta R") + OBSERVABLE(Rho, "\\rho") + OBSERVABLE(DeltaHt, "\\Delta H_{T}") + OBSERVABLE(Bdt3) + OBSERVABLE(Mass12) + OBSERVABLE(Mass23) + OBSERVABLE(Mass13) + OBSERVABLE(Pt12) + OBSERVABLE(Pt23) + OBSERVABLE(Pt13) + OBSERVABLE(DeltaPt23) + OBSERVABLE(DeltaPt13) + OBSERVABLE(Ht12) + OBSERVABLE(Ht23) + OBSERVABLE(Ht13) + OBSERVABLE(Rho23) + OBSERVABLE(Rho13) + OBSERVABLE(DeltaRap23) + OBSERVABLE(DeltaRap13) + OBSERVABLE(DeltaPhi23) + OBSERVABLE(DeltaPhi13) + OBSERVABLE(DeltaR23) + OBSERVABLE(DeltaR13) + OBSERVABLE(DeltaM23) + OBSERVABLE(DeltaM13) + OBSERVABLE(DeltaHt23) + OBSERVABLE(DeltaHt13) + substructure + OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity);
  return SignatureT::Variables();
}

}

}

