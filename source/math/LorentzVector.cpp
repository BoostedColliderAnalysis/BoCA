#include <random>

#include "TLorentzVector.h"

#include "external/exroot/exroot/Classes.hh"
#include "external/delphes/delphes/Classes.hh"

#include "boca/math/LorentzVector.hh"
#include "boca/physics/Id.hh"

namespace boca
{

LorentzVector< Momentum >::LorentzVector()
{
    Scalar() = at_rest;
    Spatial() = {at_rest,  at_rest,  at_rest};
}

// LorentzVector< Momentum >::LorentzVector(const LorentzVectorBase<Momentum>& lorentz_vector)
// {
//     Vector() = lorentz_vector.Vector();
//     Scalar() = lorentz_vector.T();
// }

LorentzVector< Momentum >::LorentzVector(const TLorentzVector& lorentzvector)
{
    Spatial() = Vector3<double>(lorentzvector.Vect()) * GeV;
    Scalar() = lorentzvector.T() * GeV;
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

void LorentzVector< Momentum >::SetVectE(Vector3<boca::Momentum> const& vector, boca::Energy const& energy)
{
    SetVectT(vector, energy);
}

void LorentzVector< Momentum >::SetPtEtaPhiM(boca::Momentum const& pt, boca::Angle const& eta, boca::Angle const& phi, boca::Mass const& mass)
{
    SetPerpEtaPhiMag(pt, eta, phi, mass);
}

void LorentzVector< Momentum >::SetPtEtaPhiE(boca::Momentum const& pt, boca::Angle const& eta, boca::Angle const& phi, boca::Energy const& energy)
{
    SetPerpEtaPhiT(pt, eta, phi, energy);
}

void LorentzVector<Momentum>::SetVectM(const boca::Vector3<boca::Momentum> &spatial, const boca::Mass &mass)
{
    SetVectMag(spatial, mass);
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

Energy LorentzVector< Momentum >::E() const
{
    return T();
}

Energy LorentzVector< Momentum >::Energy() const
{
    return T();
}

Momentum& LorentzVector< Momentum >::Px()
{
    return X();
}

Momentum& LorentzVector< Momentum >::Py()
{
    return Y();
}

Momentum& LorentzVector< Momentum >::Pz()
{
    return Z();
}

Energy& LorentzVector< Momentum >::E()
{
    return T();
}

Energy& LorentzVector< Momentum >::Energy()
{
    return T();
}

Momentum LorentzVector< Momentum >::P() const
{
    return Rho();
}

EnergySquare LorentzVector< Energy >::Et2() const
{
    return ScalarT2();
}
Energy LorentzVector< Momentum >::Et() const
{
    return ScalarT();
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
    return MagT2();
}

Mass LorentzVector< Momentum >::Mt() const
{
    return MagT();
}

Momentum LorentzVector< Momentum >::Pt() const
{
    return Perp();
}

LorentzVector< Length >::LorentzVector()
{
    Scalar() = Length(0);
}

LorentzVector< Length >::LorentzVector(delphes::Track& track)
{
    Spatial() = Vector3<Length>(static_cast<double>(track.X) * mm, static_cast<double>(track.Y) * mm, static_cast<double>(track.Z) * mm);
    Scalar() = static_cast<double>(track.T) * mm;
}

LorentzVector< Length >::LorentzVector(delphes::GenParticle& particle)
{
    Spatial() = Vector3<Length>(static_cast<double>(particle.X) * mm, static_cast<double>(particle.Y) * mm, static_cast<double>(particle.Z) * mm);
    Scalar() = static_cast<double>(particle.T) * mm;
}

void LorentzVector< Length >::Smearing(Length const& amount)
{
    std::random_device random_device;
    auto generator = std::mt19937{random_device()};
    auto normal_distribution = std::normal_distribution<double>{0, amount / m};

    Scalar() += normal_distribution(generator) * m;
    X() += normal_distribution(generator) * m;
    Y() += normal_distribution(generator) * m;
    Z() += normal_distribution(generator) * m;
}

}
