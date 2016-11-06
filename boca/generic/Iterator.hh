#pragma once

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
// template <template <typename> class Container_, typename Value_, typename Enum_>
// class Iterator
// {
// public:
//     Iterator(Container_<Value_> *container, Enum_ position) :
//         position_(position),
//         container_(container)
//     {}
//
//     bool operator!= (Iterator &iterator) const
//     {
//         return position_ != iterator.position_;
//     }
//
//     Value_ &operator*()
//     {
//         return (*container_)[*position_];
//     }
//
//     Iterator const &operator++ ()
//     {
//         ++position_;
//         return *this;
//     }
//
// private:
//     EnumIterator<Enum_> position_;
//     Container_<Value_> *container_;
// };

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

template <template <typename> class Container_,
          typename Value_,
          typename Enum_>
class Iterator : public boost::iterator_adaptor <
                          Iterator<Container_, Value_, Enum_>,
                          Container_<Value_> *,
                          boost::use_default,
                          boost::use_default,
//                           boost::bidirectional_iterator_tag,
                          Value_,
                          boost::use_default
                          >
{

    struct enabler {};

public:

//     Iterator() :
//         Iterator::iterator_adaptor_(0) {}
//
//     explicit Iterator(Value_ * value) :
//         Iterator::iterator_adaptor_(value) {}

    Iterator(Container_<Value_> *container, Enum_ position) :
        Iterator::iterator_adaptor_(container),
        position_(position)
        {}

//     template <class Value_2>
//     Iterator(Iterator<Value_2> const &other, typename boost::enable_if <boost::is_convertible<Value_2 *, Value_ *>, enabler>::type = enabler()) :
//         Iterator::iterator_adaptor_(other.base()) {}

private:

    Value_ dereference() const{
        return (*this->base())[*position_];
    }

    friend class boost::iterator_core_access;

    void increment() { ++position_; }

    void decrement() { --position_; }

    EnumIterator<Enum_> position_;

};

}

/*
 * @}
 */
