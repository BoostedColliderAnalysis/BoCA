// @(#)root/physics:$Id$
// Author: Pasha Murat , Peter Malzacher  12/02/99
//    Oct  8 1999: changed Warning to Error and
//                 return fX in Doublscalar_t & operator()
//    Oct 20 1999: dito in Doublscalar_t operator()
//    Jan 25 2000: implemented as (fP,fE) instead of (fX,fY,fZ,fE)
//           2015  Jan Hajer

#include "TLorentzVector.h"

#include "exroot/ExRootAnalysis.hh"
#include "delphes/Delphes.hh"

#include "physics/LorentzVector.hh"
#include "physics/Particles.hh"

namespace boca
{

void LorentzVector< Momentum >::SetPtEtaPhiM(boca::Momentum pt, boca::Angle eta, boca::Angle phi, boca::Mass mass)
{
    pt = boost::units::abs(pt);
    SetXYZM(pt * boost::units::cos(phi), pt * boost::units::sin(phi), pt * units::sinh(eta) , mass);
}

void LorentzVector< Momentum >::SetPtEtaPhiE(boca::Momentum pt, boca::Angle eta, boca::Angle phi, boca::Energy energy)
{
    pt = boost::units::abs(pt);
    SetXYZT(pt * boost::units::cos(phi), pt * boost::units::sin(phi), pt * units::sinh(eta) , energy);
}
LorentzVector< Momentum >::LorentzVector(const exroot::Tau& tau)
{
    LorentzVectorByMass(tau, MassOf(Id::tau));
}
LorentzVector< Momentum >::LorentzVector(const exroot::Photon& photon)
{
    LorentzVectorByMass(photon, MassOf(Id::photon));
}
LorentzVector< Momentum >::LorentzVector(const exroot::Electron& electron)
{
    LorentzVectorByMass(electron, MassOf(Id::electron));
}
LorentzVector< Momentum >::LorentzVector(const exroot::GenJet& jet)
{
    LorentzVectorByMass(jet);
}
LorentzVector< Momentum >::LorentzVector(const exroot::GenParticle& particle)
{
    LorentzVectorByEnergy(particle);
}
LorentzVector< Momentum >::LorentzVector(const exroot::Jet& jet)
{
    LorentzVectorByMass(jet);
}
LorentzVector< Momentum >::LorentzVector(const exroot::LHEFParticle& particle)
{
    LorentzVectorByM(particle);
}
LorentzVector< Momentum >::LorentzVector(const exroot::Muon& muon)
{
    LorentzVectorByMass(muon, MassOf(Id::muon));
}
Momentum LorentzVector< Momentum >::Px() const
{
    return X();
}
Momentum LorentzVector< Momentum >::Py() const
{
    return Y();
}
Momentum LorentzVector< Momentum >::Pz() const
{
    return Z();
}
Momentum LorentzVector< Momentum >::P() const
{
    return vector_3_.Mag();
}
Energy LorentzVector< Momentum >::E() const
{
    return T();
}
Energy LorentzVector< Momentum >::Energy() const
{
    return T();
}
void LorentzVector< Momentum >::SetPx(Momentum a)
{
    SetX(a);
}
void LorentzVector< Momentum >::SetPy(Momentum a)
{
    SetY(a);
}
void LorentzVector< Momentum >::SetPz(Momentum a)
{
    SetZ(a);
}
void LorentzVector< Momentum >::SetE(boca::Energy a)
{
    SetT(a);
}
EnergySqr LorentzVector< Energy >::Et2() const
{
    MomentumSqr pt2 = vector_3_.Perp2();
    return pt2 == 0. * GeV * GeV ? 0. * GeV * GeV : E() * E() * pt2 / (pt2 + Z() * Z());
}
Energy LorentzVector< Momentum >::Et() const
{
    EnergySqr etet = Et2();
    return E() < 0. * GeV ? -sqrt(etet) : sqrt(etet);
}
EnergySqr LorentzVector< Momentum >::Et2(const Vector3< Momentum >& v) const
{
    MomentumSqr pt2 = vector_3_.Perp2(v);
    Momentum pv = vector_3_.Dot(v.Unit()) / GeV; // FIXME this looks fishy
    return pt2 == 0. * GeV * GeV ? 0. * GeV * GeV : E() * E() * pt2 / (pt2 + pv * pv);
}
Energy LorentzVector< Momentum >::Et(const Vector3< Momentum >& v) const
{
    EnergySqr etet = Et2(v);
    return E() < 0. * GeV ? -sqrt(etet) : sqrt(etet);
}
MassSqr LorentzVector< Momentum >::M2() const
{
    return Mag2();
}
Mass LorentzVector< Momentum >::M() const
{
    return Mag();
}
Mass LorentzVector< Momentum >::Mass() const
{
    return Mag();
}
MassSqr LorentzVector< Momentum >::Mt2() const
{
    return sqr(E()) - sqr(Z());
}
Mass LorentzVector< Momentum >::Mt() const
{
    MassSqr mm = Mt2();
    return mm < 0. * GeV * GeV ? -sqrt(-mm) : sqrt(mm);
}
LorentzVector< Momentum >::LorentzVector()
{
    scalar_ = Momentum(0);
}
LorentzVector< Length >::LorentzVector()
{
    scalar_ = Length(0);
}
void LorentzVector< Momentum >::SetPxPyPzE(boca::Momentum px, boca::Momentum py, boca::Momentum pz, boca::Energy energy)
{
    SetXYZT(px, py, pz, energy);
}
Momentum LorentzVector< Momentum >::Pt() const
{
    return Perp();
}
Momentum LorentzVector< Momentum >::Pt(const Vector3< Momentum >& vector) const
{
    return Perp(vector);
}

LorentzVector< Momentum >::LorentzVector(const LorentzVectorBase<Momentum>& lorentz_vector)
{
    vector_3_ = lorentz_vector.Vect();
    scalar_ = lorentz_vector.T();
}

LorentzVector< Momentum >::LorentzVector(const TLorentzVector& lorentzvector)
{
    vector_3_ = Vector3<double>(lorentzvector.Vect()) * GeV;
    scalar_ = lorentzvector.T() * GeV;
}

// void LorentzVector< Momentum >::operator=(const TLorentzVector& lorentzvector)
// {
//     vector_3_ = Vector3<double>(lorentzvector.Vect()) * GeV;
//     scalar_ = lorentzvector.T() * GeV;
// }

LorentzVector< Length >::LorentzVector(delphes::Track& track)
{
  vector_3_ = Vector3<Length>(double(track.X) * mm, double(track.Y) * mm, double(track.Z) * mm);
  scalar_ = double(track.T) * mm;
}
LorentzVector< Length >::LorentzVector(delphes::GenParticle& particle)
{
  SetVect(Vector3<Length>(double(particle.X) * mm, double(particle.Y) * mm, double(particle.Z) * mm));
  scalar_ = double(particle.T) * mm;
}
}
