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
EnergySquare LorentzVector< Energy >::Et2() const
{
    MomentumSquare pt2 = vector_3_.Perp2();
    return pt2 == 0. * GeV2 ? 0. * GeV2 : sqr(E()) * pt2 / (pt2 + sqr(Z()));
}
Energy LorentzVector< Momentum >::Et() const
{
    EnergySquare etet = Et2();
    return E() < 0_GeV ? -sqrt(etet) : sqrt(etet);
}
MassSquare LorentzVector< Momentum >::M2() const
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
MassSquare LorentzVector< Momentum >::Mt2() const
{
    return sqr(E()) - sqr(Z());
}
Mass LorentzVector< Momentum >::Mt() const
{
    MassSquare mt2 = Mt2();
    return mt2 < 0. * GeV2 ? -sqrt(-mt2) : sqrt(mt2);
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

void LorentzVector< Length >::Smearing(Length amount)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::normal_distribution<double> normal_distribution(0, amount / m);

    scalar_ += normal_distribution(generator) * m;
    vector_3_.X() += normal_distribution(generator) * m;
    vector_3_.Y() += normal_distribution(generator) * m;
    vector_3_.Z() += normal_distribution(generator) * m;

}

}
