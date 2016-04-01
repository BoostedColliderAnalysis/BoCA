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

#include <limits.h>

#include "math/Vector3.hh"

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
template<typename Value>
class LorentzVectorBase
{

public:

    using ValueSquare = boca::ValueSquare<Value>;

    template<typename Value_2>
    using ValueProduct = boca::ValueProduct<Value, Value_2>;

    template<typename Value_2>
    using ValueQuotient = ValueQuotient<Value, Value_2>;

    template <typename> struct IsQuantity : std::false_type {};
    template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type {};

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value, Value_2>::value >::type;

    template<typename Value_2>
    using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value_2>::value >::type;

    LorentzVectorBase() :
        vector_3_(),
        scalar_(Value(0)) {}

// Constructor giving the components x, y, z, t.
    LorentzVectorBase(Value x, Value y, Value z, Value t) :
        vector_3_(x, y, z),
        scalar_(t) {}

// Constructor giving a 3-Vector and a time component.
    LorentzVectorBase(Vector3<Value> vector3, Value t) :
        vector_3_(std::move(vector3)),
        scalar_(t) {}

    template<typename Value_2>
    LorentzVectorBase(LorentzVectorBase<Value_2> const& lorentz_vector) {
        vector_3_ = Vector3<Value_2>(lorentz_vector.Vector());
        scalar_ = Value_2(lorentz_vector.Scalar());
    }

// Set position and time.
    void SetX(Value x) {
        vector_3_.SetX(x);
    }
    void SetY(Value y) {
        vector_3_.SetY(y);
    }
    void SetZ(Value z) {
        vector_3_.SetZ(z);
    }
    void SetT(Value t) {
        scalar_ = t;
    }

// Set spatial component.
    void SetVect(Vector3<Value> const& vector) {
        vector_3_ = vector;
    }

// Set spatial vector components in spherical coordinate system.
    void SetTheta(boca::Angle theta) {
        vector_3_.SetTheta(theta);
    }
    void SetPhi(boca::Angle phi) {
        vector_3_.SetPhi(phi);
    }
    void SetRho(Value rho) {
        vector_3_.SetMag(rho);
    }

// Setters to provide the functionality(but a more meanigful name) of
// the previous version eg SetV4... PsetV4...
    void SetXYZT(Value x, Value y, Value z, Value t) {
        vector_3_.SetXYZ(x, y, z);
        SetT(t);
    }

    void SetXYZM(Value x, Value y, Value z, Value m) {
        if (m >= Value(0)) SetXYZT(x, y, z, sqrt(sqr(x) + sqr(y) + sqr(z) + sqr(m)));
        else SetXYZT(x, y, z, sqrt(std::max((sqr(x) + sqr(y) + sqr(z) - sqr(m)), ValueSquare(0))));
    }

// Set the transverse component of the spatial vector.
    void SetPerp(Value perp) {
        vector_3_.SetPerp(perp);
    }

    // Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)
    void SetVectMag(Vector3<Value> const& spatial, Value magnitude) {
        SetXYZM(spatial.X(), spatial.Y(), spatial.Z(), magnitude);
    }

    void SetVectM(Vector3<Value> const& spatial, Value mass) {
        SetVectMag(spatial, mass);
    }

// Get position and time.
    Value X() const {
        return vector_3_.X();
    }
    Value Y() const {
        return vector_3_.Y();
    }
    Value Z() const {
        return vector_3_.Z();
    }
    Value T() const {
        return scalar_;
    }

    Value& X() {
        return vector_3_.X();
    }
    Value& Y() {
        return vector_3_.Y();
    }
    Value& Z() {
        return vector_3_.Z();
    }
    Value& T() {
        return scalar_;
    }

// Get spatial component.
    Vector3<Value> Vect() const {
        return vector_3_;
    }
    Vector3<Value> Vector() const {
        return vector_3_;
    }

// Get spatial vector components in spherical coordinate system.
    boca::Angle Theta() const {
        return vector_3_.Theta();
    }
    Value CosTheta() const {
        return vector_3_.CosTheta();
    }
    //returns phi from -pi to pi
    boca::Angle Phi() const {
        return vector_3_.Phi();
    }
    Value Rho() const {
        return vector_3_.Mag();
    }

// Getters into an arry
// no checking!
//     void GetXYZT(Value* carray) const;

// Transverse component of the spatial vector squared.
    ValueSquare Perp2() const {
        return vector_3_.Perp2();
    }

    Value Perp() const {
        return vector_3_.Perp();
    }

    // Transverse component of the spatial vector w.r.t. given axis squared.
    template <typename Value_2>
    ValueSquare Perp2(Vector3<Value_2> const& vector) const {
        return vector_3_.Perp2(vector);
    }

    template <typename Value_2>
    Value Perp(Vector3<Value_2> const& vector) const {
        return vector_3_.Perp(vector);
    }

    boca::Angle DeltaPhi(LorentzVectorBase const& lorentz_vector) const {
        return RestrictPhi(Phi() - lorentz_vector.Phi());
    }

    boca::Angle DeltaR(LorentzVectorBase const& lorentz_vector) const {
        boca::Angle delta_eta = Eta() - lorentz_vector.Eta();
        boca::Angle delta_phi = RestrictPhi(Phi() - lorentz_vector.Phi());
        return sqrt(sqr(delta_eta) + sqr(delta_phi));
    }

    boca::Angle DrEtaPhi(LorentzVectorBase const& lorentz_vector) const {
        return DeltaR(lorentz_vector);
    }

    Vector2<boca::Angle> EtaPhiVector() {
        return {Eta(), Phi()};
    }

// Angle wrt. another vector.
    boca::Angle Angle(Vector3<Value> const& vector) const {
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
    Value Mag() const {
        ValueSquare mag2 = Mag2();
        return mag2 < ValueSquare(0) ? -sqrt(-mag2) : sqrt(mag2);
    }

    double Beta() const {
        return vector_3_.Mag() / scalar_;
    }

    double Gamma() const {
        double beta = Beta();
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
    Value Plus() const {
        return T() + Z();
    }
    Value Minus() const {
        return T() - Z();
    }


    // Returns the spatial components divided by the time component.
    Vector3<double> BoostVector() const {
        if (T() == Value(0)) {
            if (Rho() > Value(0)) std::cout << "boostVector computed for LorentzVector with t=0 -- infinite result" << std::endl;
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
    void Boost(double x, double y, double z) {
        //Boost this Lorentz vector
        double b2 = sqr(x) + sqr(y) + sqr(z);
        double gamma = 1. / std::sqrt(1. - b2);
        Value bp = x * X() + y * Y() + z * Z();
        double gamma2 = b2 > 0. ? (gamma - 1.) / b2 : 0.;
        SetX(X() + gamma2 * bp * x + gamma * x * T());
        SetY(Y() + gamma2 * bp * y + gamma * y * T());
        SetZ(Z() + gamma2 * bp * z + gamma * z * T());
        SetT(gamma * (T() + bp));
    }

    void Boost(Vector3<double> const& b) {
        Boost(b.X(), b.Y(), b.Z());
    }

    // Lorentz boost.
    LorentzVectorBase<Value> Boosted(double x, double y, double z) const {
        //Boost this Lorentz vector
        double b2 = sqr(x) + sqr(y) + sqr(z);
        double gamma = 1. / std::sqrt(1. - b2);
        double gamma2 = b2 > 0. ? (gamma - 1.) / b2 : 0.;
        Value bp = x * X() + y * Y() + z * Z();
        LorentzVectorBase<Value> lorentz_vector;
        lorentz_vector.SetX(X() + gamma2 * bp * x + gamma * x * T());
        lorentz_vector.SetY(Y() + gamma2 * bp * y + gamma * y * T());
        lorentz_vector.SetZ(Z() + gamma2 * bp * z + gamma * z * T());
        lorentz_vector.SetT(gamma * (T() + bp));
        return lorentz_vector;
    }

    LorentzVectorBase<Value> Boosted(Vector3<double> const& b) const {
        return Boosted(b.X(), b.Y(), b.Z());
    }

// Returns the rapidity, i.e. 0.5*ln((E+pz)/(E-pz))
    boca::Angle Rapidity() const {
        //return rapidity
        return 0.5 * units::log(double((T() + Z()) / (T() - Z())));
    }


    /// Rapidity with respect to another vector
    boca::Angle Rapidity(Vector3<double> const& ref) const {
        double r = ref.Mag2();
        if (r == 0) {
            std::cout << "A zero vector used as reference to LorentzVector rapidity" << std::endl;
            return 0;
        }
        Value vdotu = Vect().Dot(ref) / std::sqrt(r);
        if (vdotu == Value(0)) return 0_rad;
        if (T() <= Value(0)) std::cout << "Tried to take rapidity of negative-energy Lorentz vector" << std::endl;
        Value pt = sqrt(units::max(sqr(T() * std::numeric_limits<double>::epsilon()), Perp2(ref) + Mag2()));
        boca::Angle rap = units::log(((T() + abs(Z())) / pt).value());
        return Z() > Value(0) ? rap : -rap;
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
    void RotateX(Value angle) {
        vector_3_.RotateX(angle);
    }

// Rotate the spatial component around the y-axis.
    void RotateY(Value angle) {
        vector_3_.RotateY(angle);
    }

// Rotate the spatial component around the z-axis.
    void RotateZ(Value angle) {
        vector_3_.RotateZ(angle);
    }

// Rotates the reference frame from Uz to newUz(unit vector).
    void RotateUz(Vector3<Value>& newUzVector) {
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
        return T() * lorentz_vector.T() - Vect().Dot(lorentz_vector.Vect());
    }

    // Get components by index.
    Value operator()(LorentzDim i) const {
        //dereferencing operatorconst
        switch (i) {
        case LorentzDim::x : return vector_3_(Dim3::x);
        case LorentzDim::y : return vector_3_(Dim3::y);
        case LorentzDim::z : return vector_3_(Dim3::z);
        case LorentzDim::t : return scalar_;
        default: std::cout << "bad index(%d) returning 0 " << Name(i) << std::endl;
        }
        return Value(0);
    }

    Value operator[](LorentzDim i) const {
        return (*this)(i);
    }

    // Set components by index.
    Value& operator()(LorentzDim i) {
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

    Value& operator[](LorentzDim i) {
        return (*this)(i);
    }

    ConstIterator<Vector3, Value, LorentzDim> begin() const {
        return {this, LorentzDim::x};
    }

    ConstIterator<Vector3, Value, LorentzDim> end() const {
        return {this, LorentzDim::last};
    }

    Iterator<Vector3, Value, LorentzDim> begin() {
        return {this, LorentzDim::x};
    }

    Iterator<Vector3, Value, LorentzDim> end() {
        return {this, LorentzDim::last};
    }

    // Additions.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase operator+(const LorentzVectorBase<Value_2>& lorentz_vector) const {
        return {vector_3_ + lorentz_vector.Vect(), scalar_ + lorentz_vector.T()};
    }

    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase& operator+=(LorentzVectorBase<Value_2> const& lorentz_vector) {
        vector_3_ += lorentz_vector.Vect();
        scalar_ += lorentz_vector.T();
        return *this;
    }

    // Subtractions.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase operator-(LorentzVectorBase<Value_2> const& lorentz_vector) const {
        return {vector_3_ - lorentz_vector.Vect(), scalar_ - lorentz_vector.T()};
    }

    // Divison by scalar
    template <typename Value_2>
    LorentzVectorBase<ValueQuotient<Value_2>> operator/(Value_2 const& scalar) const {
        return Scale(1. / scalar);
    }

    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase& operator-=(LorentzVectorBase<Value_2> const& lorentz_vector) {
        vector_3_ -= lorentz_vector.Vect();
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
        return Vect() == lorentz_vector.Vect() && T() == lorentz_vector.T();
    }

    bool operator!=(LorentzVectorBase const& lorentz_vector) const {
        return Vect() != lorentz_vector.Vect() || T() != lorentz_vector.T();
    }

protected:

    // 3 vector component
    Vector3<Value> vector_3_;

    // time or energy of(x,y,z,t) or(px,py,pz,e)
    Value scalar_;

};

template <typename>
struct IsLorentzVectorBase : std::false_type {};

template <typename Value>
struct IsLorentzVectorBase<LorentzVectorBase<Value>> : std::true_type {};

template<typename Value>
using OnlyIfNotLorentzVectorBase = typename std::enable_if < !IsLorentzVectorBase<Value>::value >::type;

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


