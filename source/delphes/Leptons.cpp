/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "delphes/Leptons.hh"
#include "delphes/Delphes.hh"
#include "generic/Types.hh"
#include "generic/DEBUG.hh"

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
    for (auto const & electron : TreeReader().Array<::delphes::Electron>(Branch::electron)) electrons.emplace_back(Lepton(electron.P4(), int(electron.Charge)));
    return electrons;
}

std::vector<Lepton> Leptons::Muons() const
{
    INFO0;
    std::vector<Lepton> muons;
    for (auto const & muon : TreeReader().Array<::delphes::Muon>(Branch::muon)) muons.emplace_back(Lepton(muon.P4(), int(muon.Charge)));
    return muons;
}

std::vector<Lepton> Leptons::Photons() const
{
    INFO0;
    std::vector<Lepton> photons;
    for (auto const & muon : TreeReader().Array<::delphes::Photon>(Branch::photon)) photons.emplace_back(Lepton(muon.P4()));
    return photons;
}

}

}
