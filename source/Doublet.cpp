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
    TVector2 pull = Singlet1().Pull() - Singlet1().Reference(Singlet2());
    return std::atan2(pull.Y(), pull.X());
}

float Doublet::Pull2() const
{
    Info();
    TVector2 pull = Singlet2().Pull() - Singlet2().Reference(Singlet1());
    return std::atan2(pull.Y(), pull.X());
}

float Doublet::PullDifference() const
{
    return RestrictPhi(::analysis::DeltaPhi(Pull1(), Pull2()) - M_PI);
}

float Doublet::PullSum() const
{
    return RestrictPhi(Pull1() + Pull2());
}

}
