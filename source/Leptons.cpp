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

void Leptons::NewEvent(ClonesArrays const& clones_arrays)
{
    Info0;
    FourVector::NewEvent(clones_arrays);
}

Jets Leptons::leptons() const
{
    Info0;
    return Join(Electrons(), Muons());
}

}
