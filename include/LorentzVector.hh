#pragma once
#include "Vector3.hh"
// #include <cmath>
// #include <algorithm>

class TLorentzVector;
namespace analysis
{


class LorentzVector
{

private:

    Vector3 p_;  // 3 vector component
    float e_;  // time or energy of (x,y,z,t) or (px,py,pz,e)

public:


    void operator=(const TLorentzVector &lorentzvector);

    typedef float Scalar;   // to be able to use it with the ROOT::Math::VectorUtil functions

    enum { kX = 0, kY = 1, kZ = 2, kT = 3, kNUM_COORDINATES = 4, kSIZE = kNUM_COORDINATES };
    // Safe indexing of the coordinates when using with matrices, arrays, etc.

    LorentzVector();

    LorentzVector(float x, float y, float z, float t);
    // Constructor giving the components x, y, z, t.

    LorentzVector(const float *carray);
//     LorentzVector(const float *carray);
    // Constructor from an array, not checked!

    LorentzVector(const Vector3 &vector3, float t);
    // Constructor giving a 3-Vector and a time component.

//     LorentzVector(const LorentzVector &lorentzvector);
    // Copy constructor.

//     virtual ~LorentzVector();
    // Destructor

    //  operator Vector3 () const;
    //  operator Vector3 & ();
    // Conversion (cast) to Vector3.

    float X() const;
    float Y() const;
    float Z() const;
    float T() const;
    // Get position and time.

    void SetX(float a);
    void SetY(float a);
    void SetZ(float a);
    void SetT(float a);
    // Set position and time.

    float Px() const;
    float Py() const;
    float Pz() const;
    float P()  const;
    float E()  const;
    float Energy() const;
    // Get momentum and energy.

    void SetPx(float a);
    void SetPy(float a);
    void SetPz(float a);
    void SetE(float a);
    // Set momentum and energy.

    Vector3 Vect() const ;
    // Get spatial component.

    void SetVect(const Vector3 &vect3);
    // Set spatial component.

    float Theta() const;
    float CosTheta() const;
    float Phi() const; //returns phi from -pi to pi
    float Rho() const;
    // Get spatial vector components in spherical coordinate system.

    void SetTheta(float theta);
    void SetPhi(float phi);
    void SetRho(float rho);
    // Set spatial vector components in spherical coordinate system.

    void SetPxPyPzE(float px, float py, float pz, float e);
    void SetXYZT(float  x, float  y, float  z, float t);
    void SetXYZM(float  x, float  y, float  z, float m);
    void SetPtEtaPhiM(float pt, float eta, float phi, float m);
    void SetPtEtaPhiE(float pt, float eta, float phi, float e);
    // Setters to provide the functionality (but a more meanigful name) of
    // the previous version eg SetV4... PsetV4...

    void GetXYZT(float *carray) const;
//      void GetXYZT(float *carray) const;
    // Getters into an arry
    // no checking!

    float operator()(int i) const;
    float operator [](int i) const;
    // Get components by index.

    float &operator()(int i);
    float &operator [](int i);
    // Set components by index.

    LorentzVector &operator = (const LorentzVector &);
    // Assignment.

    LorentzVector   operator + (const LorentzVector &) const;
    LorentzVector &operator += (const LorentzVector &);
    // Additions.

    LorentzVector   operator - (const LorentzVector &) const;
    LorentzVector &operator -= (const LorentzVector &);
    // Subtractions.

    LorentzVector operator - () const;
    // Unary minus.

    LorentzVector operator * (float a) const;
    LorentzVector &operator *= (float a);
    // Scaling with real numbers.

    bool operator == (const LorentzVector &) const;
    bool operator != (const LorentzVector &) const;
    // Comparisons.

    float Perp2() const;
    // Transverse component of the spatial vector squared.

    float Pt() const;
    float Perp() const;
    // Transverse component of the spatial vector (R in cylindrical system).

    void SetPerp(float);
    // Set the transverse component of the spatial vector.

    float Perp2(const Vector3 &v) const;
    // Transverse component of the spatial vector w.r.t. given axis squared.

    float Pt(const Vector3 &v) const;
    float Perp(const Vector3 &v) const;
    // Transverse component of the spatial vector w.r.t. given axis.

    float Et2() const;
    // Transverse energy squared.

    float Et() const;
    // Transverse energy.

    float Et2(const Vector3 &) const;
    // Transverse energy w.r.t. given axis squared.

    float Et(const Vector3 &) const;
    // Transverse energy w.r.t. given axis.

    float DeltaPhi(const LorentzVector &) const;
    float DeltaR(const LorentzVector &) const;
    float DrEtaPhi(const LorentzVector &) const;
    Vector2 EtaPhiVector();

    float Angle(const Vector3 &v) const;
    // Angle wrt. another vector.

    float Mag2() const;
    float M2() const;
    // Invariant mass squared.

    float Mag() const;
    float M() const;
    // Invariant mass. If mag2() is negative then -sqrt(-mag2()) is returned.

    float Mt2() const;
    // Transverse mass squared.

    float Mt() const;
    // Transverse mass.

    float Beta() const;
    float Gamma() const;

    float Dot(const LorentzVector &) const;
    float operator * (const LorentzVector &) const;
    // Scalar product.

    void SetVectMag(const Vector3 &spatial, float magnitude);
    void SetVectM(const Vector3 &spatial, float mass);
    // Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)

    float Plus() const;
    float Minus() const;
    // Returns t +/- z.
    // Related to the positive/negative light-cone component,
    // which some define this way and others define as (t +/- z)/sqrt(2)

    Vector3 BoostVector() const ;
    // Returns the spatial components divided by the time component.

    void Boost(float, float, float);
    void Boost(const Vector3 &);
    // Lorentz boost.

    float Rapidity() const;
    // Returns the rapidity, i.e. 0.5*ln((E+pz)/(E-pz))

    float Eta() const;
    float PseudoRapidity() const;
    // Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))

    void RotateX(float angle);
    // Rotate the spatial component around the x-axis.

    void RotateY(float angle);
    // Rotate the spatial component around the y-axis.

    void RotateZ(float angle);
    // Rotate the spatial component around the z-axis.

    void RotateUz(Vector3 &newUzVector);
    // Rotates the reference frame from Uz to newUz (unit vector).

//      void Rotate(float, const Vector3 &);
    // Rotate the spatial component around specified axis.

//      LorentzVector &operator *= (const TRotation &);
//      LorentzVector &Transform(const TRotation &);
    // Transformation with HepRotation.

//     LorentzVector &operator *= (const TLorentzRotation &);
//     LorentzVector &Transform(const TLorentzRotation &);
    // Transformation with HepLorenzRotation.

//     virtual void        Print(Option_t *option = "") const;

};


// LorentzVector operator * (const LorentzVector &, float a);
// moved to LorentzVector::operator * (float a)
LorentzVector operator * (float a, const LorentzVector &);
// Scaling LorentzVector with a real number



}

