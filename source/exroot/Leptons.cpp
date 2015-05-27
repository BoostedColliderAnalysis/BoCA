# include "exroot/Leptons.hh"
# include "Predicate.hh"

analysis::Jets analysis::exroot::Leptons::Electrons()
{
    Print(kInformation, "Electrons");
    analysis::Jets electrons;
    for (const int ElectronNumber : Range(clones_arrays().ElectronSum())) {
        ::exroot::Electron electron = static_cast<::exroot::Electron &>(clones_arrays().Electron(ElectronNumber));
        fastjet::PseudoJet electron_jet = PseudoJet(electron);
        electron_jet.set_user_info(new JetInfo(int(electron.Charge)));
        electrons.emplace_back(electron_jet);
    }
    return electrons;
}

analysis::Jets analysis::exroot::Leptons::Muons()
{
  Print(kInformation, "Muons");
  analysis::Jets muons;
    for (const int MuonNumber : Range(clones_arrays().MuonSum())) {
        ::exroot::Muon &muon = static_cast<::exroot::Muon &>(clones_arrays().Muon(MuonNumber));
        fastjet::PseudoJet muon_jet = PseudoJet(muon);
        muon_jet.set_user_info(new JetInfo(int(muon.Charge)));
        muons.emplace_back(muon_jet);
    }
    return muons;
}
