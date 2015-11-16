#include "exroot/Leptons.hh"

#include "exroot/ExRootAnalysis.hh"
#include "JetInfo.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

namespace exroot {

Jets Leptons::Electrons() const
{
    Info0;
    Jets electrons;
//     for (auto const& electron_number : Range(tree_reader().ElectronSum())) {
    for (auto const& electron : tree_reader().Objects<::exroot::Electron>(Branch::electron)) {
//         ::exroot::Electron electron = static_cast<::exroot::Electron&>(tree_reader().Electron(electron_number));
        fastjet::PseudoJet electron_jet = PseudoJet(electron);
        electron_jet.set_user_info(new JetInfo(int(electron.Charge)));
        electrons.emplace_back(electron_jet);
    }
    return electrons;
}

Jets Leptons::Muons() const
{
    Info0;
    Jets muons;
//     for (auto const& muon_number : Range(tree_reader().MuonSum())) {
    for (auto const& muon : tree_reader().Objects<::exroot::Muon>(Branch::muon)) {
//         ::exroot::Muon& muon = static_cast<::exroot::Muon&>(tree_reader().Muon(muon_number));
        fastjet::PseudoJet muon_jet = PseudoJet(muon);
        muon_jet.set_user_info(new JetInfo(int(muon.Charge)));
        muons.emplace_back(muon_jet);
    }
    return muons;
}

}

}
