#pragma once

#include <iterator>
#include <type_traits>

namespace boca
{

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

    void Set(Enum_ value){
      enum_ = value;
    }

    EnumIterator& operator=(EnumIterator const& rhs) {
        enum_ = rhs.enum_;
        return *this;
    }

    EnumIterator& operator++() {
        enum_ = Add(enum_, 1);
        return *this;
    }

    EnumIterator operator++(int) {
        EnumIterator iterator(*this);
        ++*this;
        return iterator;
    }

    EnumIterator& operator+=(size_type size) {
        enum_ = Add(enum_, size);
        return *this;
    }

    friend constexpr EnumIterator operator+(EnumIterator const& it, size_type size) {
        return EnumIterator(Add(it, size));
    }

    friend constexpr EnumIterator operator+(size_type size, EnumIterator const& it) {
        return EnumIterator(Add(it, size));
    }

    EnumIterator& operator--() {
        enum_ = Substract(enum_, 1);
        return *this;
    }

    EnumIterator operator--(int) {
        EnumIterator iterator(*this);
        --*this;
        return iterator;
    }

    EnumIterator& operator-=(size_type size) {
        enum_ = Add(enum_, size);
        return *this;
    }

    friend constexpr EnumIterator operator-(EnumIterator const& it, size_type size) {
        return EnumIterator(Substract(it, size));
    }

    friend constexpr difference_type operator-(EnumIterator lhs, EnumIterator rhs) {
        return static_cast<Type_>(lhs.enum_) - static_cast<Type_>(rhs.enum_);
    }

    constexpr reference operator*() const {
        return enum_;
    }

    constexpr reference operator[](size_type size) const {
        return Add(enum_, size);
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
    Enum_ Add(Enum_ _enum, size_type size) {
        return static_cast<Enum_>(static_cast<Type_>(_enum) + size);
    }
    Enum_ Substract(Enum_ _enum, size_type size) {
        return static_cast<Enum_>(static_cast<Type_>(_enum) - size);
    }

};

}
