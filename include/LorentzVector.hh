#pragma once

#include "Vector3.hh"

class TLorentzVector;

namespace analysis
{

/**
 * @brief Copy of root::TLorentzVector in order to get rid of TObject
 *
 */
class LorentzVector
{

private:

// 3 vector component
    Vector3 p_;

// time or energy of (x,y,z,t) or (px,py,pz,e)
    float e_;

public:

    void operator=(const TLorentzVector &lorentzvector);

// Safe indexing of the coordinates when using with matrices, arrays, etc.
    enum { kX = 0, kY = 1, kZ = 2, kT = 3, kNUM_COORDINATES = 4, kSIZE = kNUM_COORDINATES };

    LorentzVector();

// Constructor giving the components x, y, z, t.
    LorentzVector(float x, float y, float z, float t);

// Constructor from an array, not checked!
    LorentzVector(const float *carray);

// Constructor giving a 3-Vector and a time component.
    LorentzVector(const Vector3 &vector3, float t);

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
    void SetVect(const Vector3 &vect3);

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
    void GetXYZT(float *carray) const;

// Get components by index.
    float operator()(int i) const;
    float operator [](int i) const;

// Set components by index.
    float &operator()(int i);
    float &operator [](int i);

// Additions.
    LorentzVector operator + (const LorentzVector &) const;
    LorentzVector &operator += (const LorentzVector &);

// Subtractions.
    LorentzVector operator - (const LorentzVector &) const;
    LorentzVector &operator -= (const LorentzVector &);

// Unary minus.
    LorentzVector operator - () const;

// Scaling with real numbers.
    LorentzVector operator * (float a) const;
    LorentzVector &operator *= (float a);

// Comparisons.
    bool operator == (const LorentzVector &) const;
    bool operator != (const LorentzVector &) const;

// Transverse component of the spatial vector squared.
    float Perp2() const;

// Transverse component of the spatial vector (R in cylindrical system).
    float Pt() const;
    float Perp() const;

// Set the transverse component of the spatial vector.
    void SetPerp(float);

// Transverse component of the spatial vector w.r.t. given axis squared.
    float Perp2(const Vector3 &v) const;

// Transverse component of the spatial vector w.r.t. given axis.
    float Pt(const Vector3 &v) const;
    float Perp(const Vector3 &v) const;

// Transverse energy squared.
    float Et2() const;

// Transverse energy.
    float Et() const;

// Transverse energy w.r.t. given axis squared.
    float Et2(const Vector3 &) const;

// Transverse energy w.r.t. given axis.
    float Et(const Vector3 &) const;

    float DeltaPhi(const LorentzVector &) const;
    float DeltaR(const LorentzVector &) const;
    float DrEtaPhi(const LorentzVector &) const;
    Vector2 EtaPhiVector();

// Angle wrt. another vector.
    float Angle(const Vector3 &v) const;

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
    float Dot(const LorentzVector &) const;
    float operator * (const LorentzVector &) const;

// Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)
    void SetVectMag(const Vector3 &spatial, float magnitude);
    void SetVectM(const Vector3 &spatial, float mass);

// Returns t +/- z.
// Related to the positive/negative light-cone component,
// which some define this way and others define as (t +/- z)/sqrt(2)
    float Plus() const;
    float Minus() const;

// Returns the spatial components divided by the time component.
    Vector3 BoostVector() const ;

// Lorentz boost.
    void Boost(float, float, float);
    void Boost(const Vector3 &);

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
    void RotateUz(Vector3 &newUzVector);

};

LorentzVector operator * (float a, const LorentzVector &);

}
