// @(#)root/physics:$Id$
// Author: Pasha Murat   12/02/99
// Jan Hajer 2015

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once
#include <cmath>
#include <iostream>

namespace boca
{

/**
 * @brief Copy of root::TVector2 in order to get rid of TObject
 *
 */
template<typename Value>
class Vector2
{
public:

    /// constructor
    Vector2() {
        x_ = 0.;
        y_ = 0.;
    }

    /// constructor
    Vector2(Value x0, Value y0) {
        x_ = x0;
        y_ = y0;
    }

    // setters
    void Set(Vector2 const& v) {
        x_ = v.x_;
        y_ = v.y_;
    }

    void Set(Value x0, Value y0) {
        x_ = x0 ;
        y_ = y0 ;
    }

    void SetX(Value x0) {
        x_ = x0;
    }

    void SetY(Value y0) {
        y_ = y0;
    }

    //set vector using mag and phi
    void SetMagPhi(Value mag, Value phi) {
        Value amag = std::abs(mag);
        x_ = amag * std::cos(phi);
        y_ = amag * std::sin(phi);
    }

    /// vector sum
    template<typename Value2>
    Vector2& operator+=(Vector2<Value2> const& v) {
        x_ += v.x_;
        y_ += v.y_;
        return *this;
    }

    /// vector difference
    template<typename Value2>
    Vector2& operator-=(Vector2<Value2> const& v) {
        x_ -= v.x_;
        y_ -= v.y_;
        return *this;
    }

    /// scalar product of 2 2-vectors
    template<typename Value2>
    Value operator*=(Vector2<Value2> const& v) {
        return x_ * v.x_ + y_ * v.y_;
    }

    /// product with scalar
    template<typename Value2>
    Vector2& operator*=(Value2 s) {
        x_ *= s;
        y_ *= s;
        return *this;
    }

    /// division by scalar
    template<typename Value2>
    Vector2& operator/=(Value2 s) {
        x_ /= s;
        y_ /= s;
        return *this;
    }

    /// vector sum
    template<typename Value2>
    friend Vector2<Value> operator+(Vector2<Value> const& v1, Vector2<Value2> const& v2) {
      return {v1.X() + v2.X(), v1.Y() + v2.Y()};
    }

    // template<typename Value2>
    friend Vector2 operator+(Vector2 const& v1, Value bias) {
      return {v1.X() + bias, v1.Y() + bias};
    }

    // template<typename Value2>
    friend Vector2 operator+(Value bias, Vector2 const& v1) {
      return {v1.X() + bias, v1.Y() + bias};
    }

    template<typename Value2>
    friend Vector2 operator-(Vector2 const& v1, Vector2<Value2> const& v2) {
      return {v1.X() - v2.X(), v1.Y() - v2.Y()};
    }

    template<typename Value2>
    friend Vector2 operator-(Vector2 const& v1, Value2 bias) {
      return {v1.X() - bias, v1.Y() - bias};
    }

    template<typename Value2>
    friend Value operator*(Vector2<Value> const& v1, Vector2<Value2> const& v2) {
      return v1.X() * v2.X() + v1.Y() * v2.Y();
    }

    // template<typename Value2>
    friend Vector2 operator*(Value s, Vector2 const& v) {
      return {v.X() * s, v.Y() * s};
    }

    // template<typename Value2>
    friend Vector2 operator*(Vector2 const& v, Value s) {
      return {v.X() * s, v.Y() * s};
    }

    template<typename Value2>
    friend Vector2 operator/(Vector2 const& v, Value2 s) {
      return {v.X() / s, v.Y() / s};
    }

    template<typename Value2>
    friend Value operator^(Vector2 const& v1, Vector2<Value2> const& v2) {
      return v1.X() * v2.Y() - v1.Y() * v2.X();
    }


    Value Mod2() const {
        return x_ * x_ + y_ * y_;
    }

    /// return modulo of this vector
    Value Mod() const {
        return std::sqrt(Mod2());
    }

    Value Px() const {
        return x_;
    }

    Value Py() const {
        return y_;
    }

    Value X() const {
        return x_;
    }

    Value Y() const {
        return y_;
    }

    /// return vector phi defined in [0,TWOPI]
    Value Phi() const {
        return M_PI + std::atan2(-y_, -x_);
    }

    template<typename Value2>
    Value DeltaPhi(Vector2<Value2> const& v) const {
        return Phi_mpi_pi(Phi() - v.Phi());
    }

    /// unit vector in the direction of *this
    /// return module normalized to 1
    Vector2 Unit() const {
        return (Mod2()) ? *this / Mod() : Vector2();
    }

    Vector2 Ort() const {
        return Unit();
    }

    /// projection of *this to the direction of Vector2 vector `v'
    template<typename Value2>
    Vector2 Proj(Vector2<Value2> const& v) const {
        return v * (((*this) * v) / v.Mod2());
    }

// component of *this normal to `v'
    template<typename Value2>
    Vector2 Norm(Vector2<Value2> const& v) const {
        return *this - Proj(v);
    }

// rotates 2-vector by phi radians
    template<typename Value2>
    Vector2 Rotate(Value2 phi) const {
        return {x_* std::cos(phi) - y_* std::sin(phi), x_* std::sin(phi) + y_* std::cos(phi)};
    }

private:

    template<typename>
    friend class Vector2;

    Value x_;

    Value y_;
};

// returns phi angle in the interval [0,2*PI)
template<typename Value>
Value Phi_0_2pi(Value x)
{
    if (std::isnan(x)) {
        std::cout << "function called with NaN" << std::endl;
        return x;
    }
    while (x >= 2 * M_PI) x -= 2 * M_PI;
    while (x < 0.) x += 2 * M_PI;
    return x;
}

// returns phi angle in the interval [-PI,PI)
template<typename Value>
Value Phi_mpi_pi(Value x)
{
    if (std::isnan(x)) {
        std::cout << "function called with NaN" << std::endl;
        return x;
    }
    while (x >= M_PI) x -= 2 * M_PI;
    while (x < -M_PI) x += 2 * M_PI;
    return x;
}

}
