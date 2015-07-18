#include "exroot/Leptons.hh"
#include "JetInfo.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

namespace exroot {

Jets Leptons::Electrons() const
{
    Info();
    Jets electrons;
    for (const int electron_number : Range(clones_arrays().ElectronSum())) {
        ::exroot::Electron electron = static_cast<::exroot::Electron&>(clones_arrays().Electron(electron_number));
        fastjet::PseudoJet electron_jet = PseudoJet(electron);
        electron_jet.set_user_info(new JetInfo(int(electron.Charge)));
        electrons.emplace_back(electron_jet);
    }
    return electrons;
}

Jets Leptons::Muons() const
{
    Info();
    Jets muons;
    for (const int muon_number : Range(clones_arrays().MuonSum())) {
        ::exroot::Muon& muon = static_cast<::exroot::Muon&>(clones_arrays().Muon(muon_number));
        fastjet::PseudoJet muon_jet = PseudoJet(muon);
        muon_jet.set_user_info(new JetInfo(int(muon.Charge)));
        muons.emplace_back(muon_jet);
    }
    return muons;
}

}

}
