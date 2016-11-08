#pragma once

#include <boost/operators.hpp>

namespace boca
{

/**
 * @ingroup Math
 * @brief Container with associated scalar
 */
template<template <typename> class Container_, typename Value_>
class GradedContainer : boost::totally_ordered<GradedContainer<Container_,  Value_>>
{

public:

    /**
    * @name Constructor
    * @{
    */

    /**
     * @brief Default Constructor
     */
    GradedContainer() {}

    /**
     * @brief Constructor accepting a Container and a Scalar
     */
    GradedContainer(Container_<Value_> const& container, Value_ scalar) :
        container_(container),
        scalar_(scalar)
    {}

    //@}

    /**
    * @name Setter
    * @{
    */

    /**
     * @brief Set Container and Scalar
     */
    void Set(Container_<Value_> const& container, Value_ scalar)
    {
        container_ = container;
        scalar_ = scalar;
    }

    /**
     * @brief Set Container
     */
    void Set(Container_<Value_> const& container)
    {
        container_ = container;
    }

    /**
     * @brief Set Scalar
     */
    void Set(Value_ scalar)
    {
        scalar_ = scalar;
    }

    //@}

    /**
    * @name Accessor and Getter
    * @{
    */

    /**
     * @brief Getter for Container
     */
    Container_<Value_> const& Container() const
    {
        return container_;
    }

    /**
     * @brief Accessor of Container
     */
    Container_<Value_> &Container()
    {
        return container_;
    }

    /**
     * @brief Getter for Scalar
     */
    Value_ const& Scalar() const
    {
        return scalar_;
    }

    /**
     * @brief Accessor for Scalar
     */
    Value_ &Scalar()
    {
        return scalar_;
    }

    //@}

    /**
    * @name Products and Quotients
    * @{
    */

    /**
     * @brief Product
     */
    auto Product() const
    {
        return container_ * scalar_;
    }

    /**
     * @brief Quotient
     */
    Container_<double> Normalize() const
    {
        return container_ / scalar_;
    }

    //@}

    /**
    * @name Operator
    * @{
    */

    /**
     * @brief Less than comparison
     */
    bool operator<(GradedContainer const &graded_container) const
    {
        return Normalize() < graded_container.Normalize();
    }

    /**
     * @brief Equallity comparison
     */
    bool operator==(GradedContainer const &graded_container) const
    {
        return container_ == graded_container.container_ && scalar_ == graded_container.scalar_;
    }

    /**
     * @brief Output stream operator
     */
    friend auto &operator<<(std::ostream &stream, GradedContainer const &graded_container)
    {
        stream << Stream(graded_container.scalar_) << graded_container.container_;
        return stream;
    }

    //@}

private:

    Container_<Value_> container_;

    Value_ scalar_ = Value_(0);

};

template<template <typename> class Container_, typename Value_>
class GradedVector : public GradedContainer<Container_,  Value_>
            , public boost::additive<GradedVector<Container_,  Value_>>
{

public:

    using GradedContainer<Container_,  Value_>::GradedContainer;

    /**
    * @name Accessor and Getter
    * @{
    */

    /**
     * @brief Accessor for Vector
     */
    Container_<Value_> &Vector()
    {
        return GradedContainer<Container_,  Value_>::Container();
    }

    /**
     * @brief Getter for Vector
     */
    Container_<Value_> const& Vector() const
    {
        return GradedContainer<Container_,  Value_>::Container();
    }

    //@}

    /**
    * @name Operator
    * @{
    */

    /**
     * @brief Addiition
     */
    GradedVector &operator+=(GradedVector const &graded_container)
    {
        GradedContainer<Container_,  Value_>::Container() += graded_container.Container();
        GradedContainer<Container_,  Value_>::Scalar() += graded_container.Scalar();
        return *this;
    }

    /**
     * @brief Substraction
     */
    GradedVector &operator-=(GradedVector const &graded_container)
    {
        GradedContainer<Container_,  Value_>::Container() -= graded_container.Container();
        GradedContainer<Container_,  Value_>::Scalar() -= graded_container.Scalar();
        return *this;
    }

    //@}

};

template<template <typename> class Container_, typename Value_>
class GradedMatrix : public GradedContainer<Container_, Value_>
            , public boost::additive<GradedMatrix<Container_,  Value_>>
{

public:

    using GradedContainer<Container_,  Value_>::GradedContainer;

    /**
    * @name Accessor and Getter
    * @{
    */

    /**
     * @brief Accessor for Matrix
     */
    Container_<Value_> &Matrix()
    {
        return GradedContainer<Container_, Value_>::Container();
    }

    /**
     * @brief Getter for Matrix
     */
    Container_<Value_> const& Matrix() const
    {
        return GradedContainer<Container_, Value_>::Container();
    }

    //@}

    /**
    * @name Operator
    * @{
    */

    /**
     * @brief Addition
     */
    GradedMatrix &operator+=(GradedMatrix const &graded_container)
    {
        GradedContainer<Container_,  Value_>::Container() += graded_container.Container();
        GradedContainer<Container_,  Value_>::Scalar() += graded_container.Scalar();
        return *this;
    }

    /**
     * @brief Substraction
     */
    GradedMatrix &operator-=(GradedMatrix const &graded_container)
    {
        GradedContainer<Container_,  Value_>::Container() -= graded_container.Container();
        GradedContainer<Container_,  Value_>::Scalar() -= graded_container.Scalar();
        return *this;
    }

    //@}

};

}
