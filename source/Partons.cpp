/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "Partons.hh"
#include "generic/Types.hh"
#include "generic/DEBUG.hh"

namespace boca
{

Partons::Partons(boca::TreeReader const& tree_reader):
    FourVector(tree_reader) {}

Partons::~Partons() {}

}
