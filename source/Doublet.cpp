#include "Doublet.hh"
#include "Debug.hh"

namespace analysis
{

Singlet& Doublet::Singlet1() const
{
    return Multiplet1();
}

Singlet& Doublet::Singlet2() const
{
    return Multiplet2();
}


float Doublet::Pull1() const
{
    Info();
    TVector2 pull = Singlet1().Pull() - Singlet2().Reference(Singlet1().Jet());
    return std::atan2(pull.X(), pull.Y());
}

float Doublet::Pull2() const
{
    Info();
    TVector2 pull = Singlet2().Pull() - Singlet1().Reference(Singlet2().Jet());
    return std::atan2(pull.X(), pull.Y());
}

float Doublet::PullDifference() const
{
    return Pull1() - Pull2();
}

}
