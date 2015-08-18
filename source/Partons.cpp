/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Partons.hh"
#include "Types.hh"
#include "Debug.hh"

namespace analysis {

void Partons::NewEvent(const ClonesArrays& clones_arrays)
{
    Info();
    FourVector::NewEvent(clones_arrays);
}

}
