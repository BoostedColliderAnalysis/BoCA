// @(#)root/physics:$Id$
// Author: Pasha Murat, Peter Malzacher   12/02/99
// Jan Hajer 2015 (templates and units)

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

#include "TVector3.h"
#include "boca/math/Vector2.hh"

namespace boca
{

enum class Dim3
{
    x,
    y,
    z,
    last
};

std::string Name(Dim3 dimension);

std::vector<Dim3> Dimensions3();

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

    using ValueSquare = boca::ValueSquare<Value>;

    template<typename Value_2, typename Value_3>
    using ValueCubed = boca::ValueProduct<ValueProduct<Value_2>, Value_3>;

    template<typename Value_2>
    using ValueQuotient = ValueQuotient<Value, Value_2>;

    using ValueInverse = boost::units::divide_typeof_helper<double, Value>;

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value, Value_2>::value >::type;

    // Constructor
    Vector3() : x_(Value(0)), y_(Value(0)), z_(Value(0)) {}

    // Constructor
    Vector3(Value x, Value y, Value z) : x_(x), y_(y), z_(z) {};

    // Constructor
    Vector3(Value value, Dim3 dim) {
        x_ = dim == Dim3::x ? value : Value(0);
        y_ = dim == Dim3::y ? value : Value(0);
        z_ = dim == Dim3::z ? value : Value(0);
    }

    // Constructor
    template<typename Value_2>
    Vector3(Vector3<Value_2> const& vector) {
        x_ = Value(vector.X());
        y_ = Value(vector.Y());
        z_ = Value(vector.Z());
    }

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

    //set Pt, Eta and Phi
    void SetPtEtaPhi(Value pt, boca::Angle const& eta, boca::Angle const& phi) {
        auto apt = abs(pt);
        SetXYZ(apt * boost::units::cos(phi), apt * boost::units::sin(phi), apt / boost::units::tan(2.0 * boost::units::atan(units::exp(-eta))));
    }

    //set Pt, Theta and Phi
    void SetPtThetaPhi(Value pt, boca::Angle const& theta, boca::Angle const& phi) {
        x_ = pt * boost::units::cos(phi);
        y_ = pt * boost::units::sin(phi);
        auto tanTheta = boost::units::tan(theta);
        z_ = tanTheta ? pt / tanTheta : Value(0);
    }

    // Set phi keeping mag and theta constant(BaBar).
    void SetPhi(boca::Angle const& phi) {
        auto perp = Perp();
        SetX(perp * boost::units::cos(phi));
        SetY(perp * boost::units::sin(phi));
    }

    // Set theta keeping mag and phi constant(BaBar).
    void SetTheta(boca::Angle const& theta) {
        auto magnitude = Mag();
        auto phi = Phi();
        SetX(magnitude * boost::units::sin(theta) * boost::units::cos(phi));
        SetY(magnitude * boost::units::sin(theta) * boost::units::sin(phi));
        SetZ(magnitude * boost::units::cos(theta));
    }

    // Set magnitude keeping theta and phi constant(BaBar).
    void SetMag(Value magnitude) {
        auto old = Mag();
        if (old == 0) {
            // Warning("SetMag","zero vector can't be stretched");
        } else {
            auto factor = magnitude / old;
            SetX(x_ * factor);
            SetY(y_ * factor);
            SetZ(z_ * factor);
        }
    }

    void SetMagThetaPhi(Value mag, boca::Angle const& theta, boca::Angle const& phi) {
        //setter with mag, theta, phi
        auto amag = abs(mag);
        x_ = amag * boost::units::sin(theta) * boost::units::cos(phi);
        y_ = amag * boost::units::sin(theta) * boost::units::sin(phi);
        z_ = amag * boost::units::cos(theta);
    }

    // Set the transverse component keeping phi and z constant.
    void SetPerp(Value perp) {
        auto old = Perp();
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

    Value& X() {
        return x_;
    }

    Value& Y() {
        return y_;
    }

    Value& Z() {
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
        auto ptot = Mag();
        return ptot == 0 ? 1 : z_ / ptot;
    }

// The magnitude squared(rho^2 in spherical coordinate system).
    ValueSquare Mag2() const {
        return sqr(x_) + sqr(y_) + sqr(z_);
    }

// The magnitude(rho in spherical coordinate system).
    Value Mag() const {
        // return the magnitude(rho in spherical coordinate system)
        return sqrt(Mag2());
    }

// The transverse component squared(R^2 in cylindrical coordinate system).
    ValueSquare Perp2() const {
        return sqr(x_) + sqr(y_);
    }

// The transverse component(R in cylindrical coordinate system).
    Value Perp() const {
        //return the transverse component(R in cylindrical coordinate system)
        return sqrt(Perp2());
    }

    // The transverse component w.r.t. given axis squared.
    template <typename Value_2>
    ValueSquare Perp2(Vector3<Value_2> const& vector) const {
        auto other_mag2 = vector.Mag2();
        auto mixing = Dot(vector);
        auto this_mag_2 = Mag2();
        if (other_mag2 > boca::ValueSquare<Value_2>(0)) this_mag_2 -= sqr(mixing) / other_mag2;
        if (this_mag_2 < ValueSquare(0)) this_mag_2 = ValueSquare(0);
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
        auto deta = Eta() - vector.Eta();
        auto dphi = RestrictPhi(Phi() - vector.Phi());
        return sqrt(sqr(deta) + sqr(dphi));
    }

    boca::Angle DrEtaPhi(Vector3 const& vector) const {
        return DeltaR(vector);
    }

// // Unit vector parallel to this.
//     Vector3<double> Unit() const {
//         // return unit vector parallel to this.
//         ValueSquare tot2 = Mag2();
//         ValueInverse tot = tot2 > ValueSquare(0) ? 1. / sqrt(tot2) : 1. / Value(1.);
//         return {x_ * tot, y_ * tot, z_ * tot};
//     }


    Vector3<double> Unit() const {
        return Unit(IsQuantity<Value>());
    }

    Vector3<double> Unit(std::true_type) const {
        auto tot2 = Mag2();
        if (tot2 == ValueSquare(0)) return {x_.value(), y_.value(), z_.value()};
        auto tot = 1. / boost::units::sqrt(tot2);
        return {x_ * tot, y_ * tot, z_ * tot};
    }

    Vector3<double> Unit(std::false_type) const {
        auto tot2 = Mag2();
        auto tot = tot2 > Value(0) ? 1. / std::sqrt(tot2) : 1.;
        return {x_ * tot, y_ * tot, z_ * tot};
    }

// Vector orthogonal to this(Geant4).
    Vector3 Orthogonal() const {
        auto x = x_ < Value(0) ? -x_ : x_;
        auto y = y_ < Value(0) ? -y_ : y_;
        auto z = z_ < Value(0) ? -z_ : z_;
        if (x < y) return x < z ? Vector3(Value(0), z_, -y_) : Vector3(y_, -x_, Value(0));
        else return y < z ? Vector3(-z_, Value(0), x_) : Vector3(y_, -x_, Value(0));
    }

    using Value4 = typename boost::units::multiply_typeof_helper<ValueSquare, ValueSquare>::type;
// The angle w.r.t. another 3-vector.
    boca::Angle Angle(Vector3 const& vector) const {
        // return the angle w.r.t. another 3-vector
        auto ptot2 = Mag2() * vector.Mag2();
        if (ptot2 <= Value4(0)) return 0_rad;
        auto arg = Dot(vector) / sqrt(ptot2);
        if (arg > 1) arg = 1;
        if (arg < -1) arg = -1;

        auto res = acos(arg);

        // TVector3 finds the angle by acos(one.two / sqrt(one.one*two.two))
        // This has a relative error of 0.5*epsilon / angle**2 (where epsilon is machine epsilon)
        // due to catastrophic cancellation
        // This form is better (from my personal experiments)
        auto test = atan2(Cross(vector).Mag(), Dot(vector));

        if(res != test) Debug("first", res, "second", test);
        return boca::Angle(res);
    }

    // Find the tan(theta)**2 between two PseudoJets by calculating (p3>_1 x p3>_2)**2 / (p3>_1 . p3>_2)**2
    double Tan2(Vector3 const& vector){
      // This is more accurate than an alternate form (one.one*two.two-(one.two)**2)/(one.two)**2
      // because the cancellation in the numerator (cross-product) is handled component-by-component, rather than all at once.
      auto numerator = sqr(X() * vector.Y() - Y() * vector.X());
      numerator += sqr(X() * vector.Z() - Z() * vector.X());
      numerator += sqr(Y() * vector.Z() - Z() * vector.Y());
      return numerator / sqr(Dot(vector));
    }

// Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))
    boca::Angle PseudoRapidity() const {
        //Value m = Mag();
        //return 0.5*log((m+z_)/(m-z_) );
        // guard against Pt=0
        auto cosTheta = CosTheta();
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
    void RotateX(boca::Angle const& angle) {
        //rotate vector around X
        auto s = boost::units::sin(angle);
        auto c = boost::units::cos(angle);
        auto y = y_;
        y_ = c * y - s * z_;
        z_ = s * y + c * z_;
    }

// Rotates the Hep3Vector around the y-axis.
    void RotateY(boca::Angle const& angle) {
        //rotate vector around Y
        auto s = boost::units::sin(angle);
        auto c = boost::units::cos(angle);
        auto z = z_;
        z_ = c * z - s * x_;
        x_ = s * z + c * x_;
    }

// Rotates the Hep3Vector around the z-axis.
    void RotateZ(boca::Angle const& angle) {
        //rotate vector around Z
        auto s = boost::units::sin(angle);
        auto c = boost::units::cos(angle);
        auto z = z_;
        auto x = x_;
        x_ = c * x - s * y_;
        y_ = s * x + c * y_;
    }

// Rotates reference frame from Uz to newUz(unit vector)(Geant4).
    void RotateUz(Vector3 const& vector) {
        // NewUzVector must be normalized !
        auto x = vector.x_;
        auto y = vector.y_;
        auto z = vector.z_;
        auto square = sqr(x) + sqr(y);
        if (square) {
            auto sqrt = std::sqrt(square);
            auto px = x_;
            auto py = y_;
            auto pz = z_;
            x_ = (x * z * px - y * py + x * sqrt * pz) / sqrt;
            y_ = (y * z * px + x * py + y * sqrt * pz) / sqrt;
            z_ = (z * z * px - px + z * sqrt * pz) / sqrt;
        } else if (z < Value(0)) {
            x_ = -x_; // phi=0 teta=pi
            z_ = -z_;
        } else {};
    }

//     void Rotate(boca::Angle angle, const Vector3& axis) {
//         //rotate vector
//         Matrix3<Value> trans;
//         trans.Rotate(angle, axis);
//         operator*=(trans);
//     }
    // Rotates around the axis specified by another Hep3Vector.

//     Vector3& operator*=(const Matrix3<Value>& m) {
//         //multiplication operator
//         return *this = m *(*this);
//     }

//     Vector3& Transform(const Matrix3<Value>& m) {
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
        return x_ * vector.X() + y_ * vector.Y() + z_ * vector.Z();
    }

    // Cross product
    template <typename Value_2>
    Vector3<ValueProduct<Value_2>> Cross(Vector3<Value_2> const& vector) const {
        return {y_ * vector.Z() - vector.Y()* z_, z_ * vector.X() - vector.Z()* x_, x_ * vector.Y() - vector.X()* y_};
    }

    // Triple product
    template <typename Value_2, typename Value_3>
    ValueCubed<Value_2, Value_3> Triple(Vector3<Value_2> const& vector_1, Vector3<Value_3> const& vector_2) const {
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
    Value const& operator()(Dim3 dimension) const {
        //dereferencing operator const
        switch (dimension) {
        case Dim3::x : return x_;
        case Dim3::y : return y_;
        case Dim3::z : return z_;
        default : std::cout << "bad index(%d) returning 0 " << Name(dimension) << std::endl;
        }
        return x_;
    }

    // Set components by index.
    Value& operator()(Dim3 dimension) {
        //dereferencing operator
        switch (dimension) {
        case Dim3::x : return x_;
        case Dim3::y : return y_;
        case Dim3::z : return z_;
        default : std::cout << "bad index(%d) returning &x_" <<  Name(dimension) << std::endl;
        }
        return x_;
    }

    Value const& operator[](Dim3 dimension) const {
        return operator()(dimension);
    }

    Value& operator[](Dim3 dimension) {
        return operator()(dimension);
    }

    ConstIterator<boca::Vector3, Value, Dim3> begin() const {
        return {this, Dim3::x};
    }

    ConstIterator<boca::Vector3, Value, Dim3> end() const {
        return {this, Dim3::last};
    }

    Iterator<boca::Vector3, Value, Dim3> begin() {
        return {this, Dim3::x};
    }

    Iterator<boca::Vector3, Value, Dim3> end() {
        return {this, Dim3::last};
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

template <class Value_1, class Value_2, class Value_3>
auto Triple(Vector3<Value_1> const& vector_1, Vector3<Value_2> const& vector_2, Vector3<Value_3> const& vector_3)
{
    return vector_1.Triple(vector_2, vector_3);
}

template<typename Value_>
using GradedVector3 = GradedContainer<Vector3, Value_>;

}
