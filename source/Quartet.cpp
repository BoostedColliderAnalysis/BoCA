#include "Quartet.hh"

namespace analysis {

Doublet const& Quartet22::Doublet1() const
{
    return Multiplet1();
}

Doublet const& Quartet22::Doublet2() const
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

Triplet const& Quartet31::Triplet() const
{
    return Multiplet1();
}

Singlet const& Quartet31::Singlet() const
{
    return Multiplet2();
}

Doublet const& Quartet211::Doublet() const
{
  return Multiplet1();
}

Singlet const& Quartet211::Singlet1() const
{
  return Multiplet2();
}

Singlet const& Quartet211::Singlet2() const
{
  return Multiplet3();
}

}
