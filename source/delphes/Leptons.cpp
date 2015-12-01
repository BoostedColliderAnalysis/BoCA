/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "delphes/Leptons.hh"
#include "delphes/Delphes.hh"
#include "Types.hh"
#include "Debug.hh"

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
   std::vector<Lepton> electrons;
    for (auto const& electron : tree_reader().Objects<::delphes::Electron>(Branch::electron)) {
      Jet lepton(electron.P4(), int(electron.Charge));
        if (is(jet_detail,JetDetail::tagging)) lepton.Info().AddConstituent(electron.P4());
        electrons.emplace_back(lepton);
    }
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
        Jet lepton(muon.P4(), int(muon.Charge));
        if (is(jet_detail,JetDetail::tagging)) lepton.Info().AddConstituent(muon.P4());
        muons.emplace_back(lepton);
    }
    return muons;
}

}

}
