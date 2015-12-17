#include "exroot/Leptons.hh"

#include "exroot/ExRootAnalysis.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

namespace exroot {

  std::vector<Lepton> Leptons::Electrons() const
{
    Info0;
    std::vector<Lepton> leptons;
    for (auto const electron : tree_reader().Objects<::exroot::Electron>(Branch::electron)) leptons.emplace_back(Lepton(electron));
    return leptons;
}

std::vector<Lepton> Leptons::Muons() const
{
    Info0;
    std::vector<Lepton> leptons;
    for (auto const& muon : tree_reader().Objects<::exroot::Muon>(Branch::muon)) leptons.emplace_back(Lepton(muon));
    return leptons;
}

std::vector<Lepton> Leptons::Photons() const
{
  Info0;
  std::vector<Lepton> photons;
  for (auto const& photon : tree_reader().Objects<::exroot::Photon>(Branch::photon)) photons.emplace_back(Lepton(photon));
  return photons;
}

}

}
