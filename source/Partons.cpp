/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Partons.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca
{

Partons::Partons(boca::TreeReader const& tree_reader):
    FourVector(tree_reader) {}

Partons::~Partons() {}

}
