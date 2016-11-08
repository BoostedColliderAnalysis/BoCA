
#include "boca/event/HemisphereMasses.hh"

namespace boca
{

HemisphereMasses::HemisphereMasses() {}

HemisphereMasses::HemisphereMasses(boca::Range<double> const& masses, boca::Range<double> const& broadenings)
{
  SetMasses(masses);
  SetBroadenings(broadenings);
}

void HemisphereMasses::SetMasses(boca::Range<double> const& masses)
{
    masses_ = masses;
}

void HemisphereMasses::SetBroadenings(boca::Range<double> const& broadenings)
{
    broadenings_ = broadenings;
}

double HemisphereMasses::MHigh2() const
{
    return masses_.Max();
}

double HemisphereMasses::MLow2() const
{
    return masses_.Min();
}

double HemisphereMasses::MDiff2() const
{
    return masses_.Length();
}

double HemisphereMasses::BMax() const
{
    return broadenings_.Max();
}

double HemisphereMasses::BMin() const
{
    return broadenings_.Min();
}

double HemisphereMasses::BSum() const
{
    return broadenings_.Sum();
}

double HemisphereMasses::BDiff() const
{
    return broadenings_.Length();
}

}
