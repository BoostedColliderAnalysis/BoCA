#pragma once

#include "TVector3.h"
#include "boca/math/Vector2.hh"

namespace boca
{

/**
* @ingroup Math
* @brief Three dimensions
*/
enum class Dim3
{
    x,
    y,
    z,
    last
};

std::string Name(Dim3 dim_3);

Dim3 Third(Dim3 dim_1,  Dim3 dim_2);

Dim3 Next(Dim3 dim);

std::vector<Dim3> Dimensions3();

template<class Value_>
class Matrix3;

/**
 * @ingroup Math
 * @brief Three dimensionial vector
 */
template<class Value_>
class Vector3 : boost::totally_ordered<Vector3<Value_>>
            , boost::additive<Vector3<Value_>>
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
    constexpr Vector3() :
        trans_(),
        z_(0)
    {}

    /**
     * @brief Constructor accepting three scalars
     */
    constexpr Vector3(Value_ x, Value_ y, Value_ z) :
        trans_(x, y),
        z_(z)
    {};

    /**
     * @brief Constructor accepting one scalar and its direction
     */
    Vector3(Value_ value, Dim3 dim_3) :
        z_(dim_3 == Dim3::z ? value : Value_(0))
    {
        trans_.X() = dim_3 == Dim3::x ? value : Value_(0);
        trans_.Y() = dim_3 == Dim3::y ? value : Value_(0);
    }

    /**
     * @brief Constructor accepting a two vector and a scalar
     */
    constexpr Vector3(Vector2<Value_> const &transversal,  Value_ z) :
        trans_(transversal),
        z_(z)
    {}

    /**
     * @brief Constructor accepting a vector
     */
    template<typename Value_2_>
    constexpr Vector3(Vector3<Value_2_> const &vector) :
        trans_(vector.Transversal()),
        z_(vector.Z())
    {}

    /**
     * @brief Constructor accepting a root::TVector3
     */
    constexpr Vector3(TVector3 const &vector) :
        trans_(vector.XYvector()),
        z_(vector.Z())
    {}
    //@}

    /**
     * @name Setter
     * @{
     */

    /**
     * @brief Set x, y, z according to value
     */
    void SetUniform(Value_ value)
    {
        Transversal().SetUniform(value);
        Z() = value;
    }

    /**
     * @brief Set the magnitude keeping theta and phi constant
     */
    void SetMag(Value_ magnitude)
    {
        auto const old = Mag();
        *this *= old == Value_(0) ? 0. : magnitude / old;
    }

    /**
     * @brief Set the transverse component keeping phi and z constant.
     */
    void SetPerp(Value_ perp)
    {
        Transversal().SetMag(perp);
    }

    /**
     * @brief Set phi keeping the magnitue and theta constant
     */
    void SetPhi(boca::Angle const &phi)
    {
        Transversal().SetPhi(phi);
    }

    /**
     * @brief Set mag, theta, phi
     */
    void SetMagThetaPhi(Value_ mag, boca::Angle const &theta, boca::Angle const &phi)
    {
        Transversal().SetMagPhi(mag * boost::units::sin(theta),  phi);
        Z() = mag * boost::units::cos(theta);
    }

    /**
     * @brief Set theta keeping mag and phi constant
     */
    void SetTheta(boca::Angle const &theta)
    {
        SetMagThetaPhi(Mag(),  theta,  Phi());
    }

    /**
     * @brief Set Perpendicular, Theta and Phi
     */
    void SetPerpThetaPhi(Value_ perp, boca::Angle const &theta, boca::Angle const &phi)
    {
        Transversal().SetMagPhi(perp,  phi);
        auto const tan_theta = tan(theta);
        Z() = tan_theta == 0. ? abs(perp) / tan_theta : Value_(0);
    }

    /**
     * @brief Set Perpendicular, Eta and Phi
     */
    void SetPerpEtaPhi(Value_ const &perp, boca::Angle const &eta, boca::Angle const &phi)
    {
        Transversal().SetMagPhi(perp,  phi);
        Z() = abs(perp) * units::sinh(eta);
    }
    //@}

    /**
     * @name Accessors and Getters
     * @{
     */

    /**
     * @brief Getter for X
     */
    constexpr Value_ const& X() const
    {
        return trans_.X();
    }

    /**
     * @brief Getter for Y
     */
    constexpr Value_ const& Y() const
    {
        return trans_.Y();
    }

    /**
     * @brief Getter for Z
     */
    constexpr Value_ const& Z() const
    {
        return z_;
    }

    /**
    * @brief Transversal vector \f$(x, y)\f$
    */
    constexpr Vector2<Value_> Transversal() const
    {
        return trans_;
    }

    /**
     * @brief Accessor for X
     */
    Value_ &X()
    {
        return trans_.X();
    }

    /**
     * @brief Accessor for Y
     */
    Value_ &Y()
    {
        return trans_.Y();
    }

    /**
     * @brief Accessor for Z
     */
    Value_ &Z()
    {
        return z_;
    }

    /**
    * @brief Transversal vector \f$(x, y)\f$
    */
    Vector2<Value_> &Transversal()
    {
        return trans_;
    }
    //@}

    /**
     * @name Angles
     * @{
     */

    /**
     * @brief The azimuth angle \f$\phi\f$ restricted to \f$[-\pi,\pi]\f$
     */
    boca::Angle Phi() const
    {
        return Transversal().Phi();
    }

    /**
     * @brief The polar angle \f$\theta\f$
     */
    boca::Angle Theta() const
    {
        auto const perp = Perp();
        return perp == Value_(0) && Z() == Value_(0) ? 0_rad : atan2(perp, Z());
    }

    /**
     * @brief Cosine of the polar angle \f$\cos \theta\f$
     */
    double CosTheta() const
    {
        auto const mag = Mag();
        return mag == Value_(0) ? 1 : Z() / mag;
    }

    /**
     * @brief Square of the sine of the polar angle \f$\sin^2 \theta\f$
     */
    double SinTheta2() const
    {
        auto const mag2 = Mag2();
        return mag2 == ValueSquare(0) ? 0. : static_cast<double>(Perp2() / mag2);
    }

    /**
     * @brief Sine of the polar angle \f$\sin \theta\f$
     */
    double SinTheta() const
    {
        auto const mag = Mag();
        return mag == Value_(0) ? 0 : Perp() / mag;
    }

    /**
     * @brief Difference to vector in azimuth \f$\Delta\phi\f$ restricted to \f$[-\pi,\pi]\f$
     */
    template <typename Value_2_>
    boca::Angle DeltaPhiTo(Vector3<Value_2_> const &vector) const
    {
        return Restrict(Phi() - vector.Phi());
    }

    /**
     * @brief Difference to vector in PseudoRapidity \f$\Delta\eta\f$
     */
    template <typename Value_2_>
    boca::Angle DeltaEtaTo(Vector3<Value_2_> const &vector) const
    {
        return Eta() - vector.Eta();
    }

    /**
     * @brief Difference to vector in \f$\Delta R = \sqrt{(\Delta \eta)^2 + (\Delta \phi)^2}\f$
     */
    template <typename Value_2_>
    boca::Angle DeltaRTo(Vector3<Value_2_> const &vector) const
    {
        return sqrt(sqr(DeltaEtaTo(vector)) + sqr(DeltaPhiTo(vector)));
    }

    /**
     * @brief The angle to vector
     */
    boca::Angle Angle(Vector3 const &vector) const
    {
        return atan2(Cross(vector), Dot(vector));
    }

    /**
     * @brief Square of the tangent of the polar angle \f$\tan(\theta)^2\f$ to a vector
     *
     * usign \f$\frac{(a \times b)^2}{(a \cdot b)^2}\f$
     */
    double Tan2(Vector3 const &vector)
    {
        return sqr(Cross(vector)) / sqr(Dot(vector));
    }

    /**
     * @brief Pseudorapidity \f$\eta = -\ln(\tan(\frac{\theta}{2}))\f$
     * @{
     */
    boca::Angle PseudoRapidity() const
    {
        auto const cos_theta = CosTheta();
        if (sqr(cos_theta) < 1) return -0.5 * units::log((1 - cos_theta) / (1 + cos_theta));
        if (Z() == Value_(0)) return 0_rad;
        if (Z() > 0) return 10e10_rad;
        else return -10e10_rad;
    }

    boca::Angle Eta() const
    {
        return PseudoRapidity();
    }
    //@}

    //@}

    /**
     * @name Magnitudes
     * @{
     */

    /**
     * @brief The magnitude squared \f$r^2 = x^2 + y^2 + z^2\f$
     */
    constexpr ValueSquare Mag2() const
    {
        return Perp2() + sqr(Z());
    }

    /**
     * @brief The magnitude \f$r = \sqrt{x^2 + y^2 + z^2}\f$
     */
    constexpr Value_ Mag() const
    {
        return sqrt(Mag2());
    }

    /**
     * @brief The transverse component squared \f$\rho^2 = x^2 + y^2\f$
     */
    constexpr ValueSquare Perp2() const
    {
        return Transversal().Mag2();
    }

    /**
     * @brief The transverse component \f$\rho = \sqrt{x^2 + y^2}\f$
     */
    constexpr Value_ Perp() const
    {
        return Transversal().Mag();
    }

    /**
     * @brief The transverse component \f$x^2 + y^2\f$ to a vector
     */
    template <typename Value_2_>
    constexpr ValueSquare Perp2(Vector3<Value_2_> const &vector) const
    {
        auto const other_mag2 = vector.Mag2();
        auto this_mag_2 = Mag2();
        if (other_mag2 > boca::ValueSquare<Value_2_>(0)) this_mag_2 -= sqr(Dot(vector)) / other_mag2;
        if (this_mag_2 < ValueSquare(0)) this_mag_2 = ValueSquare(0);
        return this_mag_2;
    }

    /**
     * @brief The transverse component \f$\sqrt{x^2 + y^2}\f$ to a vector
     */
    template <typename Value_2_>
    constexpr Value_ Perp(Vector3<Value_2_> const &vector) const
    {
        return sqrt(Perp2(vector));
    }
    //@}

    /**
     * @name Rotations
     * @{
     */

    /**
    * @brief Rotate by phi in (dim_1,  dim_2) plain
    */
    Vector3 &Rotate(boca::Angle const &phi, Dim3 dim_1,  Dim3 dim_2)
    {
        if (phi == 0_rad)  return *this;
        auto const cos = boost::units::cos(phi);
        auto const sin = boost::units::sin(phi);
        auto const row = (*this)(dim_1);
        (*this)(dim_1) = cos * row - sin * (*this)(dim_2);
        (*this)(dim_2) = sin * row + cos * (*this)(dim_2);
        return *this;
//         Vector2<Value_>((*this)(dim_1),(*this)(dim_2)).Rotate(phi);
    }

    /**
    * @brief Rotate by phi around axis dim
    */
    Vector3 &Rotate(boca::Angle const &phi, Dim3 dim)
    {
        switch (dim) {
        case Dim3::x :
            return Rotate(phi, Dim3::y, Dim3::z);
        case Dim3::y :
            return Rotate(phi, Dim3::z, Dim3::x);
        case Dim3::z :
            return Rotate(phi, Dim3::x, Dim3::y);
        default :
            ;
        }
    }

    /**
    * @brief Rotates around the axis specified by another vector
    */
    template<typename Value_2_>
    auto &Rotate(boca::Angle angle, Vector3<Value_2_> const &axis);

    /**
    * @brief Transformation with a Rotation matrix.
    */
    template<typename Value_2_>
    auto &Transform(Matrix3<Value_2_> const &matrix);

    /**
    * @brief Rotates reference frame from \f$U_z\f$ to \f$U_z^\prime\f$
    */
    template<typename Value_2_>
    constexpr void RotateUz(Vector3<Value_2_> const &vector)
    {
        auto const unit = vector.Unit();
        auto const perp2 = unit.Perp();
        if (perp2 > 0) {
            auto const perp = sqrt(perp2);
            auto temp = unit * (unit.Z() * X() + perp * Z());
            temp.X() -= unit.Y() * Y();
            temp.Y() += unit.X() * Y();
            temp.Z() -= - X();
            *this = temp / perp;
        } else if (unit.Z() < 0) {
            X() = -X(); // phi=0 teta=pi
            Z() = -Z();
        } else {};
    }

    //@}

    /**
     * @name Vectors
     * @{
     */

    /**
    * @brief Unit vector parallel to this.
    */
    Vector3<double> Unit() const
    {
        auto const mag2 = Mag2();
        return mag2 == ValueSquare(0) ? Vector3<double>() : static_cast<Vector3<double>>(*this / sqrt(mag2));
    }

    /**
    * @brief Vector orthogonal to this
    */
    Vector3 Orthogonal() const
    {
        auto const x = X() < Value_(0) ? -X() : X();
        auto const y = Y() < Value_(0) ? -Y() : Y();
        auto const z = Z() < Value_(0) ? -Z() : Z();
        if (x < y) return x < z ? Vector3(Value_(0), Z(), -Y()) : Vector3(Y(), -X(), Value_(0));
        else return y < z ? Vector3(-Z(), Value_(0), X()) : Vector3(Y(), -X(), Value_(0));
    }

    /**
    * @brief Angluar vector (\f$\eta\f$, \f$\phi\f$)
    */
    Vector2<boca::Angle> EtaPhiVector() const
    {
        return {Eta(), Phi()};
    }
    //@}

    /**
     * @name Products
     * @{
     */

    /**
    * @brief Scale vector with a scalar
    */
    template <typename Value_2_>
    constexpr Vector3<ValueProduct<Value_2_>> Scale(Value_2_ const &scalar) const
    {
        return {Transversal() *scalar, Z() *scalar};
    }

    /**
    * @brief Dot product between two vector
    */
    template <typename Value_2_>
    constexpr ValueProduct<Value_2_> Dot(Vector3<Value_2_> const &vector) const
    {
        return Transversal() * vector.Transversal() + Z() * vector.Z();
    }

    /**
    * @brief Cross product between two vector
    */
    template <typename Value_2_>
    constexpr Vector3<ValueProduct<Value_2_>> Cross(Vector3<Value_2_> const &vector) const
    {
        return {Y() *vector.Z() - vector.Y() *Z(), Z() *vector.X() - vector.Z() *X(), X() *vector.Y() - vector.X() *Y()};
    }

    /**
    * @brief Triple product between three vectors
    */
    template <typename Value_2_, typename Value_3>
    constexpr ValueCubed<Value_2_, Value_3> Triple(Vector3<Value_2_> const &vector_1, Vector3<Value_3> const &vector_2) const
    {
        return Cross(vector_1) * vector_2;
    }
    //@}

    /**
     * @name Operators
     * @{
     */

    /**
    * @brief Less than comparison
    */
    constexpr bool operator<(Vector3 const &vector) const
    {
        return Mag2() < vector.Mag2();
    }

    /**
    * @brief Equality comparison
    */
    constexpr bool operator==(Vector3 const &vector) const
    {
        return vector.Transversal() == Transversal() && vector.Z() == Z();
    }

    /**
    * @brief Sum of two vectors
    */
    template <typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    Vector3 &operator+=(Vector3<Value_2_> const &vector)
    {
        Transversal() += vector.Transversal();
        Z() += vector.Z();
        return *this;
    }

    /**
    * @brief Difference of two vectors
    */
    template <typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    Vector3 &operator-=(Vector3<Value_2_> const &vector)
    {
        Transversal() -= vector.Transversal();
        Z() -= vector.Z();
        return *this;
    }

    /**
    * @brief Scaling with real numbers
    */
    template < typename Value_2_, typename = OnlyIfNotQuantity<Value_2_> >
    Vector3 &operator*=(Value_2_ scalar)
    {
        Transversal() *= scalar;
        Z() *= scalar;
        return *this;
    }

    /**
    * @brief Multiplication with a matrix
    */
    template<typename Value_2_>
    auto &operator*=(Matrix3<Value_2_> const &matrix);

    /**
    * @brief division by scalar
    */
    template < typename Value_2_, typename = OnlyIfNotQuantity<Value_2_> >
    Vector3 &operator/=(Value_2_ scalar)
    {
        Transversal() /= scalar;
        Z() /= scalar;
        return *this;
    }

    /**
    * @brief Cross product
    */
    template <typename Value_2_>
    constexpr friend Vector3<ValueProduct<Value_2_>> operator^(Vector3 const &vector_1, Vector3<Value_2_> const &vector_2)
    {
        return vector_1.Cross(vector_2);
    }

    /**
    * @brief division by scalar
    */
    template <typename Value_2_>
    constexpr friend Vector3 <ValueQuotient<Value_2_>> operator/(Vector3 const &vector, Value_2_ const &scalar)
    {
        return vector.Scale(1. / scalar);
    }

    /**
    * @brief Unary minus
    */
    constexpr Vector3 operator-() const
    {
        return { -Transversal(), -Z()};
    }

    /**
    * @brief Components by index
    */
    Value_ const& operator[](Dim3 dim_3) const
    {
        switch (dim_3) {
        case Dim3::x : return X();
        case Dim3::y : return Y();
        case Dim3::z : return Z();
        default :
            Default("Vector3", Name(dim_3));
            return X();
        }
    }

    /**
    * @brief Components by index
    */
    Value_ &operator[](Dim3 dim_3)
    {
        return const_cast<Value_ &>(static_cast<Vector3<Value_> const &>(*this)[dim_3]);
    }

    /**
     * @brief Output stream operator
     */
    friend auto &operator<<(std::ostream &stream, Vector3<Value_> const &vector)
    {
        stream << vector.Transversal() << Stream(vector.Z());
        return stream;
    }

    //@}

    /**
     * @name Iterators
     * @{
     */

    using Dimension = Dim3;

    /**
     * @brief Const begin
     */
    constexpr ConstIterator<boca::Vector3, Value_> begin() const
    {
        return {this, Dim3::x};
    }

    /**
     * @brief Const end
     */
    constexpr ConstIterator<boca::Vector3, Value_> end() const
    {
        return {this, Dim3::last};
    }

    /**
     * @brief begin
     */
    Iterator<boca::Vector3, Value_> begin()
    {
        return {this, Dim3::x};
    }

    /**
     * @brief end
     */
    Iterator<boca::Vector3, Value_> end()
    {
        return {this, Dim3::last};
    }
    //@}

private:

    Vector2<Value_> trans_;

    Value_ z_;

};

template <typename>
struct IsVector3 : std::false_type { };

template <typename Value_>
struct IsVector3<Vector3<Value_>> : std::true_type { };

template<typename Value_>
using OnlyIfNotVector3 = typename std::enable_if < !IsVector3<Value_>::value >::type;

template<typename Value_>
using OnlyIfVector3 = typename std::enable_if < IsVector3<Value_>::value >::type;

// Scalar product of 3-vectors.
template < class Value_, class Value_2_, typename = OnlyIfVector3<Value_>,  typename = OnlyIfVector3<Value_2_>  >
constexpr auto operator*(Value_ const &vector_1, Value_2_ const &vector_2)
{
    return vector_1.Dot(vector_2);
}

// Scaling of 3-vectors with a real number
template < class Value_, class Value_2_, typename = OnlyIfVector3<Value_>,  typename = OnlyIfNotVector3<Value_2_>  >
constexpr auto operator*(Value_ const &vector, Value_2_ scalar)
{
    return vector.Scale(scalar);
}

template < class Value_, class Value_2_, typename = OnlyIfVector3<Value_>,  typename = OnlyIfNotVector3<Value_2_>  >
constexpr auto operator*(Value_2_ scalar, Value_ const &vector)
{
    return vector.Scale(scalar);
}

template <class Value_1, class Value_2_, class Value_3>
constexpr auto Triple(Vector3<Value_1> const &vector_1, Vector3<Value_2_> const &vector_2, Vector3<Value_3> const &vector_3)
{
    return vector_1.Triple(vector_2, vector_3);
}

}

namespace boost{

template<typename Value_>
struct range_const_iterator< boca::Vector3<Value_> > {
    typedef typename boca::ConstIterator<boca::Vector3, Value_> type;
};

template<typename Value_>
struct range_mutable_iterator< boca::Vector3<Value_> > {
    typedef typename boca::Iterator<boca::Vector3, Value_> type;
};

}
