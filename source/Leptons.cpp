/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/Leptons.hh"

#include "boca/generic/Vector.hh"
#include "boca/generic/DEBUG.hh"

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
