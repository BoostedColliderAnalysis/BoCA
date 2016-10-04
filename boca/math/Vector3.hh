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

std::string Name(Dim3 dimension);

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

    using Value4 = typename boost::units::multiply_typeof_helper<ValueSquare, ValueSquare>::type;

public:

    /**
     * @name Constructor
     * @{
     */

    /**
     * @brief Default constructor
     */
    constexpr Vector3() :
        x_(0),
        y_(0),
        z_(0)
    {}

    /**
     * @brief Constructor accepting three scalars
     */
    constexpr Vector3(Value_ x, Value_ y, Value_ z) :
        x_(x),
        y_(y),
        z_(z)
    {};

    /**
     * @brief Constructor accepting one scalar and its direction
     */
    constexpr Vector3(Value_ value, Dim3 dim)
    {
        x_ = dim == Dim3::x ? value : Value_(0);
        y_ = dim == Dim3::y ? value : Value_(0);
        z_ = dim == Dim3::z ? value : Value_(0);
    }

    /**
     * @brief Constructor accepting a vector
     */
    template<typename Value_2_>
    constexpr Vector3(Vector3<Value_2_> const &vector) :
        x_(vector.X()),
        y_(vector.Y()),
        z_(vector.Z())
    {}

    /**
     * @brief Constructor accepting a root::TVector3
     */
    constexpr Vector3(TVector3 const &vector) :
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
    void SetPtEtaPhi(Value_ pt, boca::Angle const &eta, boca::Angle const &phi)
    {
        auto const apt = abs(pt);
        x_ = apt * cos(phi);
        y_ = apt * sin(phi);
        auto const tan_eta = tan(2.0 * atan(units::exp(-eta)));
        z_ = tan_eta == 0 ? Value_(0) : apt / tan_eta;
    }

    /**
     * @brief Set Pt, Theta and Phi
     */
    void SetPtThetaPhi(Value_ pt, boca::Angle const &theta, boca::Angle const &phi)
    {
        x_ = pt * cos(phi);
        y_ = pt * sin(phi);
        auto const tan_theta = tan(theta);
        z_ = tan_theta == 0 ? Value_(0) : pt / tan_theta;
    }

    /**
     * @brief Set phi keeping the magnitue and theta constant
     */
    constexpr void SetPhi(boca::Angle const &phi)
    {
        auto const perp = Perp();
        x_ = perp * cos(phi);
        y_ = perp * sin(phi);
    }

    /**
     * @brief Set theta keeping mag and phi constant
     */
    constexpr void SetTheta(boca::Angle const &theta)
    {
        auto const magnitude = Mag();
        auto const phi = Phi();
        x_ = magnitude * sin(theta) * cos(phi);
        y_ = magnitude * sin(theta) * sin(phi);
        z_ = magnitude * cos(theta);
    }

    /**
     * @brief Set the magnitude keeping theta and phi constant
     */
    constexpr void SetMag(Value_ magnitude)
    {
        auto const old = Mag();
        *this *= old == Value_(0) ? 0. : magnitude / old;
    }

    /**
     * @brief Set mag, theta, phi
     */
    constexpr void SetMagThetaPhi(Value_ mag, boca::Angle const &theta, boca::Angle const &phi)
    {
        auto const amag = abs(mag);
        x_ = amag * sin(theta) * cos(phi);
        y_ = amag * sin(theta) * sin(phi);
        z_ = amag * cos(theta);
    }

    constexpr void SetPerpEtaPhi(Value_ const &perp, boca::Angle const &eta, boca::Angle const &phi)
    {
        auto const aperp = abs(perp);
        x_ = aperp * cos(phi);
        y_ = aperp * sin(phi);
        z_ = aperp * units::sinh(eta);
    }

    constexpr void SetPerpEtaPhi(Value_ const &perp, Vector2<boca::Angle> const& eta_phi_vector)
    {
        auto const aperp = abs(perp);
        x_ = aperp * cos(eta_phi_vector.Y());
        y_ = aperp * sin(eta_phi_vector.Y());
        z_ = aperp * units::sinh(eta_phi_vector.X());
    }

    /**
     * @brief Set the transverse component keeping phi and z constant.
     */
    constexpr void SetPerp(Value_ perp)
    {
        auto const old = Perp();
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
     * @brief Getter for X
     */
    constexpr Value_ X() const
    {
        return x_;
    }

    /**
     * @brief Getter for Y
     */
    constexpr Value_ Y() const
    {
        return y_;
    }

    /**
     * @brief Getter for Z
     */
    constexpr Value_ Z() const
    {
        return z_;
    }

    /**
     * @brief Accessor for X
     */
    constexpr Value_ &X()
    {
        return x_;
    }

    /**
     * @brief Accessor for Y
     */
    constexpr Value_ &Y()
    {
        return y_;
    }

    /**
     * @brief Accessor for Z
     */
    constexpr Value_ &Z()
    {
        return z_;
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
        return x_ == Value_(0) && y_ == Value_(0) ? 0_rad : atan2(y_, x_);
    }

    /**
     * @brief The polar angle \f$\theta\f$
     */
    boca::Angle Theta() const
    {
        return x_ == Value_(0) && y_ == Value_(0) && z_ == Value_(0) ? 0_rad : atan2(Perp(), z_);
    }

    /**
     * @brief Cosine of the polar angle \f$\cos \theta\f$
     */
    double CosTheta() const
    {
        auto const mag = Mag();
        return mag == Value_(0) ? 1 : z_ / mag;
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
        auto const cosTheta = CosTheta();
        if (sqr(cosTheta) < 1) return -0.5 * units::log((1 - cosTheta) / (1 + cosTheta));
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
        return sqr(x_) + sqr(y_) + sqr(z_);
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
        return sqr(x_) + sqr(y_);
    }

    /**
     * @brief The transverse component \f$\rho = \sqrt{x^2 + y^2}\f$
     */
    constexpr Value_ Perp() const
    {
        return sqrt(Perp2());
    }

    /**
     * @brief The transverse component \f$x^2 + y^2\f$ to a vector
     */
    template <typename Value_2_>
    constexpr ValueSquare Perp2(Vector3<Value_2_> const &vector) const
    {
        auto const other_mag2 = vector.Mag2();
        auto const mixing = Dot(vector);
        auto this_mag_2 = Mag2();
        if (other_mag2 > boca::ValueSquare<Value_2_>(0)) this_mag_2 -= sqr(mixing) / other_mag2;
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
    void Rotate(boca::Angle const &phi, Dim3 dim_1,  Dim3 dim_2)
    {
        if (phi == 0_rad)  return *this;
        auto const cos = boost::units::cos(phi);
        auto const sin = boost::units::sin(phi);
        auto const row = (*this)(dim_1);
        (*this)(dim_1) = cos * row - sin * (*this)(dim_2);
        (*this)(dim_2) = sin * row + cos * (*this)(dim_2);
        return *this;
    }

    /**
    * @brief Rotate by phi around axis dim
    */
    constexpr void Rotate(boca::Angle const &phi, Dim3 dim)
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
    auto & Rotate(boca::Angle angle, Vector3<Value_2_> const &axis);

    /**
    * @brief Transformation with a Rotation matrix.
    */
    template<typename Value_2_>
    auto & Transform(Matrix3<Value_2_> const& matrix);

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
            x_ = -x_; // phi=0 teta=pi
            z_ = -z_;
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
    constexpr Vector3<double> Unit() const
    {
        auto const mag2 = Mag2();
        if (mag2 == ValueSquare(0)) return {};
        return *this / sqrt(mag2);
    }

    /**
    * @brief Vector orthogonal to this
    */
    constexpr Vector3 Orthogonal() const
    {
        auto const x = x_ < Value_(0) ? -x_ : x_;
        auto const y = y_ < Value_(0) ? -y_ : y_;
        auto const z = z_ < Value_(0) ? -z_ : z_;
        if (x < y) return x < z ? Vector3(Value_(0), z_, -y_) : Vector3(y_, -x_, Value_(0));
        else return y < z ? Vector3(-z_, Value_(0), x_) : Vector3(y_, -x_, Value_(0));
    }

    /**
    * @brief Transversal vector \f$(x, y)\f$
    */
    constexpr Vector2<Value_> Transversal() const
    {
        return {x_, y_};
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
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    /**
    * @brief Dot product between two vector
    */
    template <typename Value_2_>
    constexpr ValueProduct<Value_2_> Dot(Vector3<Value_2_> const &vector) const
    {
        return x_ * vector.X() + y_ * vector.Y() + z_ * vector.Z();
    }

    /**
    * @brief Cross product between two vector
    */
    template <typename Value_2_>
    constexpr Vector3<ValueProduct<Value_2_>> Cross(Vector3<Value_2_> const &vector) const
    {
        return {y_ * vector.Z() - vector.Y() *z_, z_ * vector.X() - vector.Z() *x_, x_ * vector.Y() - vector.X() *y_};
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
        return vector.x_ == x_ && vector.y_ == y_ && vector.z_ == z_;
    }

    /**
    * @brief Sum of two vectors
    */
    template <typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    constexpr Vector3 &operator+=(Vector3<Value_2_> const &vector)
    {
        x_ += vector.x_;
        y_ += vector.y_;
        z_ += vector.z_;
        return *this;
    }

    /**
    * @brief Difference of two vectors
    */
    template <typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    constexpr Vector3 &operator-=(Vector3<Value_2_> const &vector)
    {
        x_ -= vector.x_;
        y_ -= vector.y_;
        z_ -= vector.z_;
        return *this;
    }

    /**
    * @brief Scaling with real numbers
    */
    template < typename Value_2_, typename = OnlyIfNotQuantity<Value_2_> >
    constexpr Vector3 &operator*=(Value_2_ scalar)
    {
        x_ *= scalar;
        y_ *= scalar;
        z_ *= scalar;
        return *this;
    }

    /**
    * @brief Multiplication with a matrix
    */
    template<typename Value_2_>
    auto &operator*=(Matrix3<Value_2_> const& matrix);

    /**
    * @brief division by scalar
    */
    template < typename Value_2_, typename = OnlyIfNotQuantity<Value_2_> >
    constexpr Vector3 &operator/=(Value_2_ scalar)
    {
        x_ /= scalar;
        y_ /= scalar;
        z_ /= scalar;
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
        return { -x_, -y_, -z_};
    }

    /**
    * @brief Components by index
    */
    constexpr Value_ const &operator()(Dim3 dimension) const
    {
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

    /**
    * @brief Components by index
    */
    constexpr Value_ &operator()(Dim3 dimension)
    {
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

    /**
    * @brief Components by index
    */
    constexpr Value_ const &operator[](Dim3 dimension) const
    {
        return operator()(dimension);
    }

    /**
    * @brief Components by index
    */
    constexpr Value_ &operator[](Dim3 dimension)
    {
        return operator()(dimension);
    }
    //@}

    /**
     * @name Iterators
     * @{
     */

    /**
     * @brief Const begin
     */
    constexpr ConstIterator<boca::Vector3, Value_, Dim3> begin() const
    {
        return {this, Dim3::x};
    }

    /**
     * @brief Const end
     */
    constexpr ConstIterator<boca::Vector3, Value_, Dim3> end() const
    {
        return {this, Dim3::last};
    }

    /**
     * @brief begin
     */
    constexpr Iterator<boca::Vector3, Value_, Dim3> begin()
    {
        return {this, Dim3::x};
    }

    /**
     * @brief end
     */
    constexpr Iterator<boca::Vector3, Value_, Dim3> end()
    {
        return {this, Dim3::last};
    }
    //@}

private:

    Value_ x_;

    Value_ y_;

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
