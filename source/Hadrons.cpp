/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Hadrons.hh"
#include "Debug.hh"

namespace boca
{

Hadrons::Hadrons(boca::TreeReader const& tree_reader) :
    FourVector(tree_reader) {}

Momentum Hadrons::ScalarHt() const
{
    ERROR("No Scalar Ht");
    return at_rest;
}

boca::MissingEt Hadrons::MissingEt() const
{
    ERROR("No Mising Et");
    return {};
}

}
