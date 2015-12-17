/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "delphes/Leptons.hh"
#include "delphes/Delphes.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca
{

namespace delphes
{

std::vector<Lepton> Leptons::Electrons() const
{
    Info0;
    std::vector<Lepton> electrons;
    for (auto const & electron : tree_reader().Objects<::delphes::Electron>(Branch::electron)) electrons.emplace_back(Lepton(electron.P4(), int(electron.Charge)));
    return electrons;
}

std::vector<Lepton> Leptons::Muons() const
{
    Info0;
    std::vector<Lepton> muons;
    for (auto const & muon : tree_reader().Objects<::delphes::Muon>(Branch::muon)) muons.emplace_back(Lepton(muon.P4(), int(muon.Charge)));
    return muons;
}

std::vector<Lepton> Leptons::Photons() const
{
  Info0;
  std::vector<Lepton> photons;
  for (auto const & muon : tree_reader().Objects<::delphes::Photon>(Branch::photon)) photons.emplace_back(Lepton(muon.P4()));
  return photons;
}



}

}
