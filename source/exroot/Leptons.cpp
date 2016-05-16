/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/io/TreeReader.hh"
#include "boca/exroot/Leptons.hh"

#include "boca/exroot/Classes.hh"
#include "boca/generic/Types.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace exroot
{

Leptons::Leptons(boca::TreeReader const& tree_reader) :
    boca::Leptons(tree_reader) {}

std::vector<Lepton> Leptons::Electrons() const
{
    INFO0;
    std::vector<Lepton> electrons;
    for (auto const& electron : TreeReader().Array<::exroot::Electron>(Branch::electron)) electrons.emplace_back(Lepton(electron));
    return electrons;
}

std::vector<Lepton> Leptons::Muons() const
{
    INFO0;
    std::vector<Lepton> muons;
    for (auto const & muon : TreeReader().Array<::exroot::Muon>(Branch::muon)) muons.emplace_back(Lepton(muon));
    return muons;
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
