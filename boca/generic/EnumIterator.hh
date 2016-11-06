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
class EnumIterator : boost::random_access_iteratable<EnumIterator<Enum_>, Enum_ *, std::ptrdiff_t, Enum_>
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
    * @brief Constructor from enum
    */
    constexpr explicit EnumIterator(Enum_ value) : enum_(value) {}
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
    constexpr bool operator<(EnumIterator const &enum_iterator) const
    {
        return enum_ < enum_iterator.enum_;
    }

    /**
     * @brief equality comparison
     */
    constexpr bool operator==(EnumIterator const &enum_iterator) const
    {
        return enum_ == enum_iterator.enum_;
    }

    /**
     * @brief increment by integer
     */
    EnumIterator &operator+=(size_type size)
    {
        Add(size);
        return *this;
    }

    /**
     * @brief decrement by integer
     */
    EnumIterator &operator-=(size_type size)
    {
        Substract(size);
        return *this;
    }

    /**
     * @brief increment
     */
    EnumIterator &operator++()
    {
        Add();
        return *this;
    }

    /**
     * @brief decrement
     */
    EnumIterator &operator--()
    {
        Substract();
        return *this;
    }

    /**
     * @brief substruction
     */
    constexpr difference_type operator-(EnumIterator const& enum_iterator) const
    {
        return static_cast<Type_>(enum_) - static_cast<Type_>(enum_iterator.enum_);
    }

    /**
     * @brief reference
     */
    constexpr reference operator*() const
    {
        return enum_;
    }
    //@}

    constexpr friend void swap(EnumIterator const &lhs, EnumIterator const &rhs)
    {
        std::swap(lhs.enum_, rhs.enum_);
    }

private:

    Enum_ enum_;

    void Add(size_type size = 1)
    {
        enum_ = static_cast<Enum_>(static_cast<Type_>(enum_) + size);
    }

    void Substract(size_type size = 1)
    {
        enum_ = static_cast<Enum_>(static_cast<Type_>(enum_) - size);
    }

};

}
