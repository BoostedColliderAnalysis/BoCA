#include "Triplet.hh"

namespace analysis {

Doublet& Triplet::Doublet() const
{
    return Multiplet1();
}

Singlet& Triplet::Singlet() const
{
    return Multiplet2();
}

}
