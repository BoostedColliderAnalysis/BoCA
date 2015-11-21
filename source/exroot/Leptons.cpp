#include "exroot/Leptons.hh"

#include "exroot/ExRootAnalysis.hh"
#include "JetInfo.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

namespace exroot {

  std::vector<Lepton> Leptons::Electrons() const
{
    Info0;
    std::vector<Lepton> leptons;
    for (auto const electron : tree_reader().Objects<::exroot::Electron>(Branch::electron)) {
        Lepton lepton(electron);
        lepton.Info().SetCharge(electron.Charge);
        leptons.emplace_back(lepton);
    }
    return leptons;
}

std::vector<Lepton> Leptons::Muons() const
{
    Info0;
    std::vector<Lepton> leptons;
    for (auto const& muon : tree_reader().Objects<::exroot::Muon>(Branch::muon)) {
        Lepton lepton(muon);
        lepton.Info().SetCharge(muon.Charge);
        leptons.emplace_back(lepton);
    }
    return leptons;
}

}

}
