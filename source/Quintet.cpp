#include "Quintet.hh"

namespace analysis {

  const Triplet& Quintet::Triplet() const
{
    return Multiplet1();
}

const Doublet& Quintet::Doublet() const
{
    return Multiplet2();
}

}
