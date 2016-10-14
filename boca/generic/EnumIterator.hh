#pragma once

#include <iterator>
#include <type_traits>

#include <boost/operators.hpp>

namespace boca
{

/**
* @ingroup Iterator
* @brief Enables the use of strongly typed enumerators as iterators
*/
template<typename Enum_>
class EnumIterator : boost::totally_ordered<EnumIterator<Enum_>>,
//             boost::additive<EnumIterator<Enum_>>,
            boost::additive<EnumIterator<Enum_>, std::size_t>,
            boost::unit_steppable<EnumIterator<Enum_>>

{

    using size_type = std::size_t;

    using difference_type = std::ptrdiff_t;

    using value_type = Enum_;

    using reference = Enum_;

    using pointer = Enum_ *;

    using iterator_category = std::random_access_iterator_tag;

    using Type_ = typename std::underlying_type<Enum_>::type;

public:

    /**
    * @name Constructor
    * @{
    */

    /**
    * @brief Default constructor
    */
    constexpr EnumIterator() : enum_() {}

    /**
    * @brief Copy constructor
    */
//     constexpr EnumIterator(EnumIterator const &rhs) : enum_(rhs.enum_) {}

    /**
    * @brief Constructor from enum
    */
    constexpr explicit EnumIterator(Enum_ value) : enum_(value) {}

//     ~EnumIterator() {}

    //@}

    /**
     * @name Setter
     * @{
     */

    /**
     * @brief Set enum
     */
    void Set(Enum_ value)
    {
        enum_ = value;
    }
    //@}

    /**
     * @name Operators
     * @{
     */

    /**
     * @brief Less than comparison
     */
    constexpr bool operator<(EnumIterator const &enum_iterator)
    {
        return enum_ < enum_iterator.enum_;
    }

    /**
     * @brief equality comparison
     */
    constexpr bool operator==(EnumIterator const &enum_iterator)
    {
        return enum_ == enum_iterator.enum_;
    }

    EnumIterator &operator+=(size_type size)
    {
        Add(size);
        return *this;
    }

    EnumIterator &operator-=(size_type size)
    {
        Substract(size);
        return *this;
    }

    EnumIterator &operator++()
    {
        Add(1);
        return *this;
    }

    EnumIterator &operator--()
    {
        Substract(1);
        return *this;
    }

    constexpr difference_type operator-(EnumIterator const& enum_iterator)
    {
        return static_cast<Type_>(enum_) - static_cast<Type_>(enum_iterator.enum_);
    }

    constexpr reference operator*() const
    {
        return enum_;
    }

    constexpr reference operator[](size_type size) const
    {
        return Add(size);
    }

    constexpr const Enum_ *operator->() const
    {
        return &enum_;
    }

//     EnumIterator &operator=(EnumIterator const &rhs)
//     {
//         enum_ = rhs.enum_;
//         return *this;
//     }

//     constexpr EnumIterator operator++(int)
//     {
//         EnumIterator iterator(*this);
//         ++*this;
//         return iterator;
//     }

//     constexpr friend EnumIterator operator+(EnumIterator const &it, size_type size)
//     {
//         return it.Add(size);
//     }
//
//     constexpr friend EnumIterator operator+(size_type size, EnumIterator const &it)
//     {
//         return it.Add(size);
//     }

//     constexpr EnumIterator operator--(int)
//     {
//         EnumIterator iterator(*this);
//         --*this;
//         return iterator;
//     }

//     friend EnumIterator operator-(EnumIterator const &it, size_type size)
//     {
//         return it.Substract(size);
//     }

//     constexpr friend bool operator!=(EnumIterator const& lhs, EnumIterator const& rhs) {
//         return lhs.enum_ != rhs.enum_;
//     }

//     constexpr friend bool operator>(EnumIterator const& lhs, EnumIterator const& rhs) {
//         return lhs.enum_ > rhs.enum_;
//     }
//
//     constexpr friend bool operator<=(EnumIterator const& lhs, EnumIterator const& rhs) {
//         return lhs.enum_ <= rhs.enum_;
//     }
//
//     constexpr friend bool operator>=(EnumIterator const& lhs, EnumIterator const& rhs) {
//         return lhs.enum_ >= rhs.enum_;
//     }

    constexpr friend void swap(EnumIterator const &lhs, EnumIterator const &rhs)
    {
        std::swap(lhs.enum_, rhs.enum_);
    }

private:

    Enum_ enum_;

    Enum_ Add(size_type size)
    {
        enum_ = static_cast<Enum_>(static_cast<Type_>(enum_) + size);
        return enum_;
    }

    Enum_ Substract(size_type size)
    {
        enum_ = static_cast<Enum_>(static_cast<Type_>(enum_) - size);
        return enum_;
    }

};

}
