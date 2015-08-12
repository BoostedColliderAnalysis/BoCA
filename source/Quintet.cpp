#include "Quintet.hh"

namespace analysis {

  Triplet const& Quintet::Triplet() const
{
    return Multiplet1();
}

Doublet const& Quintet::Doublet() const
{
    return Multiplet2();
}

}
