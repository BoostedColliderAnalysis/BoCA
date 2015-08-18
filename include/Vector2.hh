// @(#)root/physics:$Id$
// Author: Pasha Murat   12/02/99
// Jan Hajer 2015

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

namespace analysis
{

/**
 * @brief Copy of root::TVector2 in order to get rid of TObject
 *
 */
class Vector2
{

// data members
protected:

    float fX; // components of the vector
    float fY;

// function members
public:

    Vector2();
    Vector2(float* s);
    Vector2(float x0, float y0);
// unary operators
    Vector2& operator += (Vector2 const& v);
    Vector2& operator -= (Vector2 const& v);
    float operator *= (Vector2 const& v);
    Vector2& operator *= (float s);
    Vector2& operator /= (float s);

// binary operators

    friend Vector2 operator + (Vector2 const&, Vector2 const&);
    friend Vector2 operator + (Vector2 const&, float);
    friend Vector2 operator + (float , Vector2 const&);
    friend Vector2 operator - (Vector2 const&, Vector2 const&);
    friend Vector2 operator - (Vector2 const&, float);
    friend float operator * (Vector2 const&, Vector2 const&);
    friend Vector2 operator * (Vector2 const&, float);
    friend Vector2 operator * (float , Vector2 const&);
    friend Vector2 operator / (Vector2 const&, float);
    friend float operator ^ (Vector2 const&, Vector2 const&);

// setters
    void Set(Vector2 const& v);
    void Set(float x0, float y0);
//     void Set(float x0, float y0);

// other member functions

    float Mod2() const;
    float Mod() const;

    float Px() const;
    float Py() const;
    float X() const;
    float Y() const;

// phi() is defined in [0,TWOPI]

    float Phi() const;
    float DeltaPhi(Vector2 const& v) const;
    void SetMagPhi(float mag, float phi);

// unit vector in the direction of *this

    Vector2 Unit() const;
    Vector2 Ort() const;

// projection of *this to the direction
// of Vector2 vector `v'

    Vector2 Proj(Vector2 const& v) const;

// component of *this normal to `v'

    Vector2 Norm(Vector2 const& v) const;

// rotates 2-vector by phi radians
    Vector2 Rotate(float phi) const;

// returns phi angle in the interval [0,2*PI)
    static float Phi_0_2pi(float x); // returns phi angle in the interval
// returns phi angle in the interval [-PI,PI)
    static float Phi_mpi_pi(float x);

};

}
