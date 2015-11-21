// Author: Pasha Murat , Peter Malzacher  12/02/99
// Jan Hajer 2015

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

#include "Vector3.hh"
#include "exroot/ExRootAnalysis.hh"
#include "Units.hh"

class TLorentzVector;

namespace boca {

/**
 * @brief Copy of root::TLorentzVector in order to get rid of TObject which makes it unsuitable for heavy usage
 *
 */
class LorentzVector {

private:

// 3 vector component
    Vector3 p_;

// time or energy of (x,y,z,t) or (px,py,pz,e)
    float e_;

public:

  template<typename Particle>
  void LorentzVectorByEnergy(const Particle& particle)
  {
    float Pt = particle.PT;
    float Eta = particle.Eta;
    float Phi = particle.Phi;
    float Energy = particle.E;
    SetPtEtaPhiE(Pt, Eta, Phi, Energy);
  }

  template<typename Particle>
  void LorentzVectorByMass(const Particle& particle, Mass mass)
  {
    float Pt = particle.PT;
    float Eta = particle.Eta;
    float Phi = particle.Phi;
    SetPtEtaPhiM(Pt, Eta, Phi, mass / GeV);
  }

  template<typename Particle>
  void LorentzVectorByMass(const Particle& particle)
  {
    Mass mass(particle.Mass * GeV);
    LorentzVectorByMass(particle, mass);
  }

  template<typename Particle>
  void LorentzVectorByM(const Particle& particle)
  {
    Mass mass(particle.M * GeV);
    LorentzVectorByMass(particle, mass);
  }


  LorentzVector(exroot::Electron const& Particle);
  LorentzVector(exroot::GenJet const& Particle);
  LorentzVector(exroot::GenParticle const& Particle);
  LorentzVector(exroot::Jet const& Particle);
  LorentzVector(exroot::LHEFParticle const& Particle);
  LorentzVector(exroot::Muon const& Particle);
  LorentzVector(exroot::Photon const& Particle);
  LorentzVector(exroot::Tau const& Particle);









    void operator=(TLorentzVector const& lorentzvector);

// Safe indexing of the coordinates when using with matrices, arrays, etc.
    enum { kX = 0, kY = 1, kZ = 2, kT = 3, kNUM_COORDINATES = 4, kSIZE = kNUM_COORDINATES };

    LorentzVector();

// Constructor giving the components x, y, z, t.
    LorentzVector(float x, float y, float z, float t);

// Constructor from an array, not checked!
    LorentzVector(float const* carray);

// Constructor giving a 3-Vector and a time component.
    LorentzVector(Vector3 vector3, float t);

// Get position and time.
    float X() const;
    float Y() const;
    float Z() const;
    float T() const;

// Set position and time.
    void SetX(float a);
    void SetY(float a);
    void SetZ(float a);
    void SetT(float a);

// Get momentum and energy.
    float Px() const;
    float Py() const;
    float Pz() const;
    float P() const;
    float E() const;
    float Energy() const;

// Set momentum and energy.
    void SetPx(float a);
    void SetPy(float a);
    void SetPz(float a);
    void SetE(float a);

// Get spatial component.
    Vector3 Vect() const ;

// Set spatial component.
    void SetVect(Vector3 const& vect3);

// Get spatial vector components in spherical coordinate system.
    float Theta() const;
    float CosTheta() const;
    float Phi() const; //returns phi from -pi to pi
    float Rho() const;

// Set spatial vector components in spherical coordinate system.
    void SetTheta(float theta);
    void SetPhi(float phi);
    void SetRho(float rho);

// Setters to provide the functionality (but a more meanigful name) of
// the previous version eg SetV4... PsetV4...
    void SetPxPyPzE(float px, float py, float pz, float e);
    void SetXYZT(float x, float y, float z, float t);
    void SetXYZM(float x, float y, float z, float m);
    void SetPtEtaPhiM(float pt, float eta, float phi, float m);
    void SetPtEtaPhiE(float pt, float eta, float phi, float e);

// Getters into an arry
// no checking!
    void GetXYZT(float* carray) const;

// Get components by index.
    float operator()(int i) const;
    float operator [](int i) const;

// Set components by index.
    float& operator()(int i);
    float& operator [](int i);

// Additions.
    LorentzVector operator + (const LorentzVector&) const;
    LorentzVector& operator += (const LorentzVector&);

// Subtractions.
    LorentzVector operator - (const LorentzVector&) const;
    LorentzVector& operator -= (const LorentzVector&);

// Unary minus.
    LorentzVector operator - () const;

// Scaling with real numbers.
    LorentzVector operator * (float a) const;
    LorentzVector& operator *= (float a);

// Comparisons.
    bool operator == (const LorentzVector&) const;
    bool operator != (const LorentzVector&) const;

// Transverse component of the spatial vector squared.
    float Perp2() const;

// Transverse component of the spatial vector (R in cylindrical system).
    float Pt() const;
    float Perp() const;

// Set the transverse component of the spatial vector.
    void SetPerp(float);

// Transverse component of the spatial vector w.r.t. given axis squared.
    float Perp2(Vector3 const& v) const;

// Transverse component of the spatial vector w.r.t. given axis.
    float Pt(Vector3 const& v) const;
    float Perp(Vector3 const& v) const;

// Transverse energy squared.
    float Et2() const;

// Transverse energy.
    float Et() const;

// Transverse energy w.r.t. given axis squared.
    float Et2(Vector3 const&) const;

// Transverse energy w.r.t. given axis.
    float Et(Vector3 const&) const;

    float DeltaPhi(const LorentzVector&) const;
    float DeltaR(const LorentzVector&) const;
    float DrEtaPhi(const LorentzVector&) const;
//     Vector2<float> EtaPhiVector();

// Angle wrt. another vector.
    float Angle(Vector3 const& v) const;

// Invariant mass squared.
    float Mag2() const;
    float M2() const;

// Invariant mass. If mag2() is negative then -sqrt(-mag2()) is returned.
    float Mag() const;
    float M() const;

// Transverse mass squared.
    float Mt2() const;

// Transverse mass.
    float Mt() const;

    float Beta() const;
    float Gamma() const;

// Scalar product.
    float Dot(const LorentzVector&) const;
    float operator * (const LorentzVector&) const;

// Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)
    void SetVectMag(Vector3 const& spatial, float magnitude);
    void SetVectM(Vector3 const& spatial, float mass);

// Returns t +/- z.
// Related to the positive/negative light-cone component,
// which some define this way and others define as (t +/- z)/sqrt(2)
    float Plus() const;
    float Minus() const;

// Returns the spatial components divided by the time component.
    Vector3 BoostVector() const ;

// Lorentz boost.
    void Boost(float, float, float);
    void Boost(Vector3 const&);

// Returns the rapidity, i.e. 0.5*ln((E+pz)/(E-pz))
    float Rapidity() const;

// Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))
    float Eta() const;
    float PseudoRapidity() const;

// Rotate the spatial component around the x-axis.
    void RotateX(float angle);

// Rotate the spatial component around the y-axis.
    void RotateY(float angle);

// Rotate the spatial component around the z-axis.
    void RotateZ(float angle);

// Rotates the reference frame from Uz to newUz (unit vector).
    void RotateUz(Vector3& newUzVector);

};

LorentzVector operator * (float a, const LorentzVector&);

}
