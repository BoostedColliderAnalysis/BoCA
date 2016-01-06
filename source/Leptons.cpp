/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Leptons.hh"

#include "Vector.hh"
#include "Debug.hh"

namespace boca
{

Leptons::Leptons(boca::TreeReader const& tree_reader) :
    FourVector(tree_reader) {}

Leptons::~Leptons()
{
    Info0;
}

std::vector<Lepton> Leptons::leptons() const
{
    Info0;
    return Join(Electrons(), Muons());
}

}
