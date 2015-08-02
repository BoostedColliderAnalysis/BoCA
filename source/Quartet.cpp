#include "Quartet.hh"

namespace analysis {

const Doublet& Quartet22::Doublet1() const
{
    return Multiplet1();
}

const Doublet& Quartet22::Doublet2() const
{
    return Multiplet2();
}

Doublet& Quartet22::Doublet1()
{
  return Multiplet1();
}

Doublet& Quartet22::Doublet2()
{
  return Multiplet2();
}

const Triplet& Quartet31::Triplet() const
{
    return Multiplet1();
}

const Singlet& Quartet31::Singlet() const
{
    return Multiplet2();
}

}
