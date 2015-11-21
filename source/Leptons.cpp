/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Leptons.hh"

#include "Vector.hh"
#include "Debug.hh"

namespace boca {

Leptons::~Leptons()
{
  Info0;
}

void Leptons::NewEvent(TreeReader const& tree_reader)
{
    Info0;
    FourVector::NewEvent(tree_reader);
}

std::vector<Jet> Leptons::leptons() const
{
    Info0;
    return Join(Electrons(), Muons());
}

}
