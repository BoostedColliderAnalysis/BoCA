#include "Vector2.hh"
#include <cmath>

namespace analysis
{

float const kPI = M_PI;
float const kTWOPI = 2.*kPI;

Vector2::Vector2()
{
//constructor
    x_ = 0.;
    y_ = 0.;
}

Vector2::Vector2(float *v)
{
//constructor
    x_ = v[0];
    y_ = v[1];
}

Vector2::Vector2(float x0, float y0)
{
//constructor
    x_ = x0;
    y_ = y0;
}

float Vector2::Mod() const
{
// return modulo of this vector
    return std::sqrt(x_ * x_ + y_ * y_);
}

Vector2 Vector2::Unit() const
{
// return module normalized to 1
    return (Mod2()) ? *this / Mod() : Vector2();
}

float Vector2::Phi() const
{
// return vector phi
    return M_PI + std::atan2(-y_, -x_);
}

float Vector2::Phi_0_2pi(float x)
{
// (static function) returns phi angle in the interval [0,2*PI)
    if (std::isnan(x)) {
// gROOT->Error("Vector2::Phi_0_2pi","function called with NaN");
        return x;
    }
    while (x >= kTWOPI) x -= kTWOPI;
    while (x < 0.) x += kTWOPI;
    return x;
}

float Vector2::Phi_mpi_pi(float x)
{
// (static function) returns phi angle in the interval [-PI,PI)
    if (std::isnan(x)) {
// gROOT->Error("Vector2::Phi_mpi_pi","function called with NaN");
        return x;
    }
    while (x >= kPI) x -= kTWOPI;
    while (x < -kPI) x += kTWOPI;
    return x;
}

Vector2 Vector2::Rotate(float phi) const
{
//rotation by phi
    return Vector2(x_ * std::cos(phi) - y_ * std::sin(phi), x_ * std::sin(phi) + y_ * std::cos(phi));
}

void Vector2::SetMagPhi(float mag, float phi)
{
//set vector using mag and phi
    float amag = std::abs(mag);
    x_ = amag * std::cos(phi);
    y_ = amag * std::sin(phi);
}

// unary operators
Vector2 &Vector2::operator += (Vector2 const &v)
{
    x_ += v.x_;
    y_ += v.y_;
    return *this;
}

Vector2 &Vector2::operator -= (Vector2 const &v)
{
    x_ -= v.x_;
    y_ -= v.y_;
    return *this;
}

// scalar product of 2 2-vectors
float Vector2::operator *= (const Vector2 &v)
{
    return (x_ * v.x_ + y_ * v.y_);
}

Vector2 &Vector2::operator *= (float s)
{
    x_ *= s;
    y_ *= s;
    return *this;
}
Vector2 &Vector2::operator /= (float s)
{
    x_ /= s;
    y_ /= s;
    return *this;
}

// binary operators
Vector2 operator + (const Vector2 &v1, const Vector2 &v2)
{
    return Vector2(v1.x_ + v2.x_, v1.y_ + v2.y_);
}

Vector2 operator + (const Vector2 &v1, float bias)
{
    return Vector2(v1.x_ + bias, v1.y_ + bias);
}

Vector2 operator + (float bias, const Vector2 &v1)
{
    return Vector2(v1.x_ + bias, v1.y_ + bias);
}

Vector2 operator - (const Vector2 &v1, const Vector2 &v2)
{
    return Vector2(v1.x_ - v2.x_, v1.y_ - v2.y_);
}

Vector2 operator - (const Vector2 &v1, float bias)
{
    return Vector2(v1.x_ - bias, v1.y_ - bias);
}

Vector2 operator * (const Vector2 &v, float s)
{
    return Vector2(v.x_ * s, v.y_ * s);
}

Vector2 operator * (float s, const Vector2 &v)
{
    return Vector2(v.x_ * s, v.y_ * s);
}

float operator * (const Vector2 &v1, const Vector2 &v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}

Vector2 operator / (const Vector2 &v, float s)
{
    return Vector2(v.x_ / s, v.y_ / s);
}

float operator ^ (const Vector2 &v1, const Vector2 &v2)
{
    return v1.x_ * v2.y_ - v1.y_ * v2.x_;
}

float Vector2::DeltaPhi(const Vector2 &v) const
{
    return Phi_mpi_pi(Phi() - v.Phi());
}

Vector2 Vector2::Ort() const
{
    return Unit();
}

Vector2 Vector2::Proj(const Vector2 &v) const
{
    return v * (((*this) * v) / v.Mod2());
}

Vector2 Vector2::Norm(const Vector2 &v) const
{
    return *this - Proj(v);
}

// setters
void Vector2::Set(const Vector2 &v)
{
    x_ = v.x_;
    y_ = v.y_;
}
void Vector2::Set(float x0, float y0)
{
    x_ = x0 ;
    y_ = y0 ;
}

}
