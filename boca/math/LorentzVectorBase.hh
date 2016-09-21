#pragma once

#include <climits>

#include "boca/math/Vector3.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Lorentz Dimensions
 */
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
 * @ingroup Math
 * @brief Lorentz Vector
 */
template<typename Value_>
class LorentzVectorBase : public boost::totally_ordered<LorentzVectorBase<Value_>>
            , public boost::additive<LorentzVectorBase<Value_>>
            , private Vector3<Value_>
{

    using ValueSquare = boca::ValueSquare<Value_>;

    template<typename Value_2>
    using ValueProduct = boca::ValueProduct<Value_, Value_2>;

    template<typename Value_2>
    using ValueQuotient = ValueQuotient<Value_, Value_2>;

    template <typename> struct IsQuantity : std::false_type {};
    template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type {};

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value_, Value_2>::value >::type;

protected:

    template<typename Value_2>
    using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value_2>::value >::type;

public:

    /**
     * @name Constructor
     * @{
     */

    /**
     * @brief Default constructor
     */
    LorentzVectorBase() :
        Vector3<Value_>(),
        scalar_(Value_(0)) {}

    /**
     * @brief Constructor giving the components x, y, z, t.
     */
    LorentzVectorBase(Value_ x, Value_ y, Value_ z, Value_ t) :
        Vector3<Value_>(x, y, z),
        scalar_(t) {}

    /**
     * @brief Constructor giving a 3-Vector and a time component.
     */
    LorentzVectorBase(Vector3<Value_> const &vector3, Value_ const &t) :
        Vector3<Value_>(vector3),
        scalar_(t) {}

    /**
     * @brief copy constructor with casting
     */
    template<typename Value_2>
    LorentzVectorBase(LorentzVectorBase<Value_2> const &lorentz_vector)
    {
        Vector3<Value_>(lorentz_vector.Vector());
        scalar_(lorentz_vector.Scalar());
    }
    //@}

    /**
     * @name Setter
     * @{
     */

    using Vector3<Value_>::SetTheta;

    using Vector3<Value_>::SetPhi;

    /**
     * @brief Set spacial magnitude
     */
    void SetRho(Value_ rho)
    {
        Vector().SetMag(rho);
    }

    /**
     * @brief Set components
     */
    void SetXYZT(Value_ x, Value_ y, Value_ z, Value_ t)
    {
        Vector() = {x, y, z};
        T() = t;
    }

    /**
     * @brief Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)
     */
    void SetVectMag(Vector3<Value_> const &spatial, Value_ magnitude)
    {
        Vector() = spatial;
        T() = magnitude >= Value_(0)  ?  sqrt(sqr(spatial) + sqr(magnitude)) : sqrt(std::max((sqr(spatial) - sqr(magnitude)), ValueSquare(0)));
    }

    /**
     * @brief Set x,  y,  z and magnitude
     */
    void SetXYZM(Value_ x, Value_ y, Value_ z, Value_ mass)
    {
        SetXYZM(x,  y,  z , mass);
    }

    /**
     * @brief Set x,  y,  z and magnitude
     */
    void SetVectM(Vector3<Value_> const &spatial, Value_ mass)
    {
        SetVectMag(spatial, mass);
    }

    /**
     * @brief Set the transverse component of the spatial vector.
     */
    using Vector3<Value_>::SetPerp;

    //@}

    /**
     * @name Accessors and Getter
     * @{
     */

    /**
     * @brief spatial component.
     */
    Vector3<Value_> Vector() const
    {
        return *this;
    }

    /**
     * @brief spatial component.
     */
    Vector3<Value_> &Vector()
    {
        return *this;
    }

    /**
     * @brief t
     */
    Value_ &Scalar()
    {
        return scalar_;
    }

    /**
     * @brief t
     */
    Value_ Scalar() const
    {
        return scalar_;
    }

    using Vector3<Value_>::X;

    using Vector3<Value_>::Y;

    using Vector3<Value_>::Z;

    /**
     * @brief t
     */
    Value_ T() const
    {
        return scalar_;
    }

    /**
     * @brief t
     */
    Value_ &T()
    {
        return scalar_;
    }
    //@}

    /**
     * @name spatial vector components in spherical coordinate system.
     * @{
     */

    using Vector3<Value_>::Theta;

    using Vector3<Value_>::CosTheta;

    using Vector3<Value_>::SinTheta;

    using Vector3<Value_>::SinTheta2;

    using Vector3<Value_>::Phi;

    using Vector3<Value_>::DeltaPhi;

    using Vector3<Value_>::DeltaR;

    using Vector3<Value_>::Angle;

    /**
      * @brief Angle wrt. another vector.
      */
    boca::Angle Angle(LorentzVectorBase const &vector) const
    {
        return Angle(vector.Vector());
    }

    /**
     * @brief Returns the rapidity, i.e. 0.5*ln((E+pz)/(E-pz))
     */
    boca::Angle Rapidity() const
    {
        return 0.5 * units::log(static_cast<double>(Plus() / Minus()));
    }

    /**
     * @brief Rapidity with respect to another vector
     */
    boca::Angle Rapidity(Vector3<double> const &vector) const
    {
        auto r = vector.Mag2();
        if (r == 0) {
            std::cout << "A zero vector used as reference to LorentzVector rapidity" << std::endl;
            return 0_rad;
        }
        auto vdotu = Vector().Dot(vector) / std::sqrt(r);
        if (vdotu == Value_(0)) return 0_rad;
        if (T() <= Value_(0)) std::cout << "Tried to take rapidity of negative-energy Lorentz vector" << std::endl;
        auto pt = sqrt(units::max(sqr(T() * std::numeric_limits<double>::epsilon()), Perp2(vector) + Mag2()));
        auto rap = units::log(((T() + abs(Z())) / pt).value());
        return Z() > Value_(0) ? rap : -rap;
    }

    using Vector3<Value_>::Eta;

    /**
     * @brief Rapidity
     */
    boca::Angle Rap() const
    {
        return Rapidity();
    }

    using Vector3<Value_>::PseudoRapidity;

    //@}

    /**
     * @name Magnitudes
     * @{
     */

    /**
     * @brief spacial radius
     */
    ValueSquare Rho2() const
    {
        return Vector().Mag2();
    }

    /**
     * @brief spacial radius
     */
    Value_ Rho() const
    {
        return Vector().Mag();
    }

    using Vector3<Value_>::Perp2;

    using Vector3<Value_>::Perp;

    /**
     * @brief Invariant mass squared.
     */
    ValueSquare Mag2() const
    {
        return sqr(T()) - Rho2();
    }

    /**
     * @brief Invariant mass. If mag2() is negative then -sqrt(-mag2()) is returned.
     */
    Value_ Mag() const
    {
        auto mag2 = Mag2();
        return mag2 < ValueSquare(0) ? -sqrt(-mag2) : sqrt(mag2);
    }

    /**
    * @brief transvere magnitude square
    */
    ValueSquare MagT2() const
    {
        return sqr(T()) - sqr(Z());
    }

    /**
    * @brief transvere magnitude
    */
    Value_ MagT() const
    {
        auto mt2 = MagT2();
        return mt2 < ValueSquare(0) ? -sqrt(-mt2) : sqrt(mt2);
    }

    /**
    * @brief transvere scalar square
    */
    ValueSquare ScalarT2() const
    {
        return sqr(T()) * SinTheta2();
    }

    /**
    * @brief transvere scalar square
    */
    Value_ ScalarT() const
    {
        return T() < Value_(0) ? -sqrt(ScalarT2()) : sqrt(ScalarT2());
    }

    /**
    * @brief Transverse scalar squared w.r.t. given axis
    */
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    EnergySquare ScalarT2(Vector3<Value> const& vector) const {
        auto pt2 = Vector().Perp2(vector);
        auto pv = Vector().Dot(vector.Unit());
        return pt2 == ValueSquare(0) ? ValueSquare(0) : sqr(T()) * pt2 / (pt2 + sqr(pv));
    }

    /**
    * @brief Transverse scalar w.r.t. given axis
    */
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    boca::Energy ScalarT(Vector3<Value> const& vector) const {
        return T() < Value_(0) ? -sqrt(Et2(vector)) : sqrt(Et2(vector));
    }

    /**
     * @brief beta
     */
    double Beta() const
    {
        return Rho() / Scalar();
    }

    /**
     * @brief gamma
     */
    double Gamma() const
    {
        return 1. / std::sqrt(1. - sqr(Beta()));
    }

    /**
     * @brief t + z
     *
     * Related to the positive/negative light-cone component, which some define this way and others define as(t +/- z)/sqrt(2).
     * Member functions Plus() and Minus() return the positive and negative light-cone components:
     */
    Value_ Plus() const
    {
        return T() + Z();
    }

    /**
     * @brief t - z
     *
     * The values returned are T{+,-}Z. It is known that some authors find it easier to define these components as(T{+,-}Z)/sqrt(2).
     * Thus check what definition is used in the physics you're working in and adapt your code accordingly
     */
    Value_ Minus() const
    {
        return T() - Z();
    }
    //@}

    /**
     * @name Vectors
     * @{
     */

    /**
     * @brief spatial components divided by the time component.
     */
    Vector3<double> BoostVector() const
    {
        if (T() == Value_(0)) {
            if (Rho() > Value_(0)) std::cout << "boostVector computed for LorentzVector with t=0 -- infinite result" << std::endl;
            return {};
        }
        return Vector() / T();
    }

    using Vector3<Value_>::EtaPhiVector;

    /**
     * Boost from reference frame into this vector's rest
     * frame: \f$-\frac{\vec{x}}{t}\f$.
     */
    Vector3<double> BoostIntoRestFrame() const
    {
        return -BoostVector();
    }

    /**
     * @brief Lorentz boost.
     */
    LorentzVectorBase<Value_> Boosted(Vector3<double> const &boost) const
    {
        //Boost this Lorentz vector
        auto mag_2 = boost.Mag2();
        auto gamma = 1. / std::sqrt(1. - mag_2);
        auto gamma2 = mag_2 > 0. ? (gamma - 1.) / mag_2 : 0.;
        auto bp = boost * Vector();
        auto lorentz_vector = LorentzVectorBase<Value_> {};
        lorentz_vector.Vector() = Vector() + gamma2 * bp * boost + gamma * boost * T();
        lorentz_vector.T() = gamma * (T() + bp);
        return lorentz_vector;
    }
    //@}

    /**
     * @name Rotation
     * @{
     */

    /**
     * @brief Lorentz boost.
     */
    void Boost(Vector3<double> const &boost)
    {
        //Boost this Lorentz vector
        auto mag_2 = boost.Mag2();
        auto gamma = 1. / std::sqrt(1. - mag_2);
        auto bp = boost * Vector();
        auto gamma2 = mag_2 > 0. ? (gamma - 1.) / mag_2 : 0.;
        Vector() = Vector() + gamma2 * bp * boost + gamma * boost * T();
        T() = gamma * (T() + bp);
    }

    using Vector3<Value_>::RotateX;

    using Vector3<Value_>::RotateY;

    using Vector3<Value_>::RotateZ;

    using Vector3<Value_>::RotateUz;

    //@}

    /**
     * @name Products
     * @{
     */

    /**
     * @brief Scale
     */
    template <typename Value_2>
    LorentzVectorBase<ValueProduct<Value_2>> Scale(Value_2 const &scalar) const
    {
        return {scalar * X(), scalar * Y(), scalar * Z(), scalar * T()};
    }

    /**
     * @brief Scalar product
     */
    template <typename Value_2>
    ValueProduct<Value_2> Dot(LorentzVectorBase<Value_2> const &lorentz_vector) const
    {
        return T() * lorentz_vector.T() - Vector().Dot(lorentz_vector.Vector());
    }

    /**
     * @brief Euclidean product
     */
    template <typename Value_2>
    ValueProduct<Value_2> Euclidean(LorentzVectorBase<Value_2> const &lorentz_vector) const
    {
        return T() * lorentz_vector.T() + Vector().Dot(lorentz_vector.Vector());
    }

    //@}

    /**
     * @name Operators
     * @{
     */

    /**
     * @brief Less than comparison
     */
    bool operator<(LorentzVectorBase const &lorentz_vector) const
    {
        return Mag2() < lorentz_vector.Mag2();
    }

    /**
     * @brief Equality comparison
     */
    bool operator==(LorentzVectorBase const &lorentz_vector) const
    {
        return Vector() == lorentz_vector.Vector() && T() == lorentz_vector.T();
    }

    /**
     * @brief Additions
     */
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase &operator+=(LorentzVectorBase<Value_2> const &lorentz_vector)
    {
        Vector() += lorentz_vector.Vector();
        scalar_ += lorentz_vector.T();
        return *this;
    }

    /**
     * @brief Subtractions
     */

    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase &operator-=(LorentzVectorBase<Value_2> const &lorentz_vector)
    {
        Vector() -= lorentz_vector.Vector();
        scalar_ -= lorentz_vector.T();
        return *this;
    }

    /**
     * @brief Product with scalar
     */
    template <typename Value_2, typename = OnlyIfNotQuantity<Value_2>>
    LorentzVectorBase &operator*=(Value_2 scalar)
    {
        Vector() *= scalar;
        scalar_ *= scalar;
        return *this;
    }

    /**
     * @brief Divison by scalar
     */
    template <typename Value_2, typename = OnlyIfNotQuantity<Value_2>>
    LorentzVectorBase &operator/=(Value_2 scalar)
    {
        Vector() /= scalar;
        scalar_ /= scalar;
        return *this;
    }

    /**
     * @brief Divison by scalar
     */
    template <typename Value_2>
    LorentzVectorBase<ValueQuotient<Value_2>> operator/(Value_2 const &scalar) const
    {
        return Scale(1. / scalar);
    }

    /**
     * @brief Unary minus.
     */
    LorentzVectorBase operator-() const
    {
        return { -X(), -Y(), -Z(), -T()};
    }

    /**
     * @brief components by index.
     */
    Value_ const &operator()(LorentzDim i) const
    {
        //dereferencing operatorconst
        switch (i) {
        case LorentzDim::x :
            return Vector()(Dim3::x);
        case LorentzDim::y :
            return Vector()(Dim3::y);
        case LorentzDim::z :
            return Vector()(Dim3::z);
        case LorentzDim::t :
            return scalar_;
        default:
            std::cout << "bad index(%d) returning 0 " << Name(i) << std::endl;
        }
        return Vector()(Dim3::x);
    }

    /**
     * @brief components by index.
     */
    Value_ const &operator[](LorentzDim i) const
    {
        return (*this)(i);
    }

    /**
     * @brief components by index.
     */
    Value_ &operator()(LorentzDim i)
    {
        //dereferencing operator
        switch (i) {
        case LorentzDim::x :
            return Vector()(Dim3::x);
        case LorentzDim::y :
            return Vector()(Dim3::y);
        case LorentzDim::z :
            return Vector()(Dim3::z);
        case LorentzDim::t :
            return scalar_;
        default:
            std::cout << "bad index(%d) returning &e_ " << Name(i) << std::endl;
        }
        return scalar_;
    }

    /**
     * @brief components by index.
     */
    Value_ &operator[](LorentzDim i)
    {
        return (*this)(i);
    }

    //@}

    /**
     * @name Iterators
     * @{
     */

    ConstIterator<Vector3, Value_, LorentzDim> begin() const
    {
        return {this, LorentzDim::x};
    }

    ConstIterator<Vector3, Value_, LorentzDim> end() const
    {
        return {this, LorentzDim::last};
    }

    Iterator<Vector3, Value_, LorentzDim> begin()
    {
        return {this, LorentzDim::x};
    }

    Iterator<Vector3, Value_, LorentzDim> end()
    {
        return {this, LorentzDim::last};
    }

    //@}

protected:

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
auto operator*(LorentzVectorBase<Value> const &lorentz_vector_1, LorentzVectorBase<Value_2> const &lorentz_vector_2)
{
    return lorentz_vector_1.Dot(lorentz_vector_2);
}

// Scaling of lorentzvectors with a real number
template < class Value, class Value_2, typename = OnlyIfNotLorentzVectorBase<Value_2> >
auto operator*(LorentzVectorBase<Value> const &lorentz_vector, Value_2 scalar)
{
    return lorentz_vector.Scale(scalar);
}

template < class Value, class Value_2, typename = OnlyIfNotLorentzVectorBase<Value> >
auto operator*(Value scalar, LorentzVectorBase<Value_2> const &lorentz_vector)
{
    return lorentz_vector.Scale(scalar);
}

}
