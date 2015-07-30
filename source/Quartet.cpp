#include "Quartet.hh"

namespace analysis {

Doublet& Quartet22::Doublet1() const
{
    return Multiplet1();
}

Doublet& Quartet22::Doublet2() const
{
    return Multiplet2();
}

Triplet& Quartet31::Triplet() const
{
    return Multiplet1();
}

Singlet& Quartet31::Singlet() const
{
    return Multiplet2();
}

}
