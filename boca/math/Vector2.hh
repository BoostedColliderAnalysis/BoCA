#pragma once

#include <boost/operators.hpp>

#include "boca/generic/Debug.hh"
#include "boca/generic/Iterator.hh"

#include "boca/math/GradedContainer.hh"

#include "boca/physics/Units.hh"

namespace boca
{

/**
* @ingroup Math
* @brief Two dimensions
*
*/
enum class Dim2
{
    x,
    y,
    last
};

std::string Name(Dim2 dimension);

std::vector<Dim2> Dimensions2();

/**
 * @ingroup Math
 * @brief Two dimensional Vector
 */
template<typename Value_>
class Vector2 : public boost::totally_ordered<Vector2<Value_>>
            , public boost::additive<Vector2<Value_>>
{

    template<typename Value_2>
    using ValueProduct = ValueProduct<Value_, Value_2>;

//     template<typename Value_2>
//     using ValueQuotient = ValueQuotient<Value_, Value_2>;

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value_, Value_2>::value >::type;

//     template<typename Value_2>
//     using OnlyIfQuantity = typename std::enable_if < IsQuantity<Value_2>::value>::type;

public:

    /**
    * @name Constructor
    * @{
    */

    /**
    * @brief Default constructor
    */
    Vector2() :
        x_(0) ,
        y_(0)
    {}

    /**
    * @brief Constructor from two scalars
    */
    Vector2(Value_ x, Value_ y) :
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
    template<typename Value_2/*, typename = OnlyIfQuantity<Value_2>*/>
    Vector2(Vector2<Value_2> const &vector) :
        x_(vector.X()),
        y_(vector.Y())
    {}
    //@}

    /**
    * @brief Setter for the magnitude and angle
    */
    void SetMagPhi(Value_ magnitude, Angle const &phi)
    {
        auto absolute = abs(magnitude);
        x_ = absolute * cos(phi);
        y_ = absolute * sin(phi);
    }

    /**
    * @name Accessors and Getters
    * @{
    */

    /**
    * @brief Getter for X
    */
    Value_ X() const
    {
        return x_;
    }

    /**
    * @brief Getter for Y
    */
    Value_ Y() const
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
    * @brief Magnitude square \f$x^2 + y^2\f$
    */
    auto Mag2() const
    {
        return sqr(x_) + sqr(y_);
    }

    /**
    * @brief Magnitude \f$\sqrt{x^2 + y^2}\f$
    */
    Value_ Mag() const
    {
        return sqrt(Mag2());
    }

    /**
    * @brief azimuth defined in \f$[-\pi, \pi]\f$
    */
    Angle Phi() const
    {
        return atan2(y_, x_);
    }

    /**
    * @brief Difference of azimuth defined in \f$[-\pi, \pi]\f$
    */
    template<typename Value_2>
    Angle DeltaPhi(Vector2<Value_2> const &vector) const
    {
        return Restrict(Phi() - vector.Phi());
    }

    /**
     * @brief Unit vector in the direction of *this
     */
    Vector2<double> Unit() const
    {
        return Mag2() ? *this / Mag() : Vector2<double>();
    }

    /**
     * @brief Projection onto the direction of vector
     */
    template <typename Value_2>
    Vector2 Proj(Vector2<Value_2> const &vector) const
    {
        return vector * (*this * vector / vector.Mag2());
    }

    /**
     * @brief Component normal to the vector
     */
    template <typename Value_2>
    Vector2 Norm(Vector2<Value_2> const &vector) const
    {
        return *this - Proj(vector);
    }

    /**
     * @brief rotates 2-vector by phi radians
     */
    Vector2 Rotate(Angle const &phi) const
    {
        return {x_ * cos(phi) - y_ * sin(phi), x_ * sin(phi) + y_ * cos(phi)};
    }

    /**
     * @name Products
     * @{
     */

    /**
    * @brief Dot product
    */
    template <typename Value_2>
    ValueProduct<Value_2> Dot(Vector2<Value_2> const &vector) const
    {
        return x_ * vector.X() + y_ * vector.Y();
    }

    /**
    * @brief Scale with scalar
    */
    template <typename Value_2>
    Vector2 <ValueProduct<Value_2>> Scale(Value_2 const &scalar) const
    {
        return {X() *scalar, Y() *scalar};
    }

    /**
    * @brief Signed area
    */
    template <typename Value_2>
    ValueProduct<Value_2> SignedArea(Vector2<Value_2> const &vector) const
    {
        return X() * vector.Y() - Y() * vector.X();
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
    friend ValueProduct<Value_2> operator^(Vector2 const &vector_1, Vector2<Value_2> const &vector_2)
    {
        return vector_1.SignedArea(vector_2);
    }

    /**
     * @brief Division by scalar
     */
    template <typename Value_2>
    friend auto operator/(Vector2 const &vector, Value_2 const &scalar)
    {
        return vector.Scale(1. / scalar);
    }

    /**
     * @brief Unary minus
     */
    Vector2 operator-() const
    {
        return { -x_, -y_};
    }

    /**
     * @brief Less than comparison
     */
    bool operator<(Vector2 const &vector) const
    {
        return Mag2() < vector.Mag2();
    }

    /**
     * @brief Equal comparison
     */
    bool operator==(Vector2 const &vector) const
    {
        return vector.x_ == x_ && vector.y_ == y_;
    }

    /**
     * @brief Components by index
     */
    Value_ operator()(Dim2 dimension) const
    {
        //dereferencing operator const
        switch (dimension) {
        case Dim2::x :
            return x_;
        case Dim2::y :
            return y_;
        default :
            Debug("Bad index returning x_", Name(dimension));
            return 0;
        }
    }

    /**
     * @brief Components by index
     */
    Value_ operator[](Dim2 dimension) const
    {
        return operator()(dimension);
    }

    /**
     * @brief Components by index
     */
    Value_ &operator()(Dim2 dimension)
    {
        switch (dimension) {
        case Dim2::x :
            return x_;
        case Dim2::y :
            return y_;
        default :
            Debug("Bad index returning x_", Name(dimension));
        }
        return x_;
    }

    /**
     * @brief Components by index
     */
    Value_ &operator[](Dim2 dimension)
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
    ConstIterator<boca::Vector2, Value_, Dim2> begin() const
    {
        return {this, Dim2::x};
    }

    /**
     * @brief Const end
     */
    ConstIterator<boca::Vector2, Value_, Dim2> end() const
    {
        return {this, Dim2::last};
    }

    /**
     * @brief Begin
     */
    Iterator<boca::Vector2, Value_, Dim2> begin()
    {
        return {this, Dim2::x};
    }

    /**
     * @brief End
     */
    Iterator<boca::Vector2, Value_, Dim2> end()
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

