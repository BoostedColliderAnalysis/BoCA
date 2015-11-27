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

template<typename Value, typename Value_2>
using ValueProduct = typename boost::units::multiply_typeof_helper<Value, Value_2>::type;

/**
 * @brief Copy of root::TVector2 in order to get rid of TObject
 *
 */
template<typename Value>
class Vector2
{
public:

    template<typename Value_2>
    using ValueProduct = ValueProduct<Value, Value_2>;

    template<typename Value_2>
    using ValueQuotient = typename boost::units::divide_typeof_helper<Value, Value_2>::type;


    template <typename> struct IsQuantity : std::false_type { };
    template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type { };

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value, Value_2>::value >::type;

    template<typename Value_2>
    using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value_2>::value >::type;

    /// constructor
    Vector2() {
        x_ = 0;
        y_ = 0;
    }

    /// constructor
    Vector2(Value x, Value y) {
        x_ = x;
        y_ = y;
    }

    // setters
    void Set(Vector2 const& vector) {
        x_ = vector.x_;
        y_ = vector.y_;
    }

    void Set(Value x, Value y) {
        x_ = x ;
        y_ = y ;
    }

    void SetX(Value x) {
        x_ = x;
    }

    void SetY(Value y) {
        y_ = y;
    }

    //set vector using mag and phi
    void SetMagPhi(Value magnitude, Angle phi) {
        Value absolute = Abs(magnitude, IsQuantity<Value>());
        x_ = absolute * boost::units::cos(phi);
        y_ = absolute * boost::units::sin(phi);
    }

    /// vector sum
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2& operator+=(Vector2<Value_2> const& vector) {
        x_ += vector.x_;
        y_ += vector.y_;
        return *this;
    }

    /// vector difference
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2& operator-=(Vector2<Value_2> const& vector) {
        x_ -= vector.x_;
        y_ -= vector.y_;
        return *this;
    }

    /// product with scalar
    template < typename Value_2, typename = OnlyIfNotQuantity<Value_2> >
    Vector2& operator*=(Value_2 scalar) {
        x_ *= scalar;
        y_ *= scalar;
        return *this;
    }

    /// division by scalar
    template < typename Value_2, typename = OnlyIfNotQuantity<Value_2> >
    Vector2& operator/=(Value_2 scalar) {
        x_ /= scalar;
        y_ /= scalar;
        return *this;
    }

    /// vector sum
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    friend Vector2<Value> operator+(Vector2 const& vector_1, Vector2<Value_2> const& vector_2) {
        return {vector_1.X() + vector_2.X(), vector_1.Y() + vector_2.Y()};
    }

    /// vector difference
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    friend Vector2 operator-(Vector2 const& vector_1, Vector2<Value_2> const& vector_2) {
        return {vector_1.X() - vector_2.X(), vector_1.Y() - vector_2.Y()};
    }


    template <class Value_2>
    friend Vector2 <ValueQuotient<Value_2>> operator/(Vector2 const& vector, Value_2 const& scalar) {
        return {vector.X() / scalar, vector.Y() / scalar};
    };

    template<typename Value_2>
    friend ValueProduct<Value_2> operator^(Vector2 const& vector_1, Vector2<Value_2> const& vector_2) {
        return vector_1.X() * vector_2.Y() - vector_1.Y() * vector_2.X();
    }

    ValueProduct<Value> Mod2() const {
        return x_ * x_ + y_ * y_;
    }

    /// return modulo of this vector
    Value Mod() const {
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
    Angle Phi() const {
        Phi(IsQuantity<Value>());
    }

    template<typename Value_2>
    Angle DeltaPhi(Vector2<Value_2> const& vector) const {
        return Phi_mpi_pi(Phi() - vector.Phi());
    }

    /// unit vector in the direction of *this
    /// return module normalized to 1
    Vector2 Unit() const {
        return Mod2() ? *this / Mod() : Vector2();
    }

    Vector2 Ort() const {
        return Unit();
    }

    /// projection of *this to the direction of Vector2 vector `v'
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2 Proj(Vector2<Value_2> const& vector) const {
        return vector * (*this * vector / vector.Mod2());
    }

    // component of *this normal to `v'
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2 Norm(Vector2<Value_2> const& vector) const {
        return *this - Proj(vector);
    }

// rotates 2-vector by phi radians
    Vector2 Rotate(Angle phi) const {
        return {x_* boost::units::cos(phi) - y_* boost::units::sin(phi), x_* boost::units::sin(phi) + y_* boost::units::cos(phi)};
    }

private:

    template<typename>
    friend class Vector2;

    Value Mod(std::false_type) const {
        return std::sqrt(Mod2());
    }

    Value Mod(std::true_type) const {
        return boost::units::sqrt(Mod2());
    }

    Angle Phi(std::false_type) const {
        return std::atan2(-y_, -x_) * rad;
    }

    Angle Phi(std::true_type) const {
        return boost::units::atan2(-y_, -x_);
    }

    //set vector using mag and phi
    Value Abs(Value mag, std::false_type) const {
        return std::abs(mag);
    }

    //set vector using mag and phi
    Value Abs(Value mag, std::true_type) const {
        return boost::units::abs(mag);
    }

    Value x_;

    Value y_;
};

template <typename>
struct IsVector2 : std::false_type { };

template <typename Value>
struct IsVector2<Vector2<Value>> : std::true_type { };

template<typename Value>
using OnlyIfNotVector = typename std::enable_if < !IsVector2<Value>::value >::type;

template <class Value, class Value_2>
ValueProduct<Value, Value_2> operator*(Vector2<Value> const& vector_1, const Vector2<Value_2>& vector_2)
{
    return vector_1.X() * vector_2.X() + vector_1.Y() * vector_2.Y();
};

template < class Value, class Value_2, typename = OnlyIfNotVector<Value_2> >
Vector2 <ValueProduct<Value, Value_2>> operator*(Vector2<Value> const& vector, Value_2 const& scalar)
{
    return {vector.X()* scalar, vector.Y()* scalar};
};

template < class Value, class Value_2, typename = OnlyIfNotVector<Value_2> >
Vector2 <ValueProduct<Value, Value_2>> operator*(Value_2 const& scalar, Vector2<Value> const& vector)
{
    return {vector.X()* scalar, vector.Y()* scalar};
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

