/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "Leptons.hh"

#include "Vector.hh"
#include "DEBUG.hh"

namespace boca
{

Leptons::Leptons(boca::TreeReader const& tree_reader) :
    FourVector(tree_reader) {}

Leptons::~Leptons()
{
    INFO0;
}

std::vector<Lepton> Leptons::leptons() const
{
    INFO0;
    return Combine(Electrons(), Muons());
}

}
