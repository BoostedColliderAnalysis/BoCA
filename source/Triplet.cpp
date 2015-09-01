/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Triplet.hh"

namespace boca {

Doublet const& Triplet::Doublet() const
{
    return Multiplet1();
}

Doublet& Triplet::Doublet()
{
  return Multiplet1();
}

Singlet const& Triplet::Singlet() const
{
    return Multiplet2();
}

}
