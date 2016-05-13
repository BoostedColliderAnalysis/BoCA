// Author: Pasha Murat , Peter Malzacher  12/02/99
// Jan Hajer 2015 (templates and units)

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

#include <climits>

#include "boca/math/Vector3.hh"

namespace boca
{

// Safe indexing of the coordinates when using with matrices, arrays, etc.
enum class LorentzDim
{
    x,
    y,
    z,
    t,
    last
};

std::string Name(LorentzDim dimension);

std::vector<LorentzDim> LorentzDimensions();

/**
 * @brief Copy of root::TLorentzVector in order to get rid of TObject which makes it unsuitable for heavy usage
 *
 */
template<typename Value_>
class LorentzVectorBase
{

public:

    using ValueSquare = boca::ValueSquare<Value_>;

    template<typename Value_2>
    using ValueProduct = boca::ValueProduct<Value_, Value_2>;

    template<typename Value_2>
    using ValueQuotient = ValueQuotient<Value_, Value_2>;

    template <typename> struct IsQuantity : std::false_type {};
    template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type {};

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value_, Value_2>::value >::type;

    template<typename Value_2>
    using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value_2>::value >::type;

    LorentzVectorBase() :
        vector_3_(),
        scalar_(Value_(0)) {}

// Constructor giving the components x, y, z, t.
    LorentzVectorBase(Value_ x, Value_ y, Value_ z, Value_ t) :
        vector_3_(x, y, z),
        scalar_(t) {}

// Constructor giving a 3-Vector and a time component.
    LorentzVectorBase(Vector3<Value_> vector3, Value_ t) :
        vector_3_(std::move(vector3)),
        scalar_(t) {}

    template<typename Value_2>
    LorentzVectorBase(LorentzVectorBase<Value_2> const& lorentz_vector) {
        vector_3_ = Vector3<Value_2>(lorentz_vector.Vector());
        scalar_ = Value_2(lorentz_vector.Scalar());
    }

// Set position and time.
    void SetX(Value_ x) {
        vector_3_.SetX(x);
    }
    void SetY(Value_ y) {
        vector_3_.SetY(y);
    }
    void SetZ(Value_ z) {
        vector_3_.SetZ(z);
    }
    void SetT(Value_ t) {
        scalar_ = t;
    }

// Set spatial component.
    void SetVect(Vector3<Value_> const& vector) {
        vector_3_ = vector;
    }

// Set spatial vector components in spherical coordinate system.
    void SetTheta(boca::Angle const& theta) {
        vector_3_.SetTheta(theta);
    }
    void SetPhi(boca::Angle const& phi) {
        vector_3_.SetPhi(phi);
    }
    void SetRho(Value_ rho) {
        vector_3_.SetMag(rho);
    }

// Setters to provide the functionality(but a more meanigful name) of
// the previous version eg SetV4... PsetV4...
    void SetXYZT(Value_ x, Value_ y, Value_ z, Value_ t) {
        vector_3_.SetXYZ(x, y, z);
        SetT(t);
    }

    void SetXYZM(Value_ x, Value_ y, Value_ z, Value_ mass) {
        if (mass >= Value_(0)) SetXYZT(x, y, z, sqrt(sqr(x) + sqr(y) + sqr(z) + sqr(mass)));
        else SetXYZT(x, y, z, sqrt(std::max((sqr(x) + sqr(y) + sqr(z) - sqr(mass)), ValueSquare(0))));
    }

// Set the transverse component of the spatial vector.
    void SetPerp(Value_ perp) {
        vector_3_.SetPerp(perp);
    }

    // Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)
    void SetVectMag(Vector3<Value_> const& spatial, Value_ magnitude) {
        SetXYZM(spatial.X(), spatial.Y(), spatial.Z(), magnitude);
    }

    void SetVectM(Vector3<Value_> const& spatial, Value_ mass) {
        SetVectMag(spatial, mass);
    }

// Get position and time.
    Value_ const& X() const {
        return vector_3_.X();
    }
    Value_ const& Y() const {
        return vector_3_.Y();
    }
    Value_ const& Z() const {
        return vector_3_.Z();
    }
    Value_ const& T() const {
        return scalar_;
    }

    Value_& X() {
        return vector_3_.X();
    }
    Value_& Y() {
        return vector_3_.Y();
    }
    Value_& Z() {
        return vector_3_.Z();
    }
    Value_& T() {
        return scalar_;
    }

// Get spatial component.
//     Vector3<Value> Vector() const {
//         return vector_3_;
//     }
    Vector3<Value_> const& Vector() const {
        return vector_3_;
    }

    Vector3<Value_> & Vector() {
      return vector_3_;
    }

// Get spatial vector components in spherical coordinate system.
    boca::Angle Theta() const {
        return vector_3_.Theta();
    }
    Value_ CosTheta() const {
        return vector_3_.CosTheta();
    }
    //returns phi from -pi to pi
    boca::Angle Phi() const {
        return vector_3_.Phi();
    }
    Value_ Rho() const {
        return vector_3_.Mag();
    }

// Getters into an arry
// no checking!
//     void GetXYZT(Value* carray) const;

// Transverse component of the spatial vector squared.
    ValueSquare Perp2() const {
        return vector_3_.Perp2();
    }

    Value_ Perp() const {
        return vector_3_.Perp();
    }

    // Transverse component of the spatial vector w.r.t. given axis squared.
    template <typename Value_2>
    ValueSquare Perp2(Vector3<Value_2> const& vector) const {
        return vector_3_.Perp2(vector);
    }

    template <typename Value_2>
    Value_ Perp(Vector3<Value_2> const& vector) const {
        return vector_3_.Perp(vector);
    }

    boca::Angle DeltaPhi(LorentzVectorBase const& lorentz_vector) const {
        return RestrictPhi(Phi() - lorentz_vector.Phi());
    }

    boca::Angle DeltaR(LorentzVectorBase const& lorentz_vector) const {
        auto delta_eta = Eta() - lorentz_vector.Eta();
        auto delta_phi = RestrictPhi(Phi() - lorentz_vector.Phi());
        return sqrt(sqr(delta_eta) + sqr(delta_phi));
    }

    boca::Angle DrEtaPhi(LorentzVectorBase const& lorentz_vector) const {
        return DeltaR(lorentz_vector);
    }

    Vector2<boca::Angle> EtaPhiVector() {
        return {Eta(), Phi()};
    }

// Angle wrt. another vector.
    boca::Angle Angle(Vector3<Value_> const& vector) const {
        return vector_3_.Angle(vector);
    }

    // Angle wrt. another vector.
    boca::Angle Angle(LorentzVectorBase const& vector) const {
        return vector_3_.Angle(vector.Vector());
    }

// Invariant mass squared.
    ValueSquare Mag2() const {
        return sqr(T()) - vector_3_.Mag2();
    }
// Invariant mass. If mag2() is negative then -sqrt(-mag2()) is returned.
    Value_ Mag() const {
        auto mag2 = Mag2();
        return mag2 < ValueSquare(0) ? -sqrt(-mag2) : sqrt(mag2);
    }

    double Beta() const {
        return vector_3_.Mag() / scalar_;
    }

    double Gamma() const {
        auto beta = Beta();
        return 1. / std::sqrt(1. - sqr(beta));
    }


// Returns t +/- z.
// Related to the positive/negative light-cone component,
// which some define this way and others define as(t +/- z)/sqrt(2)
//Member functions Plus() and Minus() return the positive and negative
//light-cone components:
//
// Value pcone = v.Plus();
// Value mcone = v.Minus();
//
//CAVEAT: The values returned are T{+,-}Z. It is known that some authors
//find it easier to define these components as(T{+,-}Z)/sqrt(2). Thus
//check what definition is used in the physics you're working in and adapt
//your code accordingly.
    Value_ Plus() const {
        return T() + Z();
    }
    Value_ Minus() const {
        return T() - Z();
    }


    // Returns the spatial components divided by the time component.
    Vector3<double> BoostVector() const {
        if (T() == Value_(0)) {
            if (Rho() > Value_(0)) std::cout << "boostVector computed for LorentzVector with t=0 -- infinite result" << std::endl;
            return {};
        }
        return Vector3<double>(X() / T(), Y() / T(), Z() / T());
    }

    /**
     * Boost from reference frame into this vector's rest
     * frame: \f$-\frac{\vec{x}}{t}\f$.
     */
    Vector3<double> BoostIntoRestFrame() const {
        return -BoostVector();
    }

// Lorentz boost.
    void Boost(Vector3<double> const& boost) {
      //Boost this Lorentz vector
      auto mag_2 = boost.Mag2();
      auto gamma = 1. / std::sqrt(1. - mag_2);
      auto bp = boost * Vector();
      auto gamma2 = mag_2 > 0. ? (gamma - 1.) / mag_2 : 0.;
      Vector() = Vector() + gamma2 * bp * boost + gamma * boost * T();
      T() = gamma * (T() + bp);
    }

    LorentzVectorBase<Value_> Boosted(Vector3<double> const& boost) const {
        //Boost this Lorentz vector
        auto mag_2 = boost.Mag2();
        auto gamma = 1. / std::sqrt(1. - mag_2);
        auto gamma2 = mag_2 > 0. ? (gamma - 1.) / mag_2 : 0.;
        auto bp = boost * Vector();
        LorentzVectorBase<Value_> lorentz_vector;
        lorentz_vector.Vector() = Vector() + gamma2 * bp * boost + gamma * boost * T();
        lorentz_vector.SetT(gamma * (T() + bp));
        return lorentz_vector;
    }

// Returns the rapidity, i.e. 0.5*ln((E+pz)/(E-pz))
    boca::Angle Rapidity() const {
        //return rapidity
        return 0.5 * units::log(static_cast<double>((T() + Z()) / (T() - Z())));
    }

    /// Rapidity with respect to another vector
    boca::Angle Rapidity(Vector3<double> const& ref) const {
        auto r = ref.Mag2();
        if (r == 0) {
            std::cout << "A zero vector used as reference to LorentzVector rapidity" << std::endl;
            return 0;
        }
        auto vdotu = Vector().Dot(ref) / std::sqrt(r);
        if (vdotu == Value_(0)) return 0_rad;
        if (T() <= Value_(0)) std::cout << "Tried to take rapidity of negative-energy Lorentz vector" << std::endl;
        auto pt = sqrt(units::max(sqr(T() * std::numeric_limits<double>::epsilon()), Perp2(ref) + Mag2()));
        auto rap = units::log(((T() + abs(Z())) / pt).value());
        return Z() > Value_(0) ? rap : -rap;
    }


// Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))
    boca::Angle Eta() const {
        return PseudoRapidity();
    }

    boca::Angle Rap() const {
        return Rapidity();
    }

    boca::Angle PseudoRapidity() const {
        return vector_3_.PseudoRapidity();
    }

// Rotate the spatial component around the x-axis.
    void RotateX(Value_ angle) {
        vector_3_.RotateX(angle);
    }

// Rotate the spatial component around the y-axis.
    void RotateY(Value_ angle) {
        vector_3_.RotateY(angle);
    }

// Rotate the spatial component around the z-axis.
    void RotateZ(Value_ angle) {
        vector_3_.RotateZ(angle);
    }

// Rotates the reference frame from Uz to newUz(unit vector).
    void RotateUz(Vector3<Value_>& newUzVector) {
        vector_3_.RotateUz(newUzVector);
    }

    // Scalar product.
    template <typename Value_2>
    LorentzVectorBase<ValueProduct<Value_2>> Scale(Value_2 const& scalar) const {
        return {scalar * X(), scalar * Y(), scalar * Z(), scalar * T()};
    }

    // Scalar product.
    template <typename Value_2>
    ValueProduct<Value_2> Dot(LorentzVectorBase<Value_2> const& lorentz_vector) const {
        return T() * lorentz_vector.T() - Vector().Dot(lorentz_vector.Vector());
    }

    // Scalar product.
    template <typename Value_2>
    ValueProduct<Value_2> Euclidean(LorentzVectorBase<Value_2> const& lorentz_vector) const {
      return T() * lorentz_vector.T() + Vector().Dot(lorentz_vector.Vector());
    }

    // Get components by index.
    Value_ const& operator()(LorentzDim i) const {
        //dereferencing operatorconst
        switch (i) {
        case LorentzDim::x : return vector_3_(Dim3::x);
        case LorentzDim::y : return vector_3_(Dim3::y);
        case LorentzDim::z : return vector_3_(Dim3::z);
        case LorentzDim::t : return scalar_;
        default: std::cout << "bad index(%d) returning 0 " << Name(i) << std::endl;
        }
        return vector_3_(Dim3::x);
    }

    Value_ const& operator[](LorentzDim i) const {
        return (*this)(i);
    }

    // Set components by index.
    Value_& operator()(LorentzDim i) {
        //dereferencing operator
        switch (i) {
        case LorentzDim::x : return vector_3_(Dim3::x);
        case LorentzDim::y : return vector_3_(Dim3::y);
        case LorentzDim::z : return vector_3_(Dim3::z);
        case LorentzDim::t : return scalar_;
        default:  std::cout << "bad index(%d) returning &e_ " << Name(i) << std::endl;
        }
        return scalar_;
    }

    Value_& operator[](LorentzDim i) {
        return (*this)(i);
    }

    ConstIterator<Vector3, Value_, LorentzDim> begin() const {
        return {this, LorentzDim::x};
    }

    ConstIterator<Vector3, Value_, LorentzDim> end() const {
        return {this, LorentzDim::last};
    }

    Iterator<Vector3, Value_, LorentzDim> begin() {
        return {this, LorentzDim::x};
    }

    Iterator<Vector3, Value_, LorentzDim> end() {
        return {this, LorentzDim::last};
    }

    // Additions.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase operator+(const LorentzVectorBase<Value_2>& lorentz_vector) const {
        return {vector_3_ + lorentz_vector.Vector(), scalar_ + lorentz_vector.T()};
    }

    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase& operator+=(LorentzVectorBase<Value_2> const& lorentz_vector) {
        vector_3_ += lorentz_vector.Vector();
        scalar_ += lorentz_vector.T();
        return *this;
    }

    // Subtractions.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase operator-(LorentzVectorBase<Value_2> const& lorentz_vector) const {
        return {vector_3_ - lorentz_vector.Vector(), scalar_ - lorentz_vector.T()};
    }

    // Divison by scalar
    template <typename Value_2>
    LorentzVectorBase<ValueQuotient<Value_2>> operator/(Value_2 const& scalar) const {
        return Scale(1. / scalar);
    }

    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase& operator-=(LorentzVectorBase<Value_2> const& lorentz_vector) {
        vector_3_ -= lorentz_vector.Vector();
        scalar_ -= lorentz_vector.T();
        return *this;
    }

    // Unary minus.
    LorentzVectorBase operator-() const {
        return { -X(), -Y(), -Z(), -T()};
    }

    template <typename Value_2, typename = OnlyIfNotQuantity<Value_2>>
    LorentzVectorBase& operator*=(Value_2 scalar) {
        vector_3_ *= scalar;
        scalar_ *= scalar;
        return *this;
    }

    template <typename Value_2, typename = OnlyIfNotQuantity<Value_2>>
    LorentzVectorBase& operator/=(Value_2 scalar) {
        vector_3_ /= scalar;
        scalar_ /= scalar;
        return *this;
    }

    // Comparisons.
    bool operator==(LorentzVectorBase const& lorentz_vector) const {
        return Vector() == lorentz_vector.Vector() && T() == lorentz_vector.T();
    }

    bool operator!=(LorentzVectorBase const& lorentz_vector) const {
        return Vector() != lorentz_vector.Vector() || T() != lorentz_vector.T();
    }

protected:

    // 3 vector component
    Vector3<Value_> vector_3_;

    // time or energy of(x,y,z,t) or(px,py,pz,e)
    Value_ scalar_;

};

// template <typename>
// struct IsLorentzVectorBase : std::false_type {};
//
// template <typename Value>
// struct IsLorentzVectorBase<LorentzVectorBase<Value>> : std::true_type {};

// template<typename Value>
// using OnlyIfNotLorentzVectorBase = typename std::enable_if < !IsLorentzVectorBase<Value>::value >::type;

template<typename Value>
using OnlyIfNotLorentzVectorBase = typename std::enable_if<std::is_base_of<LorentzVectorBase<Value>, Value>::value>::type;

// Scalar product of lorentzvectors.
template <class Value, class Value_2>
ValueProduct<Value, Value_2> operator*(LorentzVectorBase<Value> const& lorentz_vector_1, LorentzVectorBase<Value_2> const& lorentz_vector_2)
{
    return lorentz_vector_1.Dot(lorentz_vector_2);
}

// Scaling of lorentzvectors with a real number
template < class Value, class Value_2, typename = OnlyIfNotLorentzVectorBase<Value_2> >
LorentzVectorBase <ValueProduct<Value, Value_2>> operator*(LorentzVectorBase<Value> const& lorentz_vector, Value_2 scalar)
{
    return lorentz_vector.Scale(scalar);
}

template < class Value, class Value_2, typename = OnlyIfNotLorentzVectorBase<Value> >
LorentzVectorBase <ValueProduct<Value, Value_2>> operator*(Value scalar, LorentzVectorBase<Value_2> const& lorentz_vector)
{
    return lorentz_vector.Scale(scalar);
}

}


