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
#include <cmath>
#include "Vector2.hh"
#include "TVector3.h"
#include "TRotation.h"

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
    using ValueProduct2 = boca::ValueProduct<ValueProduct<Value_2>, Value_3>;

    template<typename Value_2>
    using ValueQuotient = typename boost::units::divide_typeof_helper<Value, Value_2>::type;

    template <typename> struct IsQuantity : std::false_type { };
    template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type { };

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value, Value_2>::value >::type;

    template<typename Value_2>
    using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value_2>::value >::type;

    void operator=(TVector3 const& vector) {
        x_ = vector.X();
        y_ = vector.Y();
        z_ = vector.Z();
    }

    Vector3() : x_(0), y_(0), z_(0) {}

// Constructor.
    Vector3(Value x, Value y, Value z) : x_(x), y_(y), z_(z) {};

// Get components by index(Geant4).
    Value operator()(int i) const {
        //dereferencing operatorconst
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

// The components in cartesian coordinate system.
    Value X() const {
        return x_;
    }

    Value Y() const {
        return y_;
    }

    Value Z() const {
        return z_;
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
    void SetPtEtaPhi(Value pt, Value eta, Value phi) {
        //set Pt, Eta and Phi
        Value apt = std::abs(pt);
        SetXYZ(apt * std::cos(phi), apt * std::sin(phi), apt / std::tan(2.0 * std::atan(std::exp(-eta))));
    }
    void SetPtThetaPhi(Value pt, Value theta, Value phi) {
        //set Pt, Theta and Phi
        x_ = pt * std::cos(phi);
        y_ = pt * std::sin(phi);
        Value tanTheta = std::tan(theta);
        z_ = tanTheta ? pt / tanTheta : 0;
    }

// The azimuth angle. returns phi from -pi to pi
    Angle Phi() const {
        Phi(IsQuantity<Value>());
    }

// The polar angle.
    Angle Theta() const {
        Theta(IsQuantity<Value>());
    }

// Cosine of the polar angle.
    double CosTheta() const {
        Value ptot = Mag();
        return ptot == 0 ? 1 : z_ / ptot;
    }

// The magnitude squared(rho^2 in spherical coordinate system).
    ValueSquared Mag2() const {
        return x_ * x_ + y_ * y_ + z_ * z_;
    }

// The magnitude(rho in spherical coordinate system).
    Value Mag() const {
        // return the magnitude(rho in spherical coordinate system)
        return std::sqrt(Mag2());
    }

// Set phi keeping mag and theta constant(BaBar).
    void SetPhi(Angle phi) {
        // Set phi keeping mag and theta constant(BaBar).
        Value perp = Perp();
        SetX(perp * boost::units::cos(phi));
        SetY(perp * boost::units::sin(phi));
    }

// Set theta keeping mag and phi constant(BaBar).
    void SetTheta(Angle theta) {
        // Set theta keeping mag and phi constant(BaBar).
        Value magnitude = Mag();
        Angle phi = Phi();
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

// The transverse component squared(R^2 in cylindrical coordinate system).
    ValueSquared Perp2() const {
        return x_ * x_ + y_ * y_;
    }

// The transverse component(R in cylindrical coordinate system).

    Value Perp() const {
        //return the transverse component(R in cylindrical coordinate system)
        return std::sqrt(Perp2());
    }


// Set the transverse component keeping phi and z constant.
    void SetPerp(Value r) {
        Value p = Perp();
        if (p != 0) {
            x_ *= r / p;
            y_ *= r / p;
        }
    }

// The transverse component w.r.t. given axis squared.
    Value Perp2(Vector3 const& p) const {
        Value tot = p.Mag2();
        Value ss = Dot(p);
        Value per = Mag2();
        if (tot > 0)
            per -= ss * ss / tot;
        if (per < 0)
            per = 0;
        return per;
    }

// The transverse component w.r.t. given axis.
    Value Perp(Vector3 const& vector) const {
        //return the transverse component(R in cylindrical coordinate system)
        return std::sqrt(Perp2(vector));
    }

    Value DeltaPhi(Vector3 const& v) const {
        return Phi_mpi_pi(Phi() - v.Phi());
    }

    Value DeltaR(Vector3 const& v) const {
        //return deltaR with respect to v
        Value deta = Eta() - v.Eta();
        Value dphi = Phi_mpi_pi(Phi() - v.Phi());
        return std::sqrt(deta * deta + dphi * dphi);
    }

    Value DrEtaPhi(Vector3 const& v) const {
        return DeltaR(v);
    }

    void SetMagThetaPhi(Value mag, Value theta, Value phi) {
        //setter with mag, theta, phi
        Value amag = std::abs(mag);
        x_ = amag * std::sin(theta) * std::cos(phi);
        y_ = amag * std::sin(theta) * std::sin(phi);
        z_ = amag * std::cos(theta);
    }

    // Comparisons
    bool operator==(Vector3 const& vector) const {
        return vector.x_ == x_ && vector.y_ == y_ && vector.z_ == z_;
    }

    bool operator!=(Vector3 const& vector) const {
        return vector.x_ != x_ || vector.y_ != y_ || vector.z_ != z_;
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

// Unary minus
    Vector3 operator-() const {
        return { -x_, -y_, -z_};
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


// Unit vector parallel to this.
    Vector3 Unit() const {
        // return unit vector parallel to this.
        Value tot2 = Mag2();
        Value tot = (tot2 > 0) ? 1 / std::sqrt(tot2) : 1;
        Vector3 p(x_ * tot, y_ * tot, z_ * tot);
        return p;
    }

// Vector orthogonal to this(Geant4).
    Vector3 Orthogonal() const {
        Value x = x_ < 0 ? -x_ : x_;
        Value y = y_ < 0 ? -y_ : y_;
        Value z = z_ < 0 ? -z_ : z_;
        if (x < y)
            return x < z ? Vector3(0, z_, -y_) : Vector3(y_, -x_, 0);
        else
            return y < z ? Vector3(-z_, 0, x_) : Vector3(y_, -x_, 0);
    }

    // Scalar product.
    template <typename Value_2>
    ValueProduct<Value_2> Dot(Vector3<Value_2> const& vector) const {
        return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
    }

    // Cross product.
    template <typename Value_2>
    Vector3<ValueProduct<Value_2>> Cross(Vector3<Value_2> const& vector) const {
        return {y_* vector.z_ - vector.y_ * z_, z_* vector.x_ - vector.z_ * x_, x_* vector.y_ - vector.x_ * y_};
    }

    template <typename Value_2, typename Value_3>
    ValueProduct2<Value_2, Value_3> Triple(Vector3<Value_2> const& vector_1, Vector3<Value_2> const& vector_2) {
        return Cross(vector_1) * vector_2;
    }


// The angle w.r.t. another 3-vector.
    Value angle(Vector3 const& vector) const {
        // return the angle w.r.t. another 3-vector
        Value ptot2 = Mag2() * vector.Mag2();
        if (ptot2 <= 0) return 0;
        else {
            Value arg = Dot(vector) / std::sqrt(ptot2);
            if (arg > 1) arg = 1;
            if (arg < -1) arg = -1;
            return std::acos(arg);
        }
    }

// Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))
    Value PseudoRapidity() const {
        //Value m = Mag();
        //return 0.5*log((m+z_)/(m-z_) );
        // guard against Pt=0
        double cosTheta = CosTheta();
        if (cosTheta * cosTheta < 1)
            return -0.5 * std::log((1 - cosTheta) / (1 + cosTheta));
        if (z_ == 0)
            return 0;
        // Warning("PseudoRapidity","transvers momentum = 0! return +/- 10e10");
        if (z_ > 0)
            return 10e10;
        else
            return -10e10;
    }

    Value Eta() const {
        return PseudoRapidity();
    }

// Rotates the Hep3Vector around the x-axis.
    void RotateX(Value angle) {
        //rotate vector around X
        Value s = std::sin(angle);
        Value c = std::cos(angle);
        Value y = y_;
        y_ = c * y - s * z_;
        z_ = s * y + c * z_;
    }

// Rotates the Hep3Vector around the y-axis.
    void RotateY(Value angle) {
        //rotate vector around Y
        Value s = std::sin(angle);
        Value c = std::cos(angle);
        Value z = z_;
        z_ = c * z - s * x_;
        x_ = s * z + c * x_;
    }

// Rotates the Hep3Vector around the z-axis.
    void RotateZ(Value angle) {
        //rotate vector around Z
        Value s = std::sin(angle);
        Value c = std::cos(angle);
        Value x = x_;
        x_ = c * x - s * y_;
        y_ = s * x + c * y_;
    }

// Rotates reference frame from Uz to newUz(unit vector)(Geant4).
    void RotateUz(Vector3 const& NewUzVector) {
        // NewUzVector must be normalized !
        Value u1 = NewUzVector.x_;
        Value u2 = NewUzVector.y_;
        Value u3 = NewUzVector.z_;
        Value up = u1 * u1 + u2 * u2;
        if (up) {
            up = std::sqrt(up);
            Value px = x_, py = y_, pz = z_;
            x_ = (u1 * u3 * px - u2 * py + u1 * up * pz) / up;
            y_ = (u2 * u3 * px + u1 * py + u2 * up * pz) / up;
            z_ = (u3 * u3 * px - px + u3 * up * pz) / up;
        } else if (u3 < 0.) {
            x_ = -x_; // phi=0 teta=pi
            z_ = -z_;
        } else {};
    }


    void Rotate(Value angle, const Vector3& axis) {
        //rotate vector
        TRotation trans;
        trans.Rotate(angle, axis);
        operator*=(trans);
    }
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
        return Vector2<Value>(x_, y_);
    }

    Vector2<Value> EtaPhiVector() const {
        return Vector2<Value>(Eta(), Phi());
    }

private:

    template<typename>
    friend class Vector2;

    Angle Phi(std::false_type) const {
        return x_ == 0 && y_ == 0 ? 0. * rad : double(std::atan2(y_, x_)) * rad;
    }
    Angle Phi(std::true_type) const {
        return x_ == 0 && y_ == 0 ? 0. * rad : boost::units::atan2(y_, x_);
    }
    Angle Theta(std::false_type) const {
        return x_ == 0 && y_ == 0 && z_ == 0 ? 0. * rad : double(std::atan2(Perp(), z_)) * rad;
    }
    Angle Theta(std::true_type) const {
        return x_ == 0 && y_ == 0 && z_ == 0 ? 0. * rad : boost::units::atan2(Perp(), z_);
    }

// The components.
    Value x_;
    Value y_;
    Value z_;

};

// Scalar product of 3-vectors.
template <class Value, class Value_2>
ValueProduct<Value, Value_2> operator*(Vector3<Value> const& vector_1, Vector3<Value_2> const& vector_2)
{
    return vector_1.Dot(vector_2);
}

// Scaling of 3-vectors with a real number
template < class Value, class Value_2, typename = OnlyIfNotVector<Value_2> >
Vector3 <ValueProduct<Value, Value_2>> operator*(Vector3<Value> const& vector, Value_2 scalar)
{
    return {scalar * vector.X(), scalar * vector.Y(), scalar * vector.Z()};
}

template < class Value, class Value_2, typename = OnlyIfNotVector<Value_2> >
Vector3 <ValueProduct<Value, Value_2>> operator*(Value_2 scalar, Vector3<Value> const& vector)
{
    return {scalar * vector.X(), scalar * vector.Y(), scalar * vector.Z()};
}

// Vector3 operator*(TMatrix const&, Vector3 const& v)
// {
//     return Vector3(m(0, 0) * v.X() + m(0, 1) * v.Y() + m(0, 2) * v.Z(),
//                    m(1, 0) * v.X() + m(1, 1) * v.Y() + m(1, 2) * v.Z(),
//                    m(2, 0) * v.X() + m(2, 1) * v.Y() + m(2, 2) * v.Z());
// }

}

