/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Partons.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

void Partons::NewEvent(ClonesArrays const& clones_arrays)
{
    Info();
    FourVector::NewEvent(clones_arrays);
}

}
