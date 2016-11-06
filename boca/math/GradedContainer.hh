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
    GradedContainer() {}
    GradedContainer(Container_<Value_> const& container, Value_ scalar) :
        container_(container),
        scalar_(scalar)
    {}
    void Set(Container_<Value_> const& container, Value_ scalar)
    {
        container_ = container;
        scalar_ = scalar;
    }
    void Set(Container_<Value_> const& container)
    {
        container_ = container;
    }
    void Set(Value_ scalar)
    {
        scalar_ = scalar;
    }
    Container_<Value_> &Container()
    {
        return container_;
    }
    Container_<Value_> const& Container() const
    {
        return container_;
    }
    Container_<double> Normalize() const
    {
        return container_ / scalar_;
    }
    Value_ const& Scalar() const
    {
        return scalar_;
    }
    Value_ &Scalar()
    {
        return scalar_;
    }
    bool operator<(GradedContainer const &graded_container) const
    {
        return Normalize() < graded_container.Normalize();
    }
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
    Container_<Value_> &Vector()
    {
        return GradedContainer<Container_,  Value_>::Container();
    }
    Container_<Value_> const& Vector() const
    {
        return GradedContainer<Container_,  Value_>::Container();
    }
    GradedVector &operator+=(GradedVector const &graded_container)
    {
        GradedContainer<Container_,  Value_>::Container() += graded_container.Container();
        GradedContainer<Container_,  Value_>::Scalar() += graded_container.Scalar();
        return *this;
    }
    GradedVector &operator-=(GradedVector const &graded_container)
    {
        GradedContainer<Container_,  Value_>::Container() -= graded_container.Container();
        GradedContainer<Container_,  Value_>::Scalar() -= graded_container.Scalar();
        return *this;
    }
};

template<template <typename> class Container_, typename Value_>
class GradedMatrix : public GradedContainer<Container_, Value_>
            , public boost::additive<GradedMatrix<Container_,  Value_>>
{
public:
    using GradedContainer<Container_,  Value_>::GradedContainer;
    Container_<Value_> &Matrix()
    {
        return GradedContainer<Container_, Value_>::Container();
    }
    Container_<Value_> const& Matrix() const
    {
        return GradedContainer<Container_, Value_>::Container();
    }
    GradedMatrix &operator+=(GradedMatrix const &graded_container)
    {
        GradedContainer<Container_,  Value_>::Container() += graded_container.Container();
        GradedContainer<Container_,  Value_>::Scalar() += graded_container.Scalar();
        return *this;
    }
    GradedMatrix &operator-=(GradedMatrix const &graded_container)
    {
        GradedContainer<Container_,  Value_>::Container() -= graded_container.Container();
        GradedContainer<Container_,  Value_>::Scalar() -= graded_container.Scalar();
        return *this;
    }
};

}
