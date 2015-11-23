/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Hadrons.hh"
#include "Debug.hh"

namespace boca {

void Hadrons::NewEvent(TreeReader const& tree_reader)
{
    Info0;
    FourVector::NewEvent(tree_reader);
}

Momentum Hadrons::ScalarHt() const
{
    Error("No Scalar Ht");
    return at_rest;
}

boca::MissingEt Hadrons::MissingEt() const
{
    Error("No Mising Et");
    return {};
}

}
