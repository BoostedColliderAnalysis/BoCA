#pragma once

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

    friend Vector2 operator + (const Vector2&, const Vector2&);
    friend Vector2 operator + (const Vector2&, float);
    friend Vector2 operator + (float , const Vector2&);
    friend Vector2 operator - (const Vector2&, const Vector2&);
    friend Vector2 operator - (const Vector2&, float);
    friend float operator * (const Vector2&, const Vector2&);
    friend Vector2 operator * (const Vector2&, float);
    friend Vector2 operator * (float , const Vector2&);
    friend Vector2 operator / (const Vector2&, float);
    friend float operator ^ (const Vector2&, const Vector2&);

// setters
    void Set(const Vector2& v);
    void Set(float x0, float y0);
//     void Set(float x0, float y0);

// other member functions

    float Mod2() const {
        return fX * fX + fY * fY;
    };
    float Mod() const;

    float Px() const {
        return fX;
    };
    float Py() const {
        return fY;
    };
    float X() const {
        return fX;
    };
    float Y() const {
        return fY;
    };

// phi() is defined in [0,TWOPI]

    float Phi() const;
    float DeltaPhi(const Vector2& v) const;
    void SetMagPhi(float mag, float phi);

// unit vector in the direction of *this

    Vector2 Unit() const;
    Vector2 Ort() const;

// projection of *this to the direction
// of Vector2 vector `v'

    Vector2 Proj(const Vector2& v) const;

// component of *this normal to `v'

    Vector2 Norm(const Vector2& v) const;

// rotates 2-vector by phi radians
    Vector2 Rotate(float phi) const;

// returns phi angle in the interval [0,2*PI)
    static float Phi_0_2pi(float x); // returns phi angle in the interval
// returns phi angle in the interval [-PI,PI)
    static float Phi_mpi_pi(float x);

};

