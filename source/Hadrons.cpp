/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Hadrons.hh"
#include "Debug.hh"

namespace boca {

void Hadrons::NewEvent(ClonesArrays const& clones_arrays)
{
    Info();
    FourVector::NewEvent(clones_arrays);
}

float Hadrons::ScalarHt() const
{
    Error("No Scalar Ht");
    return 0;
}

fastjet::PseudoJet Hadrons::MissingEt() const
{
    Error("No Mising Et");
    return fastjet::PseudoJet {};
}

}
