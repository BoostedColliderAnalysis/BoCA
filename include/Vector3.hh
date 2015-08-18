// @(#)root/physics:$Id$
// Author: Pasha Murat, Peter Malzacher   12/02/99
// Jan Hajer 2015

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/
#pragma once

typedef float Float_t;
class TVector3;
template<class Element> class TMatrixT;
typedef TMatrixT<Float_t> TMatrix;

namespace boca {

/**
 * @brief Copy of root::TVector3 in order to get rid of TObject
 *
 */
class Vector3 {

public:

    void operator=(TVector3 const& vector);

    Vector3();

// The constructor.
    Vector3(float x, float y, float z);

// Constructors from an array
    Vector3(float const*);

// Get components by index (Geant4).
    float operator()(int) const;
    float operator [](int) const;

// Set components by index.
    float& operator()(int);
    float& operator [](int);

// The components in cartesian coordinate system.
    float x() const;
    float y() const;
    float z() const;
    float X() const;
    float Y() const;
    float Z() const;
    float Px() const;
    float Py() const;
    float Pz() const;

    void SetX(float);
    void SetY(float);
    void SetZ(float);
    void SetXYZ(float x, float y, float z);
    void SetPtEtaPhi(float pt, float eta, float phi);
    void SetPtThetaPhi(float pt, float theta, float phi);

// Get the components into an array
// not checked!
    void GetXYZ(float* carray) const;

// The azimuth angle. returns phi from -pi to pi
    float Phi() const;

// The polar angle.
    float Theta() const;

// Cosine of the polar angle.
    float CosTheta() const;

// The magnitude squared (rho^2 in spherical coordinate system).
    float Mag2() const;

// The magnitude (rho in spherical coordinate system).
    float Mag() const;

// Set phi keeping mag and theta constant (BaBar).
    void SetPhi(float);

// Set theta keeping mag and phi constant (BaBar).
    void SetTheta(float);

// Set magnitude keeping theta and phi constant (BaBar).
    void SetMag(float);

// The transverse component squared (R^2 in cylindrical coordinate system).
    float Perp2() const;

// The transverse component (R in cylindrical coordinate system).
    float Pt() const;
    float Perp() const;

// Set the transverse component keeping phi and z constant.
    void SetPerp(float);

// The transverse component w.r.t. given axis squared.
    float Perp2(Vector3 const&) const;

// The transverse component w.r.t. given axis.
    float Pt(Vector3 const&) const;
    float Perp(Vector3 const&) const;

    float DeltaPhi(Vector3 const&) const;
    float DeltaR(Vector3 const&) const;
    float DrEtaPhi(Vector3 const&) const;
//     Vector2 EtaPhiVector() const;
    void SetMagThetaPhi(float mag, float theta, float phi);

// Comparisons (Geant4).
    bool operator == (Vector3 const&) const;
    bool operator != (Vector3 const&) const;

// Addition.
    Vector3& operator += (Vector3 const&);

// Subtraction.
    Vector3& operator -= (Vector3 const&);

// Unary minus.
    Vector3 operator - () const;

// Scaling with real numbers.
    Vector3& operator *= (float);

// Unit vector parallel to this.
    Vector3 Unit() const;

// Vector orthogonal to this (Geant4).
    Vector3 Orthogonal() const;

// Scalar product.
    float Dot(Vector3 const&) const;

// Cross product.
    Vector3 Cross(Vector3 const&) const;

// The angle w.r.t. another 3-vector.
    float Angle(Vector3 const&) const;

// Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))
    float PseudoRapidity() const;

    float Eta() const;

// Rotates the Hep3Vector around the x-axis.
    void RotateX(float);

// Rotates the Hep3Vector around the y-axis.
    void RotateY(float);

// Rotates the Hep3Vector around the z-axis.
    void RotateZ(float);

// Rotates reference frame from Uz to newUz (unit vector) (Geant4).
    void RotateUz(Vector3 const&);

//     Vector2 XYvector() const;

private:

// The components.
    float x_, y_, z_;

};

// Addition of 3-vectors.
Vector3 operator + (Vector3 const&, Vector3 const&);

// Subtraction of 3-vectors.
Vector3 operator - (Vector3 const&, Vector3 const&);

// Scalar product of 3-vectors.
float operator * (Vector3 const&, Vector3 const&);

// Scaling of 3-vectors with a real number
Vector3 operator * (Vector3 const&, float a);
Vector3 operator * (float a, Vector3 const&);

Vector3 operator * (TMatrix const&, Vector3 const&);

}

