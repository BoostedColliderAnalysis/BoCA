#include "exroot/Leptons.hh"

#include "exroot/Classes.hh"
#include "generic/Types.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace exroot
{

Leptons::Leptons(boca::TreeReader const& tree_reader) :
    boca::Leptons(tree_reader) {}

std::vector<Lepton> Leptons::Electrons() const
{
    INFO0;
    std::vector<Lepton> leptons;
    for (auto const electron : TreeReader().Array<::exroot::Electron>(Branch::electron)) leptons.emplace_back(Lepton(electron));
    return leptons;
}

std::vector<Lepton> Leptons::Muons() const
{
    INFO0;
    std::vector<Lepton> leptons;
    for (auto const & muon : TreeReader().Array<::exroot::Muon>(Branch::muon)) leptons.emplace_back(Lepton(muon));
    return leptons;
}

std::vector<Lepton> Leptons::Photons() const
{
    INFO0;
    std::vector<Lepton> photons;
    for (auto const & photon : TreeReader().Array<::exroot::Photon>(Branch::photon)) photons.emplace_back(Lepton(photon));
    return photons;
}

}

}
