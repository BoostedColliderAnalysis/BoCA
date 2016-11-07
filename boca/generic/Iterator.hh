#pragma once

#include <boost/range/mutable_iterator.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include "boca/generic/EnumIterator.hh"

namespace boca
{

/**
 * @ingroup Generic
 * @defgroup Iterator Iterator
 * @brief Enum based iterators
 * @{
 */

/**
* @brief %Iterator
*/
template <template <typename> class Container_, typename Value_>
class Iterator : public boost::iterator_facade <
    Iterator<Container_, Value_>,
    Container_<Value_>,
    std::bidirectional_iterator_tag,
    Value_ &
    >
{
    using Dimension = typename Container_<Value_>::Dimension;
public:
    Iterator() :
        container_(0),
        position_(0)
    {}

    Iterator(Container_<Value_> *container, Dimension position) :
        container_(container),
        position_(position)
    {}

    template<template <typename> class Container_2_>
    Iterator(Iterator<Container_2_, Value_> const &iterator) :
        container_(iterator.container_),
        position_(iterator.position_)
    {}

private:

    friend class boost::iterator_core_access;
    template <template <typename> class , typename > friend class ConstIterator;

    Value_ &dereference() const
    {
        return (*container_)[*position_];
    }

    template<template <typename> class Container_2_>
    bool equal(Iterator<Container_2_, Value_> const &iterator) const
    {
        return this->position_ == iterator.position_ && this->container_ ==  iterator.container_;
    }

    void increment()
    {
        ++position_;
    }

    void decrement()
    {
        --position_;
    }

    Container_<Value_> *container_;

    EnumIterator<Dimension> position_;
};

/**
 * @brief const iterator
 */
template <template <typename> class Container_,
          typename Value_>
class ConstIterator : public boost::iterator_facade <
    ConstIterator<Container_, Value_>,
    Container_<Value_> const,
    std::bidirectional_iterator_tag,
    Value_ const&
    >
{
    using Dimension = typename Container_<Value_>::Dimension;
public:
    ConstIterator() :
        container_(0),
        position_(0)
    {}

    ConstIterator(Container_<Value_> const* container, Dimension position) :
        container_(container),
        position_(position)
    {}

    template<template <typename> class Container_2_>
    ConstIterator(ConstIterator<Container_2_, Value_> const &iterator) :
        container_(iterator.container_),
        position_(iterator.position_)
    {}

private:

    friend class boost::iterator_core_access;
    template <template <typename> class , typename > friend class Iterator;

    Value_ const& dereference() const
    {
        return (*container_)[*position_];
    }

    template<template <typename> class Container_2_>
    bool equal(ConstIterator<Container_2_, Value_> const &iterator) const
    {
        return this->position_ == iterator.position_ && this->container_ ==  iterator.container_;
    }

    void increment()
    {
        ++position_;
    }

    void decrement()
    {
        --position_;
    }

    Container_<Value_> const* container_;

    EnumIterator<Dimension> position_;
};

/**
 * @brief %Iterator
 */
template <template <typename> class Container_, template <typename> class SubContainer_, typename Value_>
class SubIterator : public boost::iterator_facade <
    SubIterator<Container_, SubContainer_, Value_>,
    Container_<Value_>,
    std::bidirectional_iterator_tag,
    SubContainer_<Value_> &
    >
{
    using Dimension = typename Container_<Value_>::Dimension;
public:
    SubIterator() :
        container_(0),
        position_(0)
    {}

    SubIterator(Container_<Value_> *container, Dimension position) :
        container_(container),
        position_(position)
    {}

    template<template <typename> class Container_2_>
    SubIterator(SubIterator<Container_2_, SubContainer_, Value_> const &iterator) :
        container_(iterator.container_),
        position_(iterator.position_)
    {}

private:

    friend class boost::iterator_core_access;
    template <template <typename> class, template <typename> class, typename > friend class ConstSubIterator;

    SubContainer_<Value_> &dereference() const
    {
        return (*container_)[*position_];
    }

    template<template <typename> class Container_2_>
    bool equal(SubIterator<Container_2_,SubContainer_, Value_> const &iterator) const
    {
        return this->position_ == iterator.position_ && this->container_ ==  iterator.container_;
    }

    void increment()
    {
        ++position_;
    }

    void decrement()
    {
        --position_;
    }

    Container_<Value_> *container_;

    EnumIterator<Dimension> position_;
};

/**
 * @brief Const sub-iterator
 */
template <template <typename> class Container_, template <typename> class SubContainer_, typename Value_>
class ConstSubIterator : public boost::iterator_facade <
    ConstSubIterator<Container_, SubContainer_, Value_>,
    Container_<Value_> const,
    std::bidirectional_iterator_tag,
    SubContainer_<Value_> const&
    >
{
    using Dimension = typename Container_<Value_>::Dimension;
public:
    ConstSubIterator() :
        container_(0),
        position_(0)
    {}

    ConstSubIterator(Container_<Value_> const* container, Dimension position) :
        container_(container),
        position_(position)
    {}

    template<template <typename> class Container_2_>
    ConstSubIterator(ConstSubIterator<Container_2_, SubContainer_, Value_> const &iterator) :
        container_(iterator.container_),
        position_(iterator.position_)
    {}

private:

    friend class boost::iterator_core_access;
    template <template <typename> class, template <typename> class, typename > friend class SubIterator;

    SubContainer_<Value_> const& dereference() const
    {
        return (*container_)[*position_];
    }

    template<template <typename> class Container_2_>
    bool equal(ConstSubIterator<Container_2_, SubContainer_, Value_> const &iterator) const
    {
        return this->position_ == iterator.position_ && this->container_ ==  iterator.container_;
    }

    void increment()
    {
        ++position_;
    }

    void decrement()
    {
        --position_;
    }

    Container_<Value_> const* container_;

    EnumIterator<Dimension> position_;
};

}

/*
 * @}
 */
