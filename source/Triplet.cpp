#include "Triplet.hh"

namespace analysis {

const Doublet& Triplet::Doublet() const
{
    return Multiplet1();
}

Doublet& Triplet::Doublet()
{
  return Multiplet1();
}

const Singlet& Triplet::Singlet() const
{
    return Multiplet2();
}

}
