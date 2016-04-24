/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/FourVector.hh"

namespace boca
{

FourVector::FourVector(boca::TreeReader const& tree_reader)
{
    tree_reader_ = &tree_reader;
}

boca::TreeReader const& FourVector::TreeReader() const
{
    return *tree_reader_;
}

}


