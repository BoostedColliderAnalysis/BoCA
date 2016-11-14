
#include "boca/event/HemisphereMasses.hh"

namespace boca
{

HemisphereMasses::HemisphereMasses() {}

HemisphereMasses::HemisphereMasses(GradedLorentzVector<Momentum> const &negative, GradedLorentzVector<Momentum> const &positive, Momentum const &scalar_momentum)
{
    SetMasses(negative, positive);
    SetBroadenings(negative, positive, scalar_momentum);
}

HemisphereMasses::HemisphereMasses(boca::Range<double> const &masses, boca::Range<double> const &broadenings)
{
    SetMasses(masses);
    SetBroadenings(broadenings);
}

void HemisphereMasses::SetMasses(GradedLorentzVector<Momentum> const &negative, GradedLorentzVector<Momentum> const &positive)
{
    SetMasses(Range<EnergySquare>(negative.Vector().M2(), positive.Vector().M2()) / sqr(positive.Vector().E() + negative.Vector().E()));
}

void HemisphereMasses::SetMasses(boca::Range<double> const &masses)
{
    masses_ = masses;
}

void HemisphereMasses::SetBroadenings(GradedLorentzVector<Momentum> const &negative, GradedLorentzVector<Momentum> const &positive, Momentum const &scalar_momentum)
{
    SetBroadenings(Range<Energy>(negative.Scalar(), positive.Scalar()) / scalar_momentum / 2);
}

void HemisphereMasses::SetBroadenings(boca::Range<double> const &broadenings)
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
