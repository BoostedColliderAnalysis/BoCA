#pragma once

#include <boost/operators.hpp>

#include "TVector2.h"

#include "boca/generic/Debug.hh"
#include "boca/generic/Iterator.hh"

#include "boca/units/Units.hh"
#include "boca/math/Math.hh"

namespace boca
{

/**
* @ingroup Math
* @brief Two dimensionss
*
*/
enum class Dim2
{
    x,
    y,
    last
};

std::string Name(Dim2 dim_2);

std::vector<Dim2> Dimensions2();

/**
 * @ingroup Math
 * @brief Two dimensional Vector
 */
template<typename Value_>
class Vector2 : boost::totally_ordered<Vector2<Value_>>
            , boost::additive<Vector2<Value_>>
{

    template<typename Value_2>
    using ValueProduct = ValueProduct<Value_, Value_2>;

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value_, Value_2>::value >::type;

public:

    /**
    * @name Constructor
    * @{
    */

    /**
    * @brief Default constructor
    */
    constexpr Vector2() :
        x_(0) ,
        y_(0)
    {}

    /**
    * @brief Constructor from two scalars
    */
    constexpr Vector2(Value_ x, Value_ y) :
        x_(x) ,
        y_(y)
    {}

    /**
     * @brief Constructor one scalar and its direction
     */
    Vector2(Value_ value, Dim2 dim)
    {
        x_ = dim == Dim2::x ? value : Value_(0);
        y_ = dim == Dim2::y ? value : Value_(0);
    }

    /**
    * @brief Constructor from a two-vector
    */
    template<typename Value_2>
    constexpr Vector2(Vector2<Value_2> const &vector) :
        x_(vector.X()),
        y_(vector.Y())
    {}

    /**
     * @brief Constructor accepting a root::TVector2
     */
    constexpr Vector2(TVector2 const &vector) :
        x_(vector.X()),
        y_(vector.Y())
    {}

    //@}

    /**
    * @name Setter
    * @{
    */

    /**
     * @brief Set both both entries according to the value
     */
    void SetUniform(Value_ value)
    {
        x_ = value;
        y_ = value;
    }

    /**
    * @brief Setter for the magnitude and angle
    */
    void SetMagPhi(Value_ magnitude, Angle const &phi)
    {
        SetUniform(abs(magnitude));
        x_ *= static_cast<double>(cos(phi));
        y_ *= static_cast<double>(sin(phi));
    }

    /**
     * @brief Set the magnitude keeping \f$\phi\f$ constant
     */
    void SetMag(Value_ mag)
    {
        auto const old = Mag();
        if (old == Value_(0)) return;
        (*this) *= static_cast<double>(mag / old);
    }

    /**
     * @brief Set azimuth \f$\phi\f$ keeping the magnitue constant
     */
    void SetPhi(boca::Angle const &phi)
    {
        SetMagPhi(Mag(), phi);
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
        return x_;
    }

    /**
    * @brief Getter for Y
    */
    constexpr Value_ const& Y() const
    {
        return y_;
    }

    /**
    * @brief Accessor for X
    */
    Value_ &X()
    {
        return x_;
    }

    /**
    * @brief Accessor for Y
    */
    Value_ &Y()
    {
        return y_;
    }

    //@}

    /**
    * @name Magnitudes
    * @{
    */

    /**
    * @brief Square of the magnitude \f$x^2 + y^2\f$
    */
    constexpr auto Mag2() const
    {
        return sqr(x_) + sqr(y_);
    }

    /**
    * @brief Magnitude \f$\sqrt{x^2 + y^2}\f$
    */
    constexpr Value_ Mag() const
    {
        return sqrt(Mag2());
    }

    //@}

    /**
    * @name Angles
    * @{
    */

    /**
    * @brief The azimuth \f$\phi\f$ defined in \f$[-\pi, \pi]\f$
    */
    Angle Phi() const
    {
        return Angle(atan2(Y(), X()));
    }

    /**
    * @brief Difference of azimuth \f$\Delta\phi\f$ defined in \f$[-\pi, \pi]\f$
    */
    template<typename Value_2>
    Angle DeltaPhiTo(Vector2<Value_2> const &vector) const
    {
        return Restrict(Phi() - vector.Phi());
    }

    //@}

    /**
    * @name Vectors
    * @{
    */

    /**
     * @brief Unit vector in the direction of this vector
     */
    constexpr auto Unit() const
    {
        auto mag = Mag();
        return mag > Value_(0) ? Vector2<double>{*this / mag} :  Vector2<double>{};
    }

    /**
     * @brief Projection onto the direction of vector
     */
    template <typename Value_2>
    constexpr auto Project(Vector2<Value_2> const &vector) const
    {
        auto const unit = vector.Unit();
        return (*this * unit) * unit;
    }

    /**
     * @brief Component normal to the vector
     */
    template <typename Value_2>
    constexpr Vector2 Norm(Vector2<Value_2> const &vector) const
    {
        return *this - Project(vector);
    }

    /**
     * @brief Rotate this vector by \f$\phi\f$
     */
    Vector2 &Rotate(Angle const &phi)
    {
        auto const cos = boost::units::cos(phi);
        auto const sin = boost::units::sin(phi);
        *this = {x_ *cos - y_ * sin, x_ *sin + y_ * cos};
        return *this;
    }

    /**
     * @brief Rotate this vector by \f$\phi\f$
     */
    Vector2 Rotate(Angle const &phi) const
    {
        auto vector = *this;
        return vector.Rotate(phi);
    }

    //@}

    /**
     * @name Products
     * @{
     */

    /**
    * @brief Dot product between two vectors
    */
    template <typename Value_2>
    constexpr ValueProduct<Value_2> Dot(Vector2<Value_2> const &vector) const
    {
        return x_ * vector.X() + y_ * vector.Y();
    }

    /**
    * @brief Scale this vector with a scalar
    */
    template <typename Value_2>
    Vector2 <ValueProduct<Value_2>> Scale(Value_2 const &scalar) const
    {
        return {x_ *scalar, y_ *scalar};
    }

    /**
    * @brief Signed area
    */
    template <typename Value_2>
    constexpr ValueProduct<Value_2> SignedArea(Vector2<Value_2> const &vector) const
    {
        return x_ * vector.Y() - y_ * vector.X();
    }
    //@}

    /**
    * @name Operators
    * @{
    */

    /**
    * @brief Assignment operator including casting
    */
    template <typename Value_2/*, typename = OnlyIfQuantity<Value_2>*/>
    Vector2 &operator=(Vector2<Value_2> const &vector)
    {
        x_ = Value_(vector.X());
        y_ = Value_(vector.Y());
        return *this;
    }

    /**
    * @brief Sum of two vectors
    */
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2 &operator+=(Vector2<Value_2> const &vector)
    {
        x_ += vector.x_;
        y_ += vector.y_;
        return *this;
    }

    /**
    * @brief Difference of two vectors
    */
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2 &operator-=(Vector2<Value_2> const &vector)
    {
        x_ -= vector.x_;
        y_ -= vector.y_;
        return *this;
    }

    /**
     * @brief Product with scalar
     */
    template < typename Value_2, typename = OnlyIfNotQuantity<Value_2> >
    Vector2 &operator*=(Value_2 scalar)
    {
        x_ *= scalar;
        y_ *= scalar;
        return *this;
    }

    /**
     * @brief Division by scalar
     */
    template < typename Value_2, typename = OnlyIfNotQuantity<Value_2> >
    Vector2 &operator/=(Value_2 scalar)
    {
        x_ /= scalar;
        y_ /= scalar;
        return *this;
    }

    /**
     * @brief Coefficient of wedge product
     */
    template<typename Value_2>
    constexpr friend ValueProduct<Value_2> operator^(Vector2 const &vector_1, Vector2<Value_2> const &vector_2)
    {
        return vector_1.SignedArea(vector_2);
    }

    /**
     * @brief Division by scalar
     */
    template <typename Value_2>
    constexpr friend auto operator/(Vector2 const &vector, Value_2 const &scalar)
    {
        return vector.Scale(1. / scalar);
    }

    /**
     * @brief Unary minus
     */
    constexpr Vector2 operator-() const
    {
        return { -x_, -y_};
    }

    /**
     * @brief Less than comparison
     */
    constexpr bool operator<(Vector2 const &vector) const
    {
        return Mag2() < vector.Mag2();
    }

    /**
     * @brief Equal comparison
     */
    constexpr bool operator==(Vector2 const &vector) const
    {
        return vector.x_ == x_ && vector.y_ == y_;
    }

    /**
     * @brief Components by index
     */
    Value_ const &operator[](Dim2 dim_2) const
    {
        switch (dim_2) {
        case Dim2::x :
            return x_;
        case Dim2::y :
            return y_;
        default :
            Default("Matrix2", Name(dim_2));
            return x_;
        }
    }

    /**
     * @brief Components by index
     */
    Value_ &operator[](Dim2 dim_2)
    {
        return const_cast<Value_ &>(static_cast<Vector2<Value_> const &>(*this)[dim_2]);
    }

    /**
     * @brief Output stream operator
     */
    friend auto &operator<<(std::ostream &stream, Vector2<Value_> const &vector)
    {
        stream << Stream(vector.X()) << Stream(vector.Y());
        return stream;
    }

    //@}

    /**
     * @name Iterators
     * @{
     */

    using Dimension = Dim2;

    /**
     * @brief Const begin
     */
    constexpr ConstIterator<boca::Vector2, Value_> begin() const
    {
        return {this, Dim2::x};
    }

    /**
     * @brief Const end
     */
    constexpr ConstIterator<boca::Vector2, Value_> end() const
    {
        return {this, Dim2::last};
    }

    /**
     * @brief Begin
     */
    Iterator<boca::Vector2, Value_> begin()
    {
        return {this, Dim2::x};
    }

    /**
     * @brief End
     */
    Iterator<boca::Vector2, Value_> end()
    {
        return {this, Dim2::last};
    }
    //@}

private:

    Value_ x_;

    Value_ y_;
};

template <typename>
struct IsVector2 : std::false_type {};

template <typename Value_>
struct IsVector2<Vector2<Value_>> : std::true_type {};

template<typename Value_>
using OnlyIfNotVector2 = typename std::enable_if < !IsVector2<Value_>::value >::type;

/**
 * @brief Dot product
 */
template <class Value_, class Value_2>
auto operator*(Vector2<Value_> const &vector_1, const Vector2<Value_2> &vector_2)
{
    return vector_1.Dot(vector_2);
}

/**
 * @brief Scalar from the right
 */
template < class Value_, class Value_2, typename = OnlyIfNotVector2<Value_2> >
auto operator*(Vector2<Value_> const &vector, Value_2 const &scalar)
{
    return vector.Scale(scalar);
}

/**
 * @brief Scalar from the left
 */
template < class Value_, class Value_2, typename = OnlyIfNotVector2<Value_> >
auto operator*(Value_ const &scalar, Vector2<Value_2> const &vector)
{
    return vector.Scale(scalar);
}

}

namespace boost{

template<typename Value_>
struct range_const_iterator< boca::Vector2<Value_> > {
    typedef typename boca::ConstIterator<boca::Vector2, Value_> type;
};

template<typename Value_>
struct range_mutable_iterator< boca::Vector2<Value_> > {
    typedef typename boca::Iterator<boca::Vector2, Value_> type;
};

}
