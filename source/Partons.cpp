/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Partons.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

void Partons::NewEvent(TreeReader const& tree_reader)
{
    Info0;
    FourVector::NewEvent(tree_reader);
}

}
