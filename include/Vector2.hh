#pragma once

namespace analysis{

class Vector2
{
//------------------------------------------------------------------------------
//  data members
//------------------------------------------------------------------------------
protected:

    float    x_;    // components of the vector
    float    y_;
//------------------------------------------------------------------------------
//  function members
//------------------------------------------------------------------------------
public:

    typedef float Scalar;   // to be able to use it with the ROOT::Math::VectorUtil functions

    Vector2();
    Vector2(float *s);
    Vector2(float x0, float y0);
//     virtual ~Vector2();
    // ****** unary operators

    Vector2       &operator  = (Vector2 const &v);
    Vector2       &operator += (Vector2 const &v);
    Vector2       &operator -= (Vector2 const &v);
    float        operator *= (Vector2 const &v);
    Vector2       &operator *= (float s);
    Vector2       &operator /= (float s);

    // ****** binary operators

    friend Vector2       operator + (const Vector2 &, const Vector2 &);
    friend Vector2       operator + (const Vector2 &, float);
    friend Vector2       operator + (float  , const Vector2 &);
    friend Vector2       operator - (const Vector2 &, const Vector2 &);
    friend Vector2       operator - (const Vector2 &, float);
    friend float       operator * (const Vector2 &, const Vector2 &);
    friend Vector2       operator * (const Vector2 &, float);
    friend Vector2       operator * (float  , const Vector2 &);
    friend Vector2       operator / (const Vector2 &, float);
    friend float       operator ^ (const Vector2 &, const Vector2 &);

    // ****** setters
    void Set(const Vector2 &v);
    void Set(float x0, float y0);
//     void Set(float  x0, float  y0);

    // ****** other member functions

    float Mod2() const {
        return x_ * x_ + y_ * y_;
    };
    float Mod() const;

    float Px()   const {
        return x_;
    };
    float Py()   const {
        return y_;
    };
    float X()   const {
        return x_;
    };
    float Y()   const {
        return y_;
    };

    // phi() is defined in [0,TWOPI]

    float Phi() const;
    float DeltaPhi(const Vector2 &v) const;
    void     SetMagPhi(float mag, float phi);

    // unit vector in the direction of *this

    Vector2 Unit() const;
    Vector2 Ort() const;

    // projection of *this to the direction
    // of Vector2 vector `v'

    Vector2 Proj(const Vector2 &v) const;

    // component of *this normal to `v'

    Vector2 Norm(const Vector2 &v) const;

    // rotates 2-vector by phi radians
    Vector2 Rotate(float phi) const;

    // returns phi angle in the interval [0,2*PI)
    static float Phi_0_2pi(float x);                                                                               // returns phi angle in the interval
    // returns phi angle in the interval [-PI,PI)
    static float Phi_mpi_pi(float x);


//     void Print(Option_t *option = "") const;


};

// ****** unary operators

inline Vector2 &Vector2::operator  = (Vector2 const &v)
{
    x_  = v.x_;
    y_  = v.y_;
    return *this;
}
inline Vector2 &Vector2::operator += (Vector2 const &v)
{
    x_ += v.x_;
    y_ += v.y_;
    return *this;
}
inline Vector2 &Vector2::operator -= (Vector2 const &v)
{
    x_ -= v.x_;
    y_ -= v.y_;
    return *this;
}

// scalar product of 2 2-vectors

inline float   Vector2::operator *= (const Vector2 &v)
{
    return (x_ * v.x_ + y_ * v.y_);
}

inline Vector2 &Vector2::operator *= (float s)
{
    x_ *= s;
    y_ *= s;
    return *this;
}
inline Vector2 &Vector2::operator /= (float s)
{
    x_ /= s;
    y_ /= s;
    return *this;
}

// ****** binary operators

inline Vector2  operator + (const Vector2 &v1, const Vector2 &v2)
{
    return Vector2(v1.x_ + v2.x_, v1.y_ + v2.y_);
}

inline Vector2  operator + (const Vector2 &v1, float bias)
{
    return Vector2(v1.x_ + bias, v1.y_ + bias);
}

inline Vector2  operator + (float bias, const Vector2 &v1)
{
    return Vector2(v1.x_ + bias, v1.y_ + bias);
}

inline Vector2  operator - (const Vector2 &v1, const Vector2 &v2)
{
    return Vector2(v1.x_ - v2.x_, v1.y_ - v2.y_);
}

inline Vector2  operator - (const Vector2 &v1, float bias)
{
    return Vector2(v1.x_ - bias, v1.y_ - bias);
}

inline Vector2  operator * (const Vector2 &v, float s)
{
    return Vector2(v.x_ * s, v.y_ * s);
}

inline Vector2    operator * (float s, const Vector2 &v)
{
    return Vector2(v.x_ * s, v.y_ * s);
}

inline float operator * (const Vector2 &v1, const Vector2 &v2)
{
    return  v1.x_ * v2.x_ + v1.y_ * v2.y_;
}

inline Vector2     operator / (const Vector2 &v, float s)
{
    return Vector2(v.x_ / s, v.y_ / s);
}

inline float   operator ^ (const Vector2 &v1, const Vector2 &v2)
{
    return  v1.x_ * v2.y_ - v1.y_ * v2.x_;
}

inline  float Vector2::DeltaPhi(const Vector2 &v) const
{
    return Phi_mpi_pi(Phi() - v.Phi());
}

inline  Vector2 Vector2::Ort() const
{
    return Unit();
}

inline  Vector2 Vector2::Proj(const Vector2 &v) const
{
    return v * (((*this) * v) / v.Mod2());
}

inline  Vector2 Vector2::Norm(const Vector2 &v) const
{
    return *this - Proj(v);
}

// ****** setters

inline void Vector2::Set(const Vector2 &v)
{
    x_ = v.x_;
    y_ = v.y_;
}
inline void Vector2::Set(float x0, float y0)
{
    x_ = x0  ;
    y_ = y0 ;
}
// inline void Vector2::Set(float  x0, float  y0)
// {
//     x_ = x0  ;
//     y_ = y0 ;
// }

}
