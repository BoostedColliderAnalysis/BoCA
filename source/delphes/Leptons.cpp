# include "delphes/Leptons.hh"
# include "Predicate.hh"

namespace analysis
{

namespace delphes
{

Leptons::Leptons()
{
    Print(Severity::notification, "Constructor");
}
Jets Leptons::Electrons()
{
    Print(Severity::information, "Electrons", clones_arrays().ElectronSum());
    return Electrons(kPlain);
}

Jets Leptons::Electrons(FourVector::JetDetail jet_detail)
{
    Print(Severity::information, "Electrons", clones_arrays().ElectronSum());
    Jets electrons;
    for (int ElectronNumber : Range(clones_arrays().ElectronSum())) {
        ::Electron &electron = static_cast<::Electron &>(clones_arrays().Electron(ElectronNumber));
        fastjet::PseudoJet electron_jet = analysis::PseudoJet(electron.P4());
        if (jet_detail == FourVector::kTagging) {
            Constituent constituent(electron.P4(), BranchFamily(*electron.Particle.GetObject()));
            electron_jet.set_user_info(new JetInfo(constituent, int(electron.Charge)));
        } else electron_jet.set_user_info(new JetInfo(int(electron.Charge)));
        electrons.emplace_back(electron_jet);
    }
    PrintTruthLevel(Severity::debug);
    return electrons;
}

Jets Leptons::Muons()
{
    Print(Severity::information, "Muons", clones_arrays().MuonSum());
    return Muons(kPlain);
}

Jets Leptons::Muons(JetDetail jet_detail)
{
    Print(Severity::information, "Muons", clones_arrays().MuonSum());
    Jets muons;
    for (int MuonNumber : Range(clones_arrays().MuonSum())) {
        ::Muon &muon = static_cast<::Muon &>(clones_arrays().Muon(MuonNumber));
        fastjet::PseudoJet muon_jet = analysis::PseudoJet(muon.P4());
        if (jet_detail == FourVector::kTagging) {
            Constituent constituent(muon.P4(), BranchFamily(*muon.Particle.GetObject()));
            muon_jet.set_user_info(new JetInfo(constituent, int(muon.Charge)));
        } else muon_jet.set_user_info(new JetInfo(int(muon.Charge)));
        muons.emplace_back(muon_jet);
    }
    PrintTruthLevel(Severity::debug);
    return muons;
}

}

}
