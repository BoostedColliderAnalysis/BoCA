
#include "boca/HemisphereMasses.hh"
namespace boca
{
void HemisphereMasses::SetMasses(const boca::Range< double >& masses)
{
    masses_ = masses;
}
void HemisphereMasses::SetBroadenings(const boca::Range< double >& broadenings)
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
