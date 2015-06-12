# include "exroot/Leptons.hh"
# include "Predicate.hh"

namespace analysis
{

namespace exroot
{

Jets Leptons::Electrons()
{
    Print(kInformation, "Electrons");
    Jets electrons;
    for (const int ElectronNumber : Range(clones_arrays().ElectronSum())) {
        ::exroot::Electron electron = static_cast<::exroot::Electron &>(clones_arrays().Electron(ElectronNumber));
        fastjet::PseudoJet electron_jet = PseudoJet(electron);
        electron_jet.set_user_info(new JetInfo(int(electron.Charge)));
        electrons.emplace_back(electron_jet);
    }
    return electrons;
}

Jets Leptons::Muons()
{
    Print(kInformation, "Muons");
    Jets muons;
    for (const int MuonNumber : Range(clones_arrays().MuonSum())) {
        ::exroot::Muon &muon = static_cast<::exroot::Muon &>(clones_arrays().Muon(MuonNumber));
        fastjet::PseudoJet muon_jet = PseudoJet(muon);
        muon_jet.set_user_info(new JetInfo(int(muon.Charge)));
        muons.emplace_back(muon_jet);
    }
    return muons;
}

}

}
