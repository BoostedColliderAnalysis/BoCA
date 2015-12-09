// @(#)root/physics:$Id$
// Author: Pasha Murat, Peter Malzacher   12/02/99
// Jan Hajer 2015

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

#include <iostream>

// class TVector3;
// #include "TVector3.h"
// #include "TRotation.h"

#include "TVector3.h"
#include "physics/Vector2.hh"

namespace boca
{

/**
 * @brief Copy of root::TVector3 in order to get rid of TObject
 *
 */
template<class Value>
class Vector3
{

public:

    template<typename Value_2>
    using ValueProduct = ValueProduct<Value, Value_2>;
    using ValueSquared = ValueProduct<Value>;

    template<typename Value_2, typename Value_3>
    using ValueCubed = boca::ValueProduct<ValueProduct<Value_2>, Value_3>;

    template<typename Value_2>
    using ValueQuotient = typename boost::units::divide_typeof_helper<Value, Value_2>::type;

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value, Value_2>::value >::type;

    // Constructor
    Vector3() : x_(Value(0)), y_(Value(0)), z_(Value(0)) {}

    // Constructor
    Vector3(Value x, Value y, Value z) : x_(x), y_(y), z_(z) {};

    // Constructor
    Vector3(TVector3 const& vector) {
//         std::cout << "must be double" << std::endl;
//         std::cout << "vector not initiliazed" << std::endl;
        x_ = vector.X();
        y_ = vector.Y();
        z_ = vector.Z();
    }
    void SetX(Value x) {
        x_ = x;
    }
    void SetY(Value y) {
        y_ = y;
    }
    void SetZ(Value z) {
        z_ = z;
    }
    void SetXYZ(Value x, Value y, Value z) {
        x_ = x;
        y_ = y;
        z_ = z;
    }
    void SetPtEtaPhi(Value pt, boca::Angle eta, boca::Angle phi) {
        //set Pt, Eta and Phi
        Value apt = abs(pt);
        SetXYZ(apt * boost::units::cos(phi), apt * boost::units::sin(phi), apt / boost::units::tan(2.0 * boost::units::atan(units::exp(-eta))));
    }

    void SetPtThetaPhi(Value pt, boca::Angle theta, boca::Angle phi) {
        //set Pt, Theta and Phi
        x_ = pt * boost::units::cos(phi);
        y_ = pt * boost::units::sin(phi);
        double tanTheta = boost::units::tan(theta);
        z_ = tanTheta ? pt / tanTheta : 0;
    }

    // Set phi keeping mag and theta constant(BaBar).
    void SetPhi(boca::Angle phi) {
        // Set phi keeping mag and theta constant(BaBar).
        Value perp = Perp();
        SetX(perp * boost::units::cos(phi));
        SetY(perp * boost::units::sin(phi));
    }

    // Set theta keeping mag and phi constant(BaBar).
    void SetTheta(boca::Angle theta) {
        // Set theta keeping mag and phi constant(BaBar).
        Value magnitude = Mag();
        boca::Angle phi = Phi();
        SetX(magnitude * boost::units::sin(theta) * boost::units::cos(phi));
        SetY(magnitude * boost::units::sin(theta) * boost::units::sin(phi));
        SetZ(magnitude * boost::units::cos(theta));
    }

    // Set magnitude keeping theta and phi constant(BaBar).
    void SetMag(Value magnitude) {
        Value old = Mag();
        if (old == 0) {
            // Warning("SetMag","zero vector can't be stretched");
        } else {
            double factor = magnitude / old;
            SetX(x_ * factor);
            SetY(y_ * factor);
            SetZ(z_ * factor);
        }
    }

    void SetMagThetaPhi(Value mag, boca::Angle theta, boca::Angle phi) {
        //setter with mag, theta, phi
        Value amag = abs(mag);
        x_ = amag * boost::units::sin(theta) * boost::units::cos(phi);
        y_ = amag * boost::units::sin(theta) * boost::units::sin(phi);
        z_ = amag * boost::units::cos(theta);
    }

    // Set the transverse component keeping phi and z constant.
    void SetPerp(Value perp) {
        Value old = Perp();
        if (old != 0) {
            x_ *= perp / old;
            y_ *= perp / old;
        }
    }

    // The components in cartesian coordinate system.
    Value const& X() const {
        return x_;
    }

    Value const& Y() const {
        return y_;
    }

    Value const& Z() const {
        return z_;
    }

    Value & X() {
      return x_;
    }

    Value & Y() {
      return y_;
    }

    Value & Z() {
      return z_;
    }

// The azimuth angle. returns phi from -pi to pi
    boca::Angle Phi() const {
        return x_ == 0 && y_ == 0 ? 0_rad : atan2(y_, x_);
    }

// The polar angle.
    boca::Angle Theta() const {
        return x_ == 0 && y_ == 0 && z_ == 0 ? 0_rad : atan2(Perp(), z_);
    }

// Cosine of the polar angle.
    double CosTheta() const {
        Value ptot = Mag();
        return ptot == 0 ? 1 : z_ / ptot;
    }

// The magnitude squared(rho^2 in spherical coordinate system).
    ValueSquared Mag2() const {
        return sqr(x_) + sqr(y_) + sqr(z_);
    }

// The magnitude(rho in spherical coordinate system).
    Value Mag() const {
        // return the magnitude(rho in spherical coordinate system)
        return sqrt(Mag2());
    }

// The transverse component squared(R^2 in cylindrical coordinate system).
    ValueSquared Perp2() const {
        return sqr(x_) + sqr(y_);
    }

// The transverse component(R in cylindrical coordinate system).
    Value Perp() const {
        //return the transverse component(R in cylindrical coordinate system)
        return sqrt(Perp2());
    }

    // The transverse component w.r.t. given axis squared.
    template <typename Value_2>
    ValueSquared Perp2(Vector3<Value_2> const& vector) const {
        auto other_mag2 = vector.Mag2();
        auto mixing = Dot(vector);
        ValueSquared this_mag_2 = Mag2();
        if (other_mag2 >  boca::ValueProduct<Value_2, Value_2>(0)) this_mag_2 -= sqr(mixing) / other_mag2;
        if (this_mag_2 < ValueSquared(0)) this_mag_2 = ValueSquared(0);
        return this_mag_2;
    }

    // The transverse component w.r.t. given axis.
    template <typename Value_2>
    Value Perp(Vector3<Value_2> const& vector) const {
        //return the transverse component(R in cylindrical coordinate system)
        return sqrt(Perp2(vector));
    }

    template <typename Value_2>
    boca::Angle DeltaPhi(Vector3<Value_2> const& vector) const {
        return RestrictPhi(Phi() - vector.Phi());
    }

    template <typename Value_2>
    boca::Angle DeltaR(Vector3<Value_2> const& vector) const {
        //return deltaR with respect to v
        boca::Angle deta = Eta() - vector.Eta();
        boca::Angle dphi = RestrictPhi(Phi() - vector.Phi());
        return sqrt(sqr(deta) + sqr(dphi));
    }

    boca::Angle DrEtaPhi(Vector3 const& vector) const {
        return DeltaR(vector);
    }

// Unit vector parallel to this.
    Vector3 Unit() const {
        // return unit vector parallel to this.
        ValueSquared tot2 = Mag2();
        double tot = tot2 > ValueSquared(0) ? 1. / GetValue(sqrt(tot2)) : 1.;
        return Vector3(x_ * tot, y_ * tot, z_ * tot);
    }

// Vector orthogonal to this(Geant4).
    Vector3 Orthogonal() const {
        Value x = x_ < Value(0) ? -x_ : x_;
        Value y = y_ < Value(0) ? -y_ : y_;
        Value z = z_ < Value(0) ? -z_ : z_;
        if (x < y) return x < z ? Vector3(Value(0), z_, -y_) : Vector3(y_, -x_, Value(0));
        else return y < z ? Vector3(-z_, Value(0), x_) : Vector3(y_, -x_, Value(0));
    }

// The angle w.r.t. another 3-vector.
    boca::Angle Angle(Vector3 const& vector) const {
        // return the angle w.r.t. another 3-vector
        Value ptot2 = Mag2() * vector.Mag2();
        if (ptot2 <= 0) return 0_rad;
        else {
            Value arg = Dot(vector) / std::sqrt(ptot2);
            if (arg > 1) arg = 1;
            if (arg < -1) arg = -1;
            return acos(arg);
        }
    }

// Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))
    boca::Angle PseudoRapidity() const {
        //Value m = Mag();
        //return 0.5*log((m+z_)/(m-z_) );
        // guard against Pt=0
        double cosTheta = CosTheta();
        if (sqr(cosTheta) < 1) return -0.5 * units::log((1 - cosTheta) / (1 + cosTheta));
        if (z_ == 0) return 0_rad;
        // Warning("PseudoRapidity","transvers momentum = 0! return +/- 10e10");
        if (z_ > 0) return 10e10_rad;
        else return -10e10_rad;
    }

    boca::Angle Eta() const {
        return PseudoRapidity();
    }

// Rotates the Hep3Vector around the x-axis.
    void RotateX(boca::Angle angle) {
        //rotate vector around X
        double s = boost::units::sin(angle);
        double c = boost::units::cos(angle);
        Value y = y_;
        y_ = c * y - s * z_;
        z_ = s * y + c * z_;
    }

// Rotates the Hep3Vector around the y-axis.
    void RotateY(boca::Angle angle) {
        //rotate vector around Y
        double s = boost::units::sin(angle);
        double c = boost::units::cos(angle);
        Value z = z_;
        z_ = c * z - s * x_;
        x_ = s * z + c * x_;
    }

// Rotates the Hep3Vector around the z-axis.
    void RotateZ(boca::Angle angle) {
        //rotate vector around Z
        double s = boost::units::sin(angle);
        double c = boost::units::cos(angle);
        Value z = z_;
        Value x = x_;
        x_ = c * x - s * y_;
        y_ = s * x + c * y_;
    }

// Rotates reference frame from Uz to newUz(unit vector)(Geant4).
    void RotateUz(Vector3 const& vector) {
        // NewUzVector must be normalized !
        Value x = vector.x_;
        Value y = vector.y_;
        Value z = vector.z_;
        ValueSquared square = sqr(x) + sqr(y);
        if (square) {
            square = std::sqrt(square);
            Value px = x_;
            Value py = y_;
            Value pz = z_;
            x_ = (x * z * px - y * py + x * square * pz) / square;
            y_ = (y * z * px + x * py + y * square * pz) / square;
            z_ = (z * z * px - px + z * square * pz) / square;
        } else if (z < Value(0)) {
            x_ = -x_; // phi=0 teta=pi
            z_ = -z_;
        } else {};
    }

//     void Rotate(boca::Angle angle, const Vector3& axis) {
//         //rotate vector
//         TRotation trans;
//         trans.Rotate(angle, axis);
//         operator*=(trans);
//     }
    // Rotates around the axis specified by another Hep3Vector.

//     Vector3& operator*=(const TRotation& m) {
//         //multiplication operator
//         return *this = m *(*this);
//     }

//     Vector3& Transform(const TRotation& m) {
//         //transform this vector with a Rotation
//         return *this = m *(*this);
//     }
    // Transformation with a Rotation matrix.

    Vector2<Value> XYvector() const {
        return {x_, y_};
    }

    Vector2<boca::Angle> EtaPhiVector() const {
        return {Eta(), Phi()};
    }

    // Scale with scalar
    template <typename Value_2>
    Vector3<ValueProduct<Value_2>> Scale(Value_2 const& scalar) const {
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    // Scalar product.
    template <typename Value_2>
    ValueProduct<Value_2> Dot(Vector3<Value_2> const& vector) const {
        return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
    }

    // Cross product
    template <typename Value_2>
    Vector3<ValueProduct<Value_2>> Cross(Vector3<Value_2> const& vector) const {
        return {y_* vector.z_ - vector.y_ * z_, z_* vector.x_ - vector.z_ * x_, x_* vector.y_ - vector.x_ * y_};
    }

    // Triple product
    template <typename Value_2, typename Value_3>
    ValueCubed<Value_2, Value_3> Triple(Vector3<Value_2> const& vector_1, Vector3<Value_2> const& vector_2) {
        return Cross(vector_1) * vector_2;
    }

    // Addition.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector3& operator+=(Vector3<Value_2> const& vector) {
        x_ += vector.x_;
        y_ += vector.y_;
        z_ += vector.z_;
        return *this;
    }

    // Subtraction
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector3& operator-=(Vector3<Value_2> const& vector) {
        x_ -= vector.x_;
        y_ -= vector.y_;
        z_ -= vector.z_;
        return *this;
    }

    // Scaling with real numbers
    template < typename Value_2, typename = OnlyIfNotQuantity<Value_2> >
    Vector3& operator*=(Value_2 scalar) {
        x_ *= scalar;
        y_ *= scalar;
        z_ *= scalar;
        return *this;
    }

    /// division by scalar
    template < typename Value_2, typename = OnlyIfNotQuantity<Value_2> >
    Vector3& operator/=(Value_2 scalar) {
        x_ /= scalar;
        y_ /= scalar;
        z_ /= scalar;
        return *this;
    }

    // Addition of 3-vectors.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    friend Vector3 operator+(Vector3 const& vector_1, Vector3<Value_2> const& vector_2) {
        return {vector_1.X() + vector_2.X(), vector_1.Y() + vector_2.Y(), vector_1.Z() + vector_2.Z()};
    }

    // Subtraction of 3-vectors.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    friend Vector3 operator-(Vector3 const& vector_1, Vector3<Value_2> const& vector_2) {
        return {vector_1.X() - vector_2.X(), vector_1.Y() - vector_2.Y(), vector_1.Z() - vector_2.Z()};
    }

    template <typename Value_2>
    friend Vector3<ValueProduct<Value_2>> operator^(Vector3 const& vector_1, Vector3<Value_2> const& vector_2) {
        return vector_1.Cross(vector_2);
    }

    template <typename Value_2>
    friend Vector3 <ValueQuotient<Value_2>> operator/(Vector3 const& vector, Value_2 const& scalar) {
        return vector.Scale(1. / scalar);
    }

    // Get components by index
    Value operator()(int i) const {
        //dereferencing operator const
        switch (i) {
        case 0 : return x_;
        case 1 : return y_;
        case 2 : return z_;
        default : std::cout << "bad index(%d) returning 0 " << i << std::endl;
        }
        return 0;
    }

    Value operator[](int i) const {
        return operator()(i);
    }

    // Set components by index.
    Value& operator()(int i) {
        //dereferencing operator
        switch (i) {
        case 0 : return x_;
        case 1 : return y_;
        case 2 : return z_;
        default : std::cout << "bad index(%d) returning &x_" <<  i << std::endl;
        }
        return x_;
    }

    Value& operator[](int i) {
        return operator()(i);
    }

    // Comparisons
    bool operator==(Vector3 const& vector) const {
        return vector.x_ == x_ && vector.y_ == y_ && vector.z_ == z_;
    }

    bool operator!=(Vector3 const& vector) const {
        return vector.x_ != x_ || vector.y_ != y_ || vector.z_ != z_;
    }

    // Unary minus
    Vector3 operator-() const {
        return { -x_, -y_, -z_};
    }

private:

    Value x_;

    Value y_;

    Value z_;

};

template <typename>
struct IsVector3 : std::false_type { };

template <typename Value>
struct IsVector3<Vector3<Value>> : std::true_type { };

template<typename Value>
using OnlyIfNotVector3 = typename std::enable_if < !IsVector3<Value>::value >::type;

// Scalar product of 3-vectors.
template <class Value, class Value_2>
ValueProduct<Value, Value_2> operator*(Vector3<Value> const& vector_1, Vector3<Value_2> const& vector_2)
{
    return vector_1.Dot(vector_2);
}

// Scaling of 3-vectors with a real number
template < class Value, class Value_2, typename = OnlyIfNotVector3<Value_2> >
Vector3 <ValueProduct<Value, Value_2>> operator*(Vector3<Value> const& vector, Value_2 scalar)
{
    return vector.Scale(scalar);
}

template < class Value, class Value_2, typename = OnlyIfNotVector3<Value_2> >
Vector3 <ValueProduct<Value, Value_2>> operator*(Value_2 scalar, Vector3<Value> const& vector)
{
    return vector.Scale(scalar);
}

// Vector3 operator*(TMatrix const&, Vector3 const& v)
// {
//     return Vector3(m(0, 0) * v.X() + m(0, 1) * v.Y() + m(0, 2) * v.Z(),
//                    m(1, 0) * v.X() + m(1, 1) * v.Y() + m(1, 2) * v.Z(),
//                    m(2, 0) * v.X() + m(2, 1) * v.Y() + m(2, 2) * v.Z());
// }



// template
// Vector3<double>::Vector3(TVector3 const& vector);

}
