# include "delphes/Leptons.hh"
# include "Predicate.hh"

analysis::delphes::Leptons::Leptons()
{
    Print(kNotification, "Constructor");
}
analysis::Jets analysis::delphes::Leptons::Electrons()
{
    Print(kInformation, "Electrons", clones_arrays().ElectronSum());
    return Electrons(kPlain);
}

analysis::Jets analysis::delphes::Leptons::Electrons(analysis::FourVector::JetDetail jet_detail)
{
    Print(kInformation, "Electrons", clones_arrays().ElectronSum());
    analysis::Jets electrons;
    for (int ElectronNumber : Range(clones_arrays().ElectronSum())) {
        ::delphes::Electron &electron = static_cast<::delphes::Electron &>(clones_arrays().Electron(ElectronNumber));
        fastjet::PseudoJet electron_jet = analysis::PseudoJet(electron.P4());
        if (jet_detail == analysis::FourVector::kTagging) {
            Constituent constituent(electron.P4(), BranchFamily(*electron.Particle.GetObject()));
            electron_jet.set_user_info(new JetInfo(constituent, int(electron.Charge)));
        } else electron_jet.set_user_info(new JetInfo(int(electron.Charge)));
        electrons.emplace_back(electron_jet);
    }
    PrintTruthLevel(kDebug);
    return electrons;
}

analysis::Jets analysis::delphes::Leptons::Muons()
{
    Print(kInformation, "Muons", clones_arrays().MuonSum());
    return Muons(kPlain);
}

analysis::Jets analysis::delphes::Leptons::Muons(JetDetail jet_detail)
{
    Print(kInformation, "Muons", clones_arrays().MuonSum());
    analysis::Jets muons;
    for (int MuonNumber : Range(clones_arrays().MuonSum())) {
        ::delphes::Muon &muon = static_cast<::delphes::Muon &>(clones_arrays().Muon(MuonNumber));
        fastjet::PseudoJet muon_jet = analysis::PseudoJet(muon.P4());
        if (jet_detail == analysis::FourVector::kTagging) {
            Constituent constituent(muon.P4(), BranchFamily(*muon.Particle.GetObject()));
            muon_jet.set_user_info(new JetInfo(constituent, int(muon.Charge)));
        } else muon_jet.set_user_info(new JetInfo(int(muon.Charge)));
        muons.emplace_back(muon_jet);
    }
    PrintTruthLevel(kDebug);
    return muons;
}
