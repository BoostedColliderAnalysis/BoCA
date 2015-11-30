// Author: Pasha Murat , Peter Malzacher  12/02/99
// Jan Hajer 2015

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

#include "delphes/DelphesForward.hh"
#include "exroot/ExRootAnalysisForward.hh"

#include "LorentzVectorBase.hh"

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
    void LorentzVectorByMass(const Particle& particle, boca::Mass mass) {
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
    Momentum Px() const;
    Momentum Py() const;
    Momentum Pz() const;
    Momentum P() const;
    boca::Energy E() const;
    boca::Energy Energy() const;

    // Set momentum and energy.
    void SetPx(Momentum a);
    void SetPy(Momentum a);
    void SetPz(Momentum a);
    void SetE(boca::Energy a);
    // Transverse energy squared.
    EnergySqr Et2() const;

    // Transverse energy.
    boca::Energy Et() const;

    // Transverse energy w.r.t. given axis squared.
    EnergySqr Et2(Vector3<Momentum> const& v) const;

    // Transverse energy w.r.t. given axis.
    boca::Energy Et(Vector3<Momentum> const& v) const;

    // Setters to provide the functionality(but a more meanigful name) of
    void SetPxPyPzE(Momentum px, Momentum py, Momentum pz, boca::Energy energy);

    void SetPtEtaPhiM(Momentum pt, boca::Angle eta, boca::Angle phi, boca::Mass mass);

    void SetPtEtaPhiE(Momentum pt, boca::Angle eta, boca::Angle phi, boca::Energy energy);

    MassSqr M2() const;

    boca::Mass M() const;
    boca::Mass Mass() const;

    // Transverse mass squared.
    MassSqr Mt2() const;

    // Transverse mass.
    boca::Mass Mt() const;

    // Transverse component of the spatial vector(R in cylindrical system).
    Momentum Pt() const;

    // Transverse component of the spatial vector w.r.t. given axis.
    Momentum Pt(Vector3<Momentum> const& vector) const;
};

template<>
class LorentzVector<Length> : public LorentzVectorBase<Length>
{
public:

    using LorentzVectorBase<Length>::LorentzVectorBase;

    LorentzVector();

    LorentzVector(::delphes::Track& track);

    LorentzVector(::delphes::GenParticle& particle);

};


}

