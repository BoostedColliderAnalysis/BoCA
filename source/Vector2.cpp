#include "Vector2.hh"
#include <cmath>
#include "Debug.hh"

Vector2::Vector2()
{
//constructor
    fX = 0.;
    fY = 0.;
}

Vector2::Vector2(float* v)
{
//constructor
    fX = v[0];
    fY = v[1];
}

Vector2::Vector2(float x0, float y0)
{
//constructor
    fX = x0;
    fY = y0;
}

float Vector2::Mod() const
{
// return modulo of this vector
    return std::sqrt(fX * fX + fY * fY);
}

Vector2 Vector2::Unit() const
{
// return module normalized to 1
    return (Mod2()) ? *this / Mod() : Vector2();
}

float Vector2::Phi() const
{
// return vector phi
    return M_PI + std::atan2(-fY, -fX);
}

float Vector2::Phi_0_2pi(float x)
{
// (static function) returns phi angle in the interval [0,2*PI)
    if (std::isnan(x)) {
        Error("function called with NaN");
        return x;
    }
    while (x >= 2 * M_PI) x -= 2 * M_PI;
    while (x < 0.) x += 2 * M_PI;
    return x;
}

float Vector2::Phi_mpi_pi(float x)
{
// (static function) returns phi angle in the interval [-PI,PI)
    if (std::isnan(x)) {
        Error("function called with NaN");
        return x;
    }
    while (x >= M_PI) x -= 2 * M_PI;
    while (x < -M_PI) x += 2 * M_PI;
    return x;
}

Vector2 Vector2::Rotate(float phi) const
{
//rotation by phi
    return Vector2(fX * std::cos(phi) - fY * std::sin(phi), fX * std::sin(phi) + fY * std::cos(phi));
}

void Vector2::SetMagPhi(float mag, float phi)
{
//set vector using mag and phi
    float amag = std::abs(mag);
    fX = amag * std::cos(phi);
    fY = amag * std::sin(phi);
}

// unary operators
Vector2& Vector2::operator += (Vector2 const& v)
{
    fX += v.fX;
    fY += v.fY;
    return *this;
}
Vector2& Vector2::operator -= (Vector2 const& v)
{
    fX -= v.fX;
    fY -= v.fY;
    return *this;
}

// scalar product of 2 2-vectors

float Vector2::operator *= (const Vector2& v)
{
    return (fX * v.fX + fY * v.fY);
}

Vector2& Vector2::operator *= (float s)
{
    fX *= s;
    fY *= s;
    return *this;
}
Vector2& Vector2::operator /= (float s)
{
    fX /= s;
    fY /= s;
    return *this;
}

// binary operators

Vector2 operator + (const Vector2& v1, const Vector2& v2)
{
    return Vector2(v1.fX + v2.fX, v1.fY + v2.fY);
}

Vector2 operator + (const Vector2& v1, float bias)
{
    return Vector2(v1.fX + bias, v1.fY + bias);
}

Vector2 operator + (float bias, const Vector2& v1)
{
    return Vector2(v1.fX + bias, v1.fY + bias);
}

Vector2 operator - (const Vector2& v1, const Vector2& v2)
{
    return Vector2(v1.fX - v2.fX, v1.fY - v2.fY);
}

Vector2 operator - (const Vector2& v1, float bias)
{
    return Vector2(v1.fX - bias, v1.fY - bias);
}

Vector2 operator * (const Vector2& v, float s)
{
    return Vector2(v.fX * s, v.fY * s);
}

Vector2 operator * (float s, const Vector2& v)
{
    return Vector2(v.fX * s, v.fY * s);
}

float operator * (const Vector2& v1, const Vector2& v2)
{
    return v1.fX * v2.fX + v1.fY * v2.fY;
}

Vector2 operator / (const Vector2& v, float s)
{
    return Vector2(v.fX / s, v.fY / s);
}

float operator ^ (const Vector2& v1, const Vector2& v2)
{
    return v1.fX * v2.fY - v1.fY * v2.fX;
}

float Vector2::DeltaPhi(const Vector2& v) const
{
    return Phi_mpi_pi(Phi() - v.Phi());
}

Vector2 Vector2::Ort() const
{
    return Unit();
}

Vector2 Vector2::Proj(const Vector2& v) const
{
    return v * (((*this) * v) / v.Mod2());
}

Vector2 Vector2::Norm(const Vector2& v) const
{
    return *this - Proj(v);
}

// setters

void Vector2::Set(const Vector2& v)
{
    fX = v.fX;
    fY = v.fY;
}
void Vector2::Set(float x0, float y0)
{
    fX = x0 ;
    fY = y0 ;
}
// void Vector2::Set(float x0, float y0)
// {
//     fX = x0 ;
//     fY = y0 ;
// }
