// @(#)root/physics:$Id$
// Author: Pasha Murat   12/02/99
// Jan Hajer 2015 remove some stuff, make the class templated and compatible with boost units

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once
#include <type_traits>
// #include <cmath>
#include <boost/units/cmath.hpp>
#include <iostream>
#include "Units.hh"

namespace boca
{

template<typename Value, typename Value2>
using ValueProduct = typename boost::units::multiply_typeof_helper<Value, Value2>::type;

/**
 * @brief Copy of root::TVector2 in order to get rid of TObject
 *
 */
template<typename Value>
class Vector2
{
public:

    template<typename Value2>
    using ValueProduct = ValueProduct<Value, Value2>;

    template<typename Value2>
    using ValueQuotient = typename boost::units::divide_typeof_helper<Value, Value2>::type;


    template <typename> struct IsQuantity : std::false_type { };
    template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type { };

    template<typename Value2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value2>::value || std::is_same<Value, Value2>::value >::type;

    template<typename Value2>
    using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value2>::value >::type;

    /// constructor
    Vector2() {
        x_ = 0;
        y_ = 0;
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
    void SetMagPhi(Value mag, Angle phi) {
        Value amag = Abs(mag, IsQuantity<Value>());
        x_ = amag * boost::units::cos(phi);
        y_ = amag * boost::units::sin(phi);
    }

    /// vector sum
    template <typename Value2, typename = OnlyIfNotOrSameQuantity<Value2>>
    Vector2& operator+=(Vector2<Value2> const& v) {
        x_ += v.x_;
        y_ += v.y_;
        return *this;
    }

    /// vector difference
    template <typename Value2, typename = OnlyIfNotOrSameQuantity<Value2>>
    Vector2& operator-=(Vector2<Value2> const& v) {
        x_ -= v.x_;
        y_ -= v.y_;
        return *this;
    }

    /// product with scalar
    template < typename Value2, typename = OnlyIfNotQuantity<Value2> >
    Vector2& operator*=(Value2 s) {
        x_ *= s;
        y_ *= s;
        return *this;
    }

    /// division by scalar
    template < typename Value2, typename = OnlyIfNotQuantity<Value2> >
    Vector2& operator/=(Value2 s) {
        x_ /= s;
        y_ /= s;
        return *this;
    }

    /// vector sum
    template <typename Value2, typename = OnlyIfNotOrSameQuantity<Value2>>
    friend Vector2<Value> operator+(Vector2 const& v1, Vector2<Value2> const& v2) {
        return {v1.X() + v2.X(), v1.Y() + v2.Y()};
    }

    /// vector difference
    template <typename Value2, typename = OnlyIfNotOrSameQuantity<Value2>>
    friend Vector2 operator-(Vector2 const& v1, Vector2<Value2> const& v2) {
        return {v1.X() - v2.X(), v1.Y() - v2.Y()};
    }


    template <class U>
    friend Vector2 <ValueQuotient<U>> operator/(const Vector2& v, const U& s) {
        return {v.X() / s, v.Y() / s};
    };

    template<typename Value2>
    friend ValueProduct<Value2> operator^(Vector2 const& v1, Vector2<Value2> const& v2) {
        return v1.X() * v2.Y() - v1.Y() * v2.X();
    }

    ValueProduct<Value> Mod2() const {
        return x_ * x_ + y_ * y_;
    }

    /// return modulo of this vector
    Value Mod() {
        Mod(IsQuantity<Value>());
    }

    Value X() const {
        return x_;
    }

    Value Y() const {
        return y_;
    }

//     /// return vector phi defined in [0,TWOPI]
//     Angle Phi() const {
//         return M_PI + std::atan2(-y_, -x_);
//     }

/// return vector phi defined in [-pi, pi]
    Angle Phi() {
        Phi(IsQuantity<Value>());
    }

    template<typename Value2>
    Angle DeltaPhi(Vector2<Value2> const& v) const {
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
    template <typename Value2, typename = OnlyIfNotOrSameQuantity<Value2>>
    Vector2 Proj(Vector2<Value2> const& v) const {
        return v * (((*this) * v) / v.Mod2());
    }

    // component of *this normal to `v'
    template <typename Value2, typename = OnlyIfNotOrSameQuantity<Value2>>
    Vector2 Norm(Vector2<Value2> const& v) const {
        return *this - Proj(v);
    }

// rotates 2-vector by phi radians
    Vector2 Rotate(Angle phi) const {
        return {x_* boost::units::cos(phi) - y_* boost::units::sin(phi), x_* boost::units::sin(phi) + y_* boost::units::cos(phi)};
    }

private:

    template<typename>
    friend class Vector2;

    Value Mod(std::false_type) {
        return std::sqrt(Mod2());
    }

    Value Mod(std::true_type) {
        return boost::units::sqrt(Mod2());
    }

    Angle Phi(std::false_type) const {
        return std::atan2(-y_, -x_) * rad;
    }

    Angle Phi(std::true_type) const {
        return boost::units::atan2(-y_, -x_);
    }

    //set vector using mag and phi
    Value Abs(Value mag, std::false_type) {
        return std::abs(mag);
    }

    //set vector using mag and phi
    Value Abs(Value mag, std::true_type) {
        return boost::units::abs(mag);
    }

    Value x_;

    Value y_;
};

template <typename> struct IsVector2 : std::false_type { };
template <typename T> struct IsVector2<Vector2<T>> : std::true_type { };
template<typename Value2>
using OnlyIfNotVector = typename std::enable_if < !IsVector2<Value2>::value >::type;

template <class T, class U>
ValueProduct<T, U> operator*(const Vector2<T>& v1, const Vector2<U>& v2)
{
    return v1.X() * v2.X() + v1.Y() * v2.Y();
};

template < class T, class U, typename = OnlyIfNotVector<U> >
Vector2 <ValueProduct<T, U>> operator*(const Vector2<T>& v, const U& s)
{
    return {v.X()* s, v.Y()* s};
};

template < class T, class U, typename = OnlyIfNotVector<U> >
Vector2 <ValueProduct<T, U>> operator*(const U& s, const Vector2<T>& v)
{
    return {v.X()* s, v.Y()* s};
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

