#pragma once

#include <iterator>
#include <type_traits>

namespace boca
{

/**
* @ingroup Iterator
* @brief Enables the use of strongly typed enumerators as iterators
*/
template<typename Enum_>
class EnumIterator
{
public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = Enum_;
    using reference = Enum_;
    using pointer = Enum_* ;
    using iterator_category = std::random_access_iterator_tag;

    constexpr EnumIterator() : enum_() {}

    constexpr EnumIterator(EnumIterator const& rhs) : enum_(rhs.enum_) {}

    constexpr explicit EnumIterator(Enum_ value) : enum_(value) {}

    ~EnumIterator() {}

    void Set(Enum_ value) {
        enum_ = value;
    }

    EnumIterator& operator=(EnumIterator const& rhs) {
        enum_ = rhs.enum_;
        return *this;
    }

    EnumIterator& operator++() {
        Add(1);
        return *this;
    }

    EnumIterator operator++(int) {
        EnumIterator iterator(*this);
        ++*this;
        return iterator;
    }

    EnumIterator& operator+=(size_type size) {
        Add(size);
        return *this;
    }

    friend EnumIterator operator+(EnumIterator const& it, size_type size) {
        return it.Add(size);
    }

    friend EnumIterator operator+(size_type size, EnumIterator const& it) {
        return it.Add(size);
    }

    EnumIterator& operator--() {
        Substract(1);
        return *this;
    }

    EnumIterator operator--(int) {
        EnumIterator iterator(*this);
        --*this;
        return iterator;
    }

    EnumIterator& operator-=(size_type size) {
        Add(size);
        return *this;
    }

    friend EnumIterator operator-(EnumIterator const& it, size_type size) {
        return it.Substract(size);
    }

    friend constexpr difference_type operator-(EnumIterator lhs, EnumIterator rhs) {
        return static_cast<Type_>(lhs.enum_) - static_cast<Type_>(rhs.enum_);
    }

    constexpr reference operator*() const {
        return enum_;
    }

    constexpr reference operator[](size_type size) const {
        return Add(size);
    }

    constexpr const Enum_* operator->() const {
        return &enum_;
    }

    constexpr friend bool operator==(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ == rhs.enum_;
    }

    constexpr friend bool operator!=(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ != rhs.enum_;
    }

    constexpr friend bool operator<(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ < rhs.enum_;
    }

    constexpr friend bool operator>(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ > rhs.enum_;
    }

    constexpr friend bool operator<=(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ <= rhs.enum_;
    }

    constexpr friend bool operator>=(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ >= rhs.enum_;
    }

    friend void swap(EnumIterator const& lhs, EnumIterator const& rhs) {
        std::swap(lhs.enum_, rhs.enum_);
    }

private:

    Enum_ enum_;

    using Type_ = typename std::underlying_type<Enum_>::type;

    Enum_ Add(size_type size) {
        enum_ = static_cast<Enum_>(static_cast<Type_>(enum_) + size);
        return enum_;
    }

    Enum_ Substract(size_type size) {
        enum_ = static_cast<Enum_>(static_cast<Type_>(enum_) - size);
        return enum_;
    }

};

}
