// Author: Pasha Murat , Peter Malzacher  12/02/99
// Jan Hajer 2015 (tempaltes and units)

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

#include "boca/delphes/Forward.hh"
#include "boca/exroot/Forward.hh"

#include "boca/math/LorentzVectorBase.hh"

class TLorentzVector;

namespace boca
{

template<typename Value>
class LorentzVector : public LorentzVectorBase<Value>
{
    using LorentzVectorBase<Value>::LorentzVectorBase;
};

template<>
class LorentzVector<Momentum> : public LorentzVectorBase<Momentum>
{
public:

    using LorentzVectorBase<Momentum>::LorentzVectorBase;

    LorentzVector();

    LorentzVector(LorentzVectorBase<Momentum> const& lorentz_vector);

    LorentzVector(TLorentzVector const& lorentzvector);

    LorentzVector(exroot::Electron const& electron);

    LorentzVector(exroot::GenJet const& jet);

    LorentzVector(exroot::GenParticle const& particle);

    LorentzVector(exroot::Jet const& jet);

    LorentzVector(exroot::LHEFParticle const& particle);

    LorentzVector(exroot::Muon const& muon);

    LorentzVector(exroot::Photon const& photon);

    LorentzVector(exroot::Tau const& tau);

    template<typename Particle>
    void LorentzVectorByEnergy(const Particle& particle) {
        SetPtEtaPhiE(particle.PT * GeV, particle.Eta * rad, particle.Phi * rad, particle.E * GeV);
    }

    template<typename Particle>
    void LorentzVectorByMass(const Particle& particle, boca::Mass const& mass) {
        SetPtEtaPhiM(particle.PT * GeV, particle.Eta * rad, particle.Phi * rad, mass);
    }

    template<typename Particle>
    void LorentzVectorByMass(const Particle& particle) {
        LorentzVectorByMass(particle, particle.Mass * GeV);
    }

    template<typename Particle>
    void LorentzVectorByM(const Particle& particle) {
        LorentzVectorByMass(particle, particle.M * GeV);
    }
    // Get momentum and energy.
    Momentum const& Px() const;
    Momentum const& Py() const;
    Momentum const& Pz() const;
    boca::Energy const& E() const;
    boca::Energy const& Energy() const;
    Momentum & Px() ;
    Momentum & Py() ;
    Momentum & Pz() ;
    boca::Energy & E() ;
    boca::Energy & Energy() ;
    Momentum P() const;

    // Set momentum and energy.
    void SetPx(const boca::Momentum& a);
    void SetPy(Momentum const& a);
    void SetPz(Momentum const& a);
    void SetE(boca::Energy const& a);
    // Transverse energy squared.
    EnergySquare Et2() const;

    // Transverse energy.
    boca::Energy Et() const;

    // Transverse energy w.r.t. given axis squared.
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    EnergySquare Et2(Vector3<Value> const& vector) const {
        MomentumSquare pt2 = vector_3_.Perp2(vector);
        Momentum pv = vector_3_.Dot(vector.Unit());
        return pt2 == 0. * GeV2 ? 0. * GeV2 : sqr(E()) * pt2 / (pt2 + sqr(pv));
    }

    // Transverse energy w.r.t. given axis.
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    boca::Energy Et(Vector3<Value> const& vector) const {
        auto etet = Et2(vector);
        return E() < 0_GeV ? -sqrt(etet) : sqrt(etet);
    }

    // Setters to provide the functionality(but a more meanigful name) of
    void SetPxPyPzE(const boca::Momentum& px, const boca::Momentum& py, const boca::Momentum& pz, const boca::Energy& energy);

    void SetPtEtaPhiM(Momentum const& pt, boca::Angle const& eta, boca::Angle const& phi, boca::Mass const& mass);

    void SetPtEtaPhiE(Momentum const& pt, boca::Angle const& eta, boca::Angle const& phi, boca::Energy const& energy);

    MassSquare M2() const;

    boca::Mass M() const;
    boca::Mass Mass() const;

    // Transverse mass squared.
    MassSquare Mt2() const;

    // Transverse mass.
    boca::Mass Mt() const;

    // Transverse component of the spatial vector(R in cylindrical system).
    Momentum Pt() const;

    // Transverse component of the spatial vector w.r.t. given axis.
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    Momentum Pt(Vector3<Value> const& vector) const
    {
      return Perp(vector);
    }
};

template<>
class LorentzVector<Length> : public LorentzVectorBase<Length>
{
public:

    using LorentzVectorBase<Length>::LorentzVectorBase;

    LorentzVector();

    LorentzVector(::delphes::Track& track);

    LorentzVector(::delphes::GenParticle& particle);

    void Smearing(const boca::Length& amount);

};

template<typename Value_>
using GradedLorentzVector = GradedContainer<LorentzVector, Value_>;

}

