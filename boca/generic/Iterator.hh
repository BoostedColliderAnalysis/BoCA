#pragma once

#include <iostream>
#include <boost/iterator_adaptors.hpp>

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
template <template <typename> class Container_, typename Value_, typename Enum_>
class Iterator
{
public:
    Iterator(Container_<Value_> *container, Enum_ position) :
        position_(position),
        container_(container)
    {}

    bool operator!= (Iterator &iterator) const
    {
        return position_ != iterator.position_;
    }

    Value_ &operator*()
    {
        return (*container_)[*position_];
    }

    Iterator const &operator++ ()
    {
        ++position_;
        return *this;
    }

private:
    EnumIterator<Enum_> position_;
    Container_<Value_> *container_;
};

/**
* @brief const iterator
*/
template <template <typename> class Container_, typename Value_, typename Enum_>
class ConstIterator
{
public:
    ConstIterator(Container_<Value_> const *container, Enum_ position) :
        position_(position),
        container_(container)
    {}

    bool operator!= (ConstIterator const &iterator) const
    {
        return position_ != iterator.position_;
    }

    Value_ operator*() const
    {
        return (*container_)[*position_];
    }

    ConstIterator const &operator++ ()
    {
        ++position_;
        return *this;
    }

private:
    EnumIterator<Enum_> position_;
    Container_<Value_> const *container_;
};

/**
 * @brief %Iterator
 */
template <template <typename> class Container_, template <typename> class SubContainer_, typename Value_, typename Enum_>
class SubIterator
{
public:
    SubIterator(Container_<Value_> *container, Enum_ position) :
        position_(position),
        container_(container)
    {}

    bool operator!= (SubIterator const &iterator) const
    {
        return position_ != iterator.position_;
    }

    SubContainer_<Value_> &operator*()
    {
        return (*container_)[*position_];
    }

    SubIterator const &operator++ ()
    {
        ++position_;
        return *this;
    }

private:
    EnumIterator<Enum_> position_;
    Container_<Value_> *container_;
};

/**
 * @brief Const sub-iterator
 */
template <template <typename> class Container_, template <typename> class SubContainer_, typename Value_, typename Enum_>
class ConstSubIterator
{
public:
    ConstSubIterator(Container_<Value_> const *container, Enum_ position) :
        position_(position),
        container_(container)
    {}

    bool operator!= (ConstSubIterator const &iterator) const
    {
        return position_ != iterator.position_;
    }

    SubContainer_<Value_> operator*() const
    {
        return (*container_)[*position_];
    }

    ConstSubIterator const &operator++ ()
    {
        ++position_;
        return *this;
    }

private:
    EnumIterator<Enum_> position_;
    Container_<Value_> const *container_;
};


template<typename Value_>
std::string Name(Value_ value);


template <template <typename> class Container_,
         typename Value_,
         typename Enum_>
class IteratorTest : public boost::iterator_adaptor <
IteratorTest<Container_, Value_, Enum_>,
    Container_<Value_> *,
    boost::use_default,
//     EnumIterator<Enum_>,
//     boost::use_default,
                              boost::random_access_traversal_tag,
    Value_,
    boost::use_default
    >
{

    struct enabler {};

public:

  IteratorTest(Container_<Value_> *container, Enum_ position) :
  IteratorTest::iterator_adaptor_(container),
        position_(position)
    {
        std::cout << "construc: " << Name(position) << '\n';
    }


private:

    Value_ dereference() const {
        std::cout << "deref: " << (*this->base())[*position_] << '\n';
        return (*this->base())[*position_];
    }

    friend class boost::iterator_core_access;

    void increment() {
        std::cout << "inc: " << Name(*position_) << '\n';
        ++position_;
    }

    void decrement() {
         std::cout << "inc: " << Name(*position_) << '\n';
        --position_;
    }

    EnumIterator<Enum_> position_;

};

}

// namespace boost
// {
//   // specialize range_mutable_iterator and range_const_iterator in
//   // namespace boost
//   template<template <typename> class T, class V, class D>
//   struct range_mutable_iterator< boca::Iterator<T, V, D> > {
//     typedef typename boca::Iterator<T, V, D>::const_iterator type;
//   };
//
//   template<template <typename> class T, class V, class D>
//   struct range_const_iterator< boca::Iterator<T, V, D> > {
//     typedef typename boca::Iterator<T, V, D>::const_iterator type;
//   };
// }

/*
 * @}
 */
