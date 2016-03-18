/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "delphes/Leptons.hh"
#include "delphes/Delphes.hh"
#include "Types.hh"
#include "DEBUG.hh"

namespace boca
{

namespace delphes
{

Leptons::Leptons(boca::TreeReader const& tree_reader) :
    boca::Leptons(tree_reader) {}

std::vector<Lepton> Leptons::Electrons() const
{
    INFO0;
    std::vector<Lepton> electrons;
    for (auto const & electron : TreeReader().Objects<::delphes::Electron>(Branch::electron)) electrons.emplace_back(Lepton(electron.P4(), int(electron.Charge)));
    return electrons;
}

std::vector<Lepton> Leptons::Muons() const
{
    INFO0;
    std::vector<Lepton> muons;
    for (auto const & muon : TreeReader().Objects<::delphes::Muon>(Branch::muon)) muons.emplace_back(Lepton(muon.P4(), int(muon.Charge)));
    return muons;
}

std::vector<Lepton> Leptons::Photons() const
{
    INFO0;
    std::vector<Lepton> photons;
    for (auto const & muon : TreeReader().Objects<::delphes::Photon>(Branch::photon)) photons.emplace_back(Lepton(muon.P4()));
    return photons;
}

}

}
