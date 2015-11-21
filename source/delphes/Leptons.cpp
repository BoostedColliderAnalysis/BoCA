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

std::vector<Jet> Leptons::Electrons() const
{
    Info0;
    return Electrons(JetDetail::plain);
}

std::vector<Jet> Leptons::Electrons(JetDetail jet_detail) const
{
   Info0;
   std::vector<Jet> electrons;
    for (auto const& electron : tree_reader().Objects<::delphes::Electron>(Branch::electron)) {
        Jet electron_jet(electron.P4());
        if (is(jet_detail,JetDetail::tagging)) {
            Constituent constituent(electron.P4()/*, BranchFamily(*electron.Particle.GetObject())*/);
            electron_jet.set_user_info(new JetInfo(constituent, int(electron.Charge)));
        } else electron_jet.set_user_info(new JetInfo(int(electron.Charge)));
        electrons.emplace_back(electron_jet);
    }
//     PrintTruthLevel(Severity::debug);
    return electrons;
}

std::vector<Jet> Leptons::Muons() const
{
    Info0;
    return Muons(JetDetail::plain);
}

std::vector<Jet> Leptons::Muons(JetDetail jet_detail) const
{
   Info0;
   std::vector<Jet> muons;
    for (auto const& muon : tree_reader().Objects<::delphes::Muon>(Branch::muon)) {
        Jet muon_jet(muon.P4());
        if (is(jet_detail,JetDetail::tagging)) {
            Constituent constituent(muon.P4()/*, BranchFamily(*muon.Particle.GetObject())*/);
            muon_jet.set_user_info(new JetInfo(constituent, int(muon.Charge)));
        } else muon_jet.set_user_info(new JetInfo(int(muon.Charge)));
        muons.emplace_back(muon_jet);
    }
    return muons;
}

}

}
