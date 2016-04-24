/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/Partons.hh"
#include "boca/generic/Types.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

Partons::Partons(boca::TreeReader const& tree_reader):
    FourVector(tree_reader) {}

Partons::~Partons() {}

}
