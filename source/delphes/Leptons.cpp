/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "delphes/Leptons.hh"
#include "delphes/Delphes.hh"
#include "Types.hh"
#include "Debug.hh"
#include "JetInfo.hh"

namespace boca {

namespace delphes {

Jets Leptons::Electrons() const
{
//     Info(tree_reader().ElectronSum());
    return Electrons(JetDetail::plain);
}

Jets Leptons::Electrons(JetDetail jet_detail) const
{
//     Info(tree_reader().ElectronSum());
    Jets electrons;
    for (auto const& electron : tree_reader().Objects<::delphes::Electron>(Branch::electron)) {
        fastjet::PseudoJet electron_jet = boca::PseudoJet(electron.P4());
        if (is(jet_detail,JetDetail::tagging)) {
            Constituent constituent(electron.P4()/*, BranchFamily(*electron.Particle.GetObject())*/);
            electron_jet.set_user_info(new JetInfo(constituent, int(electron.Charge)));
        } else electron_jet.set_user_info(new JetInfo(int(electron.Charge)));
        electrons.emplace_back(electron_jet);
    }
//     PrintTruthLevel(Severity::debug);
    return electrons;
}

Jets Leptons::Muons() const
{
//     Info(tree_reader().MuonSum());
    return Muons(JetDetail::plain);
}

Jets Leptons::Muons(JetDetail jet_detail) const
{
//     Info(tree_reader().MuonSum());
    Jets muons;
    for (auto const& muon : tree_reader().Objects<::delphes::Muon>(Branch::muon)) {
        fastjet::PseudoJet muon_jet = boca::PseudoJet(muon.P4());
        if (is(jet_detail,JetDetail::tagging)) {
            Constituent constituent(muon.P4()/*, BranchFamily(*muon.Particle.GetObject())*/);
            muon_jet.set_user_info(new JetInfo(constituent, int(muon.Charge)));
        } else muon_jet.set_user_info(new JetInfo(int(muon.Charge)));
        muons.emplace_back(muon_jet);
    }
//     PrintTruthLevel(Severity::debug);
    return muons;
}

}

}
