#include "boca/OBSERVABLE_MACROS.hh"

#include "simple/Branch.hh"

namespace simple
{

// initiatialize all observables with an unphysical value
// note that only integer variables must be initiatialized as integer
Branch::Branch()
{
    jet_number = static_cast<int>(InitialValue());
    bottom_number = static_cast<int>(InitialValue());
    missing_et = InitialValue();
    scalar_ht = InitialValue();
    jet_1_pt = InitialValue();
    jet_2_pt = InitialValue();
    jet_3_pt = InitialValue();
    jet_4_pt = InitialValue();
}

boca::Observables Branch::Variables()
{
    //  return a list of observables by passing all class members with their description to the OBSERVABLE macro
    return boca::branch::Bdt::Variables() + OBSERVABLE(bottom_number, "#b") + OBSERVABLE(jet_number, "#j") + OBSERVABLE(missing_et, "E_{T}^{miss}") + OBSERVABLE(scalar_ht, "H_{T}^{scalar}") + OBSERVABLE(jet_1_pt, "p_{T}(j_{1})") + OBSERVABLE(jet_2_pt, "p_{T}(j_{2})") + OBSERVABLE(jet_3_pt, "p_{T}(j_{3})") + OBSERVABLE(jet_4_pt, "p_{T}(j_{4})");
}

void Branch::Fill(Observables const& observables)
{
    // store the BDT value in the BDT member
    boca::branch::Bdt::Fill(observables);
    //  store the other observables in their fields
    jet_number = observables.JetNumber();
    bottom_number = observables.BottomNumber();
    // note that the Branch only takes plain numbers
    missing_et = observables.MissingEt() / GeV;
    scalar_ht = observables.ScalarHt() / GeV;
    jet_1_pt = observables.JetPt(0) / GeV;
    jet_2_pt = observables.JetPt(1) / GeV;
    jet_3_pt = observables.JetPt(2) / GeV;
    jet_4_pt = observables.JetPt(3) / GeV;
}

}
