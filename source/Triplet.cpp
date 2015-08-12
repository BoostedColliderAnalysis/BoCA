#include "Triplet.hh"

namespace analysis {

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
