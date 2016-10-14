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
class LorentzVectorBase : boost::totally_ordered<LorentzVectorBase<Value_>>
            , boost::additive<LorentzVectorBase<Value_>>
            , Vector3<Value_>
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
    constexpr LorentzVectorBase() :
        Vector3<Value_>(),
        scalar_(Value_(0)) {}

    /**
     * @brief Constructor accepting the components x, y, z, t.
     */
    constexpr LorentzVectorBase(Value_ x, Value_ y, Value_ z, Value_ t) :
        Vector3<Value_>(x, y, z),
        scalar_(t) {}

    /**
     * @brief Constructor accepting a 3-Vector and a scalar component.
     */
    constexpr LorentzVectorBase(Vector3<Value_> const &vector3, Value_ const &t) :
        Vector3<Value_>(vector3),
        scalar_(t) {}

    /**
     * @brief Copy constructor with casting
     */
    template<typename Value_2>
    constexpr LorentzVectorBase(LorentzVectorBase<Value_2> const &lorentz_vector) :
        Vector3<Value_>(lorentz_vector.Spatial()),
        scalar_(lorentz_vector.Scalar()) {}
    //@}

    /**
     * @name Setter
     * @{
     */

    /**
     * @brief Set components
     */
    constexpr void SetVectT(Vector3<Value_> const &spatial, Value_ t)
    {
        Spatial() = spatial;
        Scalar() = t;
    }

    using Vector3<Value_>::SetTheta;

    using Vector3<Value_>::SetPhi;

    using Vector3<Value_>::SetPerp;

    using Vector3<Value_>::SetPerpEtaPhi;

    /**
     * @brief Set spatial magnitude
     */
    constexpr void SetRho(Value_ rho)
    {
        Spatial().SetMag(rho);
    }

    /**
     * @brief Set Nergy according to spatial component and magnitude \f$e = \sqrt{ m^2 + \rho^2}\f$
     */
    constexpr void SetMag(Value_ magnitude)
    {
        Scalar() = magnitude >= Value_(0)  ?  sqrt(sqr(Spatial()) + sqr(magnitude)) : sqrt(std::max((sqr(Spatial()) - sqr(magnitude)), ValueSquare(0)));
    }

    /**
     * @brief Copy spatial coordinates, and set \f$e = \sqrt{ m^2 + \rho^2}\f$
     */
    constexpr void SetVectMag(Vector3<Value_> const &spatial, Value_ magnitude)
    {
        Spatial() = spatial;
        SetMag(magnitude);
    }

    /**
     * @brief Set perp,  \f$\eta\f$, \f$\phi\f$ and magnitude
     */
    constexpr void SetPerpEtaPhiMag(Value_ const &perp, boca::Angle const &eta, boca::Angle const &phi, Value_ const &mag)
    {
        SetPerpEtaPhi(perp, eta,  phi);
        SetMag(mag);
    }

    /**
     * @brief Set perp,  \f$\eta\f$, \f$\phif$ and time
     */
    constexpr void SetPerpEtaPhiT(Value_ const &perp, boca::Angle const &eta, boca::Angle const &phi, Value_ const &t)
    {
        SetPerpEtaPhi(perp, eta, phi);
        scalar_ = t;
    }

    //@}

    /**
     * @name Accessors and Getter
     * @{
     */

    /**
     * @brief Getter for the spatial components
     */
    constexpr Vector3<Value_> Spatial() const
    {
        return *this;
    }

    /**
     * @brief Accessor for the spatial components
     */
    Vector3<Value_> &Spatial()
    {
        return *this;
    }

    using Vector3<Value_>::X;

    using Vector3<Value_>::Y;

    using Vector3<Value_>::Z;

    /**
     * @brief Accessor for the scalar
     * @{
     */
    Value_ &Scalar()
    {
        return scalar_;
    }

    Value_ &T()
    {
        return scalar_;
    }
    //@}

    /**
     * @brief Getter for the scalar component
     * @{
     */
    constexpr Value_ Scalar() const
    {
        return scalar_;
    }

    constexpr Value_ T() const
    {
        return scalar_;
    }
    //@}

    //@}

    /**
     * @name Angles
     * @{
     */

    using Vector3<Value_>::Phi;

    using Vector3<Value_>::Theta;

    using Vector3<Value_>::CosTheta;

    using Vector3<Value_>::SinTheta2;

    using Vector3<Value_>::SinTheta;

//     using Vector3<Value_>::Angle;
//
//     /**
//       * @brief Angle wrt. another vector.
//       */
//     boca::Angle Angle(LorentzVectorBase const &vector) const
//     {
//         return Angle(vector.Spatial());
//     }

    using Vector3<Value_>::Eta;

    using Vector3<Value_>::PseudoRapidity;

    /**
     * @brief Rapidity \f$y = \frac{1}{2} \ln\frac{t + z}{t - z}\f$
     * @{
     */
    boca::Angle Rapidity() const
    {
        return 0.5 * units::log(static_cast<double>(Plus() / Minus()));
    }

    boca::Angle Rap() const
    {
        return Rapidity();
    }
    //@}

    /**
     * @brief Rapidity with respect to another vector
     */
    boca::Angle Rapidity(Vector3<double> const &vector) const
    {
        auto const mag_2 = vector.Mag2();
        if (mag_2 <= 0) return 0_rad;
        auto const vdotu = Spatial().Dot(vector) / sqrt(mag_2);
        if (vdotu == Value_(0)) return 0_rad;
//         if (Scalar() <= Value_(0)) std::cout << "Tried to take rapidity of negative-energy Lorentz vector" << '\n';
//         auto pt = sqrt(units::max(sqr(Scalar() * std::numeric_limits<double>::epsilon()), Perp2(vector) + Mag2()));
        auto const mt = sqrt(Perp2(vector) + Mag2());
        if (mt == Value_(0)) return 0_rad;
        auto const rap = units::log(static_cast<double>((Scalar() + abs(Z())) / mt));
        return Z() > Value_(0) ? rap : -rap;
    }

    using Vector3<Value_>::DeltaPhiTo;

    using Vector3<Value_>::DeltaEtaTo;

    /**
     * @brief Difference in Rapidity to a vector \f$\Delta y\f$
     */
    template <typename Value_2_>
    boca::Angle DeltaRapTo(LorentzVectorBase<Value_2_> const &vector) const
    {
        return Rap() - vector.Rap();
    }

    /**
     * @brief Difference in agular space to a vector \f$\Delta R = \sqrt{ (\Delta y)^2 + (\Delta \phi)^2}\f$ to vector
     */
    template <typename Value_2_>
    boca::Angle DeltaRTo(LorentzVectorBase<Value_2_> const &vector) const
    {
        return sqrt(sqr(DeltaRapTo(vector)) + sqr(DeltaPhiTo(vector)));
    }

    //@}

    /**
     * @name Magnitudes
     * @{
     */

    using Vector3<Value_>::Perp2;

    using Vector3<Value_>::Perp;

    /**
     * @brief Square of the spatial radius  \f$\rho^2 = x^2 + y^2\f$
     */
    constexpr ValueSquare Rho2() const
    {
        return Spatial().Mag2();
    }

    /**
     * @brief spatial radius \f$\rho = \sqrt{x^2 + y^2 + z^2}\f$
     */
    constexpr Value_ Rho() const
    {
        return Spatial().Mag();
    }

    /**
     * @brief Square of the magnitude \f$m^2 = t^2 - \rho^2\f$
     */
    constexpr ValueSquare Mag2() const
    {
        return sqr(Scalar()) - Rho2();
    }

    /**
     * @brief Magnitude \f$m = \sqrt{t^2 - \rho^2}\f$
     *
     * If the square of the magnitude is negative \f$-\sqrt{-m^2}\f$ is returned
     */
    constexpr Value_ Mag() const
    {
        auto const mag2 = Mag2();
        return mag2 < ValueSquare(0) ? -sqrt(-mag2) : sqrt(mag2);
    }

    /**
    * @brief Square of the transvere magnitude \f$m_T^2 = m^2 + x^2 + y^2\f$
    */
    constexpr ValueSquare MagT2() const
    {
        return sqr(Scalar()) - sqr(Z());
    }

    /**
    * @brief Transvere magnitude \f$m_T = \sqrt{m^2 + x^2 + y^2}\f$
    */
    constexpr Value_ MagT() const
    {
        auto const mt2 = MagT2();
        return mt2 < ValueSquare(0) ? -sqrt(-mt2) : sqrt(mt2);
    }

    /**
    * @brief transvere scalar square \f$e_T^2 = e^2 \frac{p_T^2}{\rho^2}\f$
    */
    constexpr ValueSquare ScalarT2() const
    {
        return sqr(Scalar()) * SinTheta2();
    }

    /**
    * @brief transvere scalar square \f$e_T = e \frac{p_T}{\rho}\f$
    */
    constexpr Value_ ScalarT() const
    {
        return Scalar() < Value_(0) ? -sqrt(ScalarT2()) : sqrt(ScalarT2());
    }

    /**
    * @brief Transverse scalar squared towards a vector
    */
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    constexpr ValueSquare ScalarT2(Vector3<Value> const &vector) const
    {
        auto const pt2 = Spatial().Perp2(vector);
        return pt2 == ValueSquare(0) ? ValueSquare(0) : sqr(Scalar()) * pt2 / (pt2 + sqr(Spatial().Dot(vector.Unit())));
    }

    /**
    * @brief Transverse scalar towards a vector
    */
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    constexpr Value_ ScalarT(Vector3<Value> const &vector) const
    {
        return Scalar() < Value_(0) ? -sqrt(Et2(vector)) : sqrt(Et2(vector));
    }

    /**
     * @brief Relative velocity \f$\beta = \frac{\rho}{t}\f$
     */
    constexpr double Beta() const
    {
        return Rho() / Scalar();
    }

    /**
     * @brief Lorentz factor \f$\gamma = \frac{1}{\sqrt{1-\beta^2}}\f$
     */
    constexpr double Gamma() const
    {
        return 1. / std::sqrt(1. - sqr(Beta()));
    }

    /**
     * @brief Positive light cone component \f$p = t + z\f$
     *
     * Beware of alternative definition \f$p = \frac{t + z}{\sqrt 2}\f$
     */
    constexpr Value_ Plus() const
    {
        return Scalar() + Z();
    }

    /**
     * @brief Negative light cone component \f$m = t - z\f$
     *
     * Beware of alternative definition \f$m = \frac{t - z}{\sqrt 2}\f$
     */
    constexpr Value_ Minus() const
    {
        return Scalar() - Z();
    }
    //@}

    /**
     * @name Vectors
     * @{
     */

    /**
     * @brief Spatial components divided by the time component
     */
    constexpr Vector3<double> BoostVector() const
    {
        return Scalar() == Value_(0) ? Vector3<double> {} :
               Vector3<double> {Spatial() / Scalar()};
    }

    using Vector3<Value_>::Transversal;

    using Vector3<Value_>::EtaPhiVector;

    /**
     * Boost from reference frame into this vector's rest frame: \f$-\frac{\vec{x}}{t}\f$.
     */
    constexpr Vector3<double> BoostIntoRestFrame() const
    {
        return -BoostVector();
    }

    /**
     * @brief Boosted Lorentz vector
     */
    constexpr LorentzVectorBase<Value_> Boosted(Vector3<double> const &boost) const
    {
        auto lorentz_vector = *this;
        return lorentz_vector.Boost(boost);
    }
    //@}

    /**
     * @name Rotation
     * @{
     */

    /**
     * @brief Boost this Lorentz vector
     */
    constexpr LorentzVectorBase<Value_> &Boost(Vector3<double> const &boost)
    {
        auto const mag_2 = boost.Mag2();
        auto const gamma = 1 / sqrt(1 - mag_2);
        auto const gamma2 = mag_2 > 0 ? (gamma - 1) / mag_2 : 0;
        auto const bp = boost * Spatial();
        auto const scaled = gamma * Scalar();

        Spatial() += boost * (gamma2 * bp + scaled);
        Scalar() = scaled + gamma * bp;
        return *this;
    }

    using Vector3<Value_>::Rotate;

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
    constexpr LorentzVectorBase<ValueProduct<Value_2>> Scale(Value_2 const &scalar) const
    {
        return {Spatial() * scalar, Scalar() * scalar};
    }

    /**
     * @brief Scalar dot product with a lorentz vector
     */
    template <typename Value_2>
    constexpr ValueProduct<Value_2> Dot(LorentzVectorBase<Value_2> const &lorentz_vector) const
    {
        return Scalar() * lorentz_vector.Scalar() - Spatial().Dot(lorentz_vector.Spatial());
    }

    /**
     * @brief Euclidean product with a lorentz vector
     */
    template <typename Value_2>
    constexpr ValueProduct<Value_2> Euclidean(LorentzVectorBase<Value_2> const &lorentz_vector) const
    {
        return Scalar() * lorentz_vector.Scalar() + Spatial().Dot(lorentz_vector.Spatial());
    }

    //@}

    /**
     * @name Operators
     * @{
     */

    /**
     * @brief Less than comparison
     */
    constexpr bool operator<(LorentzVectorBase const &lorentz_vector) const
    {
        return Mag2() < lorentz_vector.Mag2();
    }

    /**
     * @brief Equality comparison
     */
    constexpr bool operator==(LorentzVectorBase const &lorentz_vector) const
    {
        return Spatial() == lorentz_vector.Spatial() && Scalar() == lorentz_vector.Scalar();
    }

    /**
     * @brief Additions
     */
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    constexpr LorentzVectorBase &operator+=(LorentzVectorBase<Value_2> const &lorentz_vector)
    {
        Spatial() += lorentz_vector.Spatial();
        scalar_ += lorentz_vector.Scalar();
        return *this;
    }

    /**
     * @brief Subtractions
     */

    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    constexpr LorentzVectorBase &operator-=(LorentzVectorBase<Value_2> const &lorentz_vector)
    {
        Spatial() -= lorentz_vector.Spatial();
        scalar_ -= lorentz_vector.Scalar();
        return *this;
    }

    /**
     * @brief Product with scalar
     */
    template <typename Value_2, typename = OnlyIfNotQuantity<Value_2>>
    constexpr LorentzVectorBase &operator*=(Value_2 scalar)
    {
        Spatial() *= scalar;
        Scalar() *= scalar;
        return *this;
    }

    /**
     * @brief Divison by scalar
     */
    template <typename Value_2, typename = OnlyIfNotQuantity<Value_2>>
    constexpr LorentzVectorBase &operator/=(Value_2 scalar)
    {
        Spatial() /= scalar;
        Scalar() /= scalar;
        return *this;
    }

    /**
     * @brief Divison by scalar
     */
    template <typename Value_2>
    constexpr LorentzVectorBase<ValueQuotient<Value_2>> operator/(Value_2 const &scalar) const
    {
        return Scale(1. / scalar);
    }

    /**
     * @brief Unary minus
     */
    constexpr LorentzVectorBase operator-() const
    {
        return { -Spatial(), -Scalar()};
    }

    /**
     * @brief components by index.
     */
    constexpr Value_ const &operator()(LorentzDim i) const
    {
        //dereferencing operatorconst
        switch (i) {
        case LorentzDim::x :
            return Spatial()(Dim3::x);
        case LorentzDim::y :
            return Spatial()(Dim3::y);
        case LorentzDim::z :
            return Spatial()(Dim3::z);
        case LorentzDim::t :
            return scalar_;
        default:
            std::cout << "bad index(%d) returning 0 " << Name(i) << '\n';
        }
        return Spatial()(Dim3::x);
    }

    /**
     * @brief components by index.
     */
    constexpr Value_ const &operator[](LorentzDim i) const
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
            return Spatial()(Dim3::x);
        case LorentzDim::y :
            return Spatial()(Dim3::y);
        case LorentzDim::z :
            return Spatial()(Dim3::z);
        case LorentzDim::t :
            return scalar_;
        default:
            std::cout << "bad index(%d) returning &e_ " << Name(i) << '\n';
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

    constexpr ConstIterator<Vector3, Value_, LorentzDim> begin() const
    {
        return {this, LorentzDim::x};
    }

    constexpr ConstIterator<Vector3, Value_, LorentzDim> end() const
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

    /**
    * @brief time or energy component
    */
    Value_ scalar_;

};

template<typename Value>
using OnlyIfNotLorentzVectorBase = typename std::enable_if<std::is_base_of<LorentzVectorBase<Value>, Value>::value>::type;

/**
 * @brief Scalar product of lorentzvectors.
 */
template <class Value, class Value_2>
constexpr auto operator*(LorentzVectorBase<Value> const &lorentz_vector_1, LorentzVectorBase<Value_2> const &lorentz_vector_2)
{
    return lorentz_vector_1.Dot(lorentz_vector_2);
}

/**
 * @brief Scaling of lorentzvectors with a real number
 */
template < class Value, class Value_2, typename = OnlyIfNotLorentzVectorBase<Value_2> >
constexpr auto operator*(LorentzVectorBase<Value> const &lorentz_vector, Value_2 scalar)
{
    return lorentz_vector.Scale(scalar);
}

/**
 * @brief Scaling of lorentzvectors with a real number
 */
template < class Value, class Value_2, typename = OnlyIfNotLorentzVectorBase<Value> >
constexpr auto operator*(Value scalar, LorentzVectorBase<Value_2> const &lorentz_vector)
{
    return lorentz_vector.Scale(scalar);
}

}
