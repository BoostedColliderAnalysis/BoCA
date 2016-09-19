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
 * @brief Three dimensionial vector
 *
 */
template<class Value_>
class Vector3 : public boost::less_than_comparable<Vector3<Value_>>
            , public boost::equality_comparable<Vector3<Value_>>
            , public boost::addable<Vector3<Value_>>
            , public boost::subtractable<Vector3<Value_>>
{

    template<typename Value_2_>
    using ValueProduct = ValueProduct<Value_, Value_2_>;

    using ValueSquare = boca::ValueSquare<Value_>;

    template<typename Value_2_, typename Value_3>
    using ValueCubed = boca::ValueProduct<ValueProduct<Value_2_>, Value_3>;

    template<typename Value_2_>
    using ValueQuotient = ValueQuotient<Value_, Value_2_>;

    using ValueInverse = boost::units::divide_typeof_helper<double, Value_>;

    template<typename Value_2_>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2_>::value || std::is_same<Value_, Value_2_>::value >::type;

public:

    /**
     * @name Constructor
     * @{
     */

    /**
     * @brief Default constructor
     */
    Vector3() :
        x_(0),
        y_(0),
        z_(0)
    {}

    /**
     * @brief Constructor accepting three scalars
     */
    Vector3(Value_ x, Value_ y, Value_ z) :
        x_(x),
        y_(y),
        z_(z)
    {};

    /**
     * @brief Constructor one scalar and its direction
     */
    Vector3(Value_ value, Dim3 dim) {
        x_ = dim == Dim3::x ? value : Value_(0);
        y_ = dim == Dim3::y ? value : Value_(0);
        z_ = dim == Dim3::z ? value : Value_(0);
    }

    /**
     * @brief Constructor accepting a three vector
     */
    template<typename Value_2_>
    Vector3(Vector3<Value_2_> const& vector) :
        x_(vector.X()),
        y_(vector.Y()),
        z_(vector.Z())
    {}

    /**
     * @brief Constructor accepting a root::TVector3
     */
    Vector3(TVector3 const& vector) :
        x_(vector.X()),
        y_(vector.Y()),
        z_(vector.Z())
    {}
    //@}

    /**
     * @name Setter
     * @{
     */

    /**
     * @brief Set Pt, Eta and Phi
     */
    void SetPtEtaPhi(Value_ pt, boca::Angle const& eta, boca::Angle const& phi) {
        auto apt = abs(pt);
        x_ = apt * cos(phi);
        y_ = apt * sin(phi);
        z_ = apt / tan(2.0 * atan(units::exp(-eta)));
    }

    /**
     * @brief Set Pt, Theta and Phi
     */
    void SetPtThetaPhi(Value_ pt, boca::Angle const& theta, boca::Angle const& phi) {
        x_ = pt * cos(phi);
        y_ = pt * sin(phi);
        auto tanTheta = tan(theta);
        z_ = tanTheta ? pt / tanTheta : Value_(0);
    }

    /**
     * @brief Set phi keeping the magnitue and theta constant
     */
    void SetPhi(boca::Angle const& phi) {
        auto perp = Perp();
        x_ = perp * cos(phi);
        y_ = perp * sin(phi);
    }

    /**
     * @brief Set theta keeping mag and phi constant
     */
    void SetTheta(boca::Angle const& theta) {
        auto magnitude = Mag();
        auto phi = Phi();
        x_ = magnitude * sin(theta) * cos(phi);
        y_ = magnitude * sin(theta) * sin(phi);
        z_ = magnitude * cos(theta);
    }

    /**
     * @brief Set the magnitude keeping theta and phi constant
     */
    void SetMag(Value_ magnitude) {
        auto old = Mag();
        if (old == Value_(0)) Debug("SetMag","zero vector can't be stretched");
        else *this *= magnitude / old;
    }

    /**
     * @brief Set mag, theta, phi
     */
    void SetMagThetaPhi(Value_ mag, boca::Angle const& theta, boca::Angle const& phi) {
        auto amag = abs(mag);
        x_ = amag * sin(theta) * cos(phi);
        y_ = amag * sin(theta) * sin(phi);
        z_ = amag * cos(theta);
    }

    /**
     * @brief Set the transverse component keeping phi and z constant.
     */
    void SetPerp(Value_ perp) {
        auto old = Perp();
        if (old == Value_(0)) return;
        x_ *= perp / old;
        y_ *= perp / old;
    }
    //@}

    /**
     * @name Accessors and Getters
     * @{
     */

    /**
     * @brief X getter
     */
    Value_ X() const {
        return x_;
    }

    /**
     * @brief Y getter
     */
    Value_ Y() const {
        return y_;
    }

    /**
     * @brief Z getter
     */
    Value_ Z() const {
        return z_;
    }

    /**
     * @brief X accessor
     */
    Value_& X() {
        return x_;
    }

    /**
     * @brief Y accessor
     */
    Value_& Y() {
        return y_;
    }

    /**
     * @brief Z accessor
     */
    Value_& Z() {
        return z_;
    }
    //@}

    /**
     * @brief The azimuth angle \f$\phi\f$ restricted to \f$[-\pi,\pi]\f$
     */
    boca::Angle Phi() const {
        return x_ == Value_(0) && y_ == Value_(0) ? 0_rad : atan2(y_, x_);
    }

    /**
     * @brief The polar angle \f$\theta\f$
     */
    boca::Angle Theta() const {
        return x_ == Value_(0) && y_ == Value_(0) && z_ == Value_(0) ? 0_rad : atan2(Perp(), z_);
    }

    /**
     * @brief Cosine of the polar angle.
     */
    double CosTheta() const {
        auto ptot = Mag();
        return ptot == Value_(0) ? 1 : z_ / ptot;
    }

    /**
     * @brief The magnitude squared \f$x^2 + y^2 + z^2\f$
     */
    ValueSquare Mag2() const {
        return sqr(x_) + sqr(y_) + sqr(z_);
    }

    /**
     * @brief The magnitude \f$sqrt{x^2 + y^2 + z^2}\f$
     */
    Value_ Mag() const {
        return sqrt(Mag2());
    }

    /**
     * @brief The transverse component squared \f$x^2 + y^2\f$
     */
    ValueSquare Perp2() const {
        return sqr(x_) + sqr(y_);
    }

    /**
     * @brief The transverse component \f$sqrt{x^2 + y^2}\f$
     */
    Value_ Perp() const {
        return sqrt(Perp2());
    }

    // The transverse component w.r.t. given axis squared.
    template <typename Value_2_>
    ValueSquare Perp2(Vector3<Value_2_> const& vector) const {
        auto other_mag2 = vector.Mag2();
        auto mixing = Dot(vector);
        auto this_mag_2 = Mag2();
        if (other_mag2 > boca::ValueSquare<Value_2_>(0)) this_mag_2 -= sqr(mixing) / other_mag2;
        if (this_mag_2 < ValueSquare(0)) this_mag_2 = ValueSquare(0);
        return this_mag_2;
    }

    // The transverse component w.r.t. given axis.
    template <typename Value_2_>
    Value_ Perp(Vector3<Value_2_> const& vector) const {
        //return the transverse component(R in cylindrical coordinate system)
        return sqrt(Perp2(vector));
    }

    template <typename Value_2_>
    boca::Angle DeltaPhi(Vector3<Value_2_> const& vector) const {
        return Restrict(Phi() - vector.Phi());
    }

    template <typename Value_2_>
    boca::Angle DeltaR(Vector3<Value_2_> const& vector) const {
        //return deltaR with respect to v
        auto deta = Eta() - vector.Eta();
        auto dphi = Restrict(Phi() - vector.Phi());
        return sqrt(sqr(deta) + sqr(dphi));
    }

    boca::Angle DrEtaPhi(Vector3 const& vector) const {
        return DeltaR(vector);
    }

// // Unit vector parallel to this.
//     Vector3<double> Unit() const {
//         // return unit vector parallel to this.
//         ValueSquare tot2 = Mag2();
//         ValueInverse tot = tot2 > ValueSquare(0) ? 1. / sqrt(tot2) : 1. / Value_(1.);
//         return {x_ * tot, y_ * tot, z_ * tot};
//     }


    Vector3<double> Unit() const {
        return Unit(IsQuantity<Value_>());
    }

    Vector3<double> Unit(std::true_type) const {
        auto tot2 = Mag2();
        if (tot2 == ValueSquare(0)) return {x_.value(), y_.value(), z_.value()};
        auto tot = 1. / sqrt(tot2);
        return {x_ * tot, y_ * tot, z_ * tot};
    }

    Vector3<double> Unit(std::false_type) const {
        auto tot2 = Mag2();
        auto tot = tot2 > Value_(0) ? 1. / std::sqrt(tot2) : 1.;
        return {x_ * tot, y_ * tot, z_ * tot};
    }

// Vector orthogonal to this(Geant4).
    Vector3 Orthogonal() const {
        auto x = x_ < Value_(0) ? -x_ : x_;
        auto y = y_ < Value_(0) ? -y_ : y_;
        auto z = z_ < Value_(0) ? -z_ : z_;
        if (x < y) return x < z ? Vector3(Value_(0), z_, -y_) : Vector3(y_, -x_, Value_(0));
        else return y < z ? Vector3(-z_, Value_(0), x_) : Vector3(y_, -x_, Value_(0));
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
    double Tan2(Vector3 const& vector) {
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
        if (z_ == Value_(0)) return 0_rad;
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
        auto s = sin(angle);
        auto c = cos(angle);
        auto y = y_;
        y_ = c * y - s * z_;
        z_ = s * y + c * z_;
    }

// Rotates the Hep3Vector around the y-axis.
    void RotateY(boca::Angle const& angle) {
        //rotate vector around Y
        auto s = sin(angle);
        auto c = cos(angle);
        auto z = z_;
        z_ = c * z - s * x_;
        x_ = s * z + c * x_;
    }

// Rotates the Hep3Vector around the z-axis.
    void RotateZ(boca::Angle const& angle) {
        //rotate vector around Z
        auto s = sin(angle);
        auto c = cos(angle);
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
        } else if (z < Value_(0)) {
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

    Vector2<Value_> XYvector() const {
        return {x_, y_};
    }

    Vector2<boca::Angle> EtaPhiVector() const {
        return {Eta(), Phi()};
    }

    // Scale with scalar
    template <typename Value_2_>
    Vector3<ValueProduct<Value_2_>> Scale(Value_2_ const& scalar) const {
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    // Scalar product.
    template <typename Value_2_>
    ValueProduct<Value_2_> Dot(Vector3<Value_2_> const& vector) const {
        return x_ * vector.X() + y_ * vector.Y() + z_ * vector.Z();
    }

    // Cross product
    template <typename Value_2_>
    Vector3<ValueProduct<Value_2_>> Cross(Vector3<Value_2_> const& vector) const {
        return {y_ * vector.Z() - vector.Y()* z_, z_ * vector.X() - vector.Z()* x_, x_ * vector.Y() - vector.X()* y_};
    }

    // Triple product
    template <typename Value_2_, typename Value_3>
    ValueCubed<Value_2_, Value_3> Triple(Vector3<Value_2_> const& vector_1, Vector3<Value_3> const& vector_2) const {
        return Cross(vector_1) * vector_2;
    }

    // Addition.
    template <typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    Vector3& operator+=(Vector3<Value_2_> const& vector) {
        x_ += vector.x_;
        y_ += vector.y_;
        z_ += vector.z_;
        return *this;
    }

    // Subtraction
    template <typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    Vector3& operator-=(Vector3<Value_2_> const& vector) {
        x_ -= vector.x_;
        y_ -= vector.y_;
        z_ -= vector.z_;
        return *this;
    }

    // Scaling with real numbers
    template < typename Value_2_, typename = OnlyIfNotQuantity<Value_2_> >
    Vector3& operator*=(Value_2_ scalar) {
        x_ *= scalar;
        y_ *= scalar;
        z_ *= scalar;
        return *this;
    }

    /// division by scalar
    template < typename Value_2_, typename = OnlyIfNotQuantity<Value_2_> >
    Vector3& operator/=(Value_2_ scalar) {
        x_ /= scalar;
        y_ /= scalar;
        z_ /= scalar;
        return *this;
    }

    template <typename Value_2_>
    friend Vector3<ValueProduct<Value_2_>> operator^(Vector3 const& vector_1, Vector3<Value_2_> const& vector_2) {
        return vector_1.Cross(vector_2);
    }

    template <typename Value_2_>
    friend Vector3 <ValueQuotient<Value_2_>> operator/(Vector3 const& vector, Value_2_ const& scalar) {
        return vector.Scale(1. / scalar);
    }

    // Get components by index
    Value_ const& operator()(Dim3 dimension) const {
        //dereferencing operator const
        switch (dimension) {
        case Dim3::x :
            return x_;
        case Dim3::y :
            return y_;
        case Dim3::z :
            return z_;
        default :
            std::cout << "bad index(%d) returning 0 " << Name(dimension) << std::endl;
        }
        return x_;
    }

    // Set components by index.
    Value_& operator()(Dim3 dimension) {
        //dereferencing operator
        switch (dimension) {
        case Dim3::x :
            return x_;
        case Dim3::y :
            return y_;
        case Dim3::z :
            return z_;
        default :
            std::cout << "bad index(%d) returning &x_" <<  Name(dimension) << std::endl;
        }
        return x_;
    }

    Value_ const& operator[](Dim3 dimension) const {
        return operator()(dimension);
    }

    Value_& operator[](Dim3 dimension) {
        return operator()(dimension);
    }

    ConstIterator<boca::Vector3, Value_, Dim3> begin() const {
        return {this, Dim3::x};
    }

    ConstIterator<boca::Vector3, Value_, Dim3> end() const {
        return {this, Dim3::last};
    }

    Iterator<boca::Vector3, Value_, Dim3> begin() {
        return {this, Dim3::x};
    }

    Iterator<boca::Vector3, Value_, Dim3> end() {
        return {this, Dim3::last};
    }

    // Comparisons
    bool operator==(Vector3 const& vector) const {
        return vector.x_ == x_ && vector.y_ == y_ && vector.z_ == z_;
    }

    bool operator!=(Vector3 const& vector) const {
        return vector.x_ != x_ || vector.y_ != y_ || vector.z_ != z_;
    }

    bool operator<(Vector3 const& vector) const
    {
       return Mag2() < vector.Mag2();
    }

    bool operator>(Vector3 const& vector) const
    {
        return vector < *this;
    }

    bool operator<=(Vector3 const& vector) const
    {
        return !(*this > vector);
    }

    bool operator>=(Vector3 const& vector) const
    {
        return !(*this < vector);
    }

    // Unary minus
    Vector3 operator-() const {
        return { -x_, -y_, -z_};
    }

private:

    Value_ x_;

    Value_ y_;

    Value_ z_;

};

template <typename>
struct IsVector3 : std::false_type { };

template <typename Value>
struct IsVector3<Vector3<Value>> : std::true_type { };

template<typename Value>
using OnlyIfNotVector3 = typename std::enable_if < !IsVector3<Value>::value >::type;

// Scalar product of 3-vectors.
template <class Value, class Value_2_>
ValueProduct<Value, Value_2_> operator*(Vector3<Value> const& vector_1, Vector3<Value_2_> const& vector_2)
{
    return vector_1.Dot(vector_2);
}

// Scaling of 3-vectors with a real number
template < class Value, class Value_2_, typename = OnlyIfNotVector3<Value_2_> >
Vector3 <ValueProduct<Value, Value_2_>> operator*(Vector3<Value> const& vector, Value_2_ scalar)
{
    return vector.Scale(scalar);
}

template < class Value, class Value_2_, typename = OnlyIfNotVector3<Value_2_> >
Vector3 <ValueProduct<Value, Value_2_>> operator*(Value_2_ scalar, Vector3<Value> const& vector)
{
    return vector.Scale(scalar);
}

template <class Value_1, class Value_2_, class Value_3>
auto Triple(Vector3<Value_1> const& vector_1, Vector3<Value_2_> const& vector_2, Vector3<Value_3> const& vector_3)
{
    return vector_1.Triple(vector_2, vector_3);
}

template<typename Value_>
using GradedVector3 = GradedContainer<Vector3, Value_>;

}
