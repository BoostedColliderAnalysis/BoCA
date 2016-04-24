/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Sextet.hh"

namespace boca {

Triplet const& Sextet::Triplet1() const
{
    return Multiplet1();
}

Triplet const& Sextet::Triplet2() const
{
    return Multiplet2();
}

Triplet & Sextet::Triplet1()
{
  return Multiplet1();
}

Triplet & Sextet::Triplet2()
{
  return Multiplet2();
}
Momentum Sextet::HardTopPt() const
{
    return std::max(Triplet1().Pt(), Triplet2().Pt());
}
Momentum Sextet::SoftTopPt() const
{
    return std::min(Triplet1().Pt(), Triplet2().Pt());
}
Angle Sextet::GetLargertripletDeltaR() const
{
    return std::max(Triplet1().DeltaR(), Triplet2().DeltaR());
}
Angle Sextet::GetSmallertripletDeltaR() const
{
    return std::min(Triplet1().DeltaR(), Triplet2().DeltaR());
}
Angle Sextet::GetLargertripletDeltaRap() const
{
    return std::max(Triplet1().DeltaRap(), Triplet2().DeltaRap());
}
Angle Sextet::GetSmallertripletDeltaRap() const
{
    return std::min(Triplet1().DeltaRap(), Triplet2().DeltaRap());
}
Angle Sextet::GetLargerTripleDeltaPhi() const
{
    return std::max(boost::units::abs(Triplet1().DeltaPhi()), boost::units::abs(Triplet2().DeltaPhi()));
}
Angle Sextet::GetSmallertripletDeltaPhi() const
{
    return std::min(boost::units::abs(Triplet1().DeltaPhi()), boost::units::abs(Triplet2().DeltaPhi()));
}
Mass Sextet::GetBetterTripleMass(Id id) const
{
    return boost::units::fmin(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
}
Mass Sextet::GetWorseTripleMass(Id id) const
{
    return boost::units::fmax(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
}
Mass Sextet::GetBetterPairMass(Id id) const
{
    return boost::units::fmin(Triplet1().Doublet().MassDifferenceTo(id), Triplet2().Doublet().MassDifferenceTo(id));
}
Mass Sextet::GetWorsePairMass(Id id) const
{
    return boost::units::fmax(Triplet1().Doublet().MassDifferenceTo(id), Triplet2().Doublet().MassDifferenceTo(id));
}
Mass Sextet::GetBetterJetMass(Id id) const
{
    return boost::units::fmin(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
}
Mass Sextet::GetWorseJetMass(Id id) const
{
    return boost::units::fmax(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
}

}
