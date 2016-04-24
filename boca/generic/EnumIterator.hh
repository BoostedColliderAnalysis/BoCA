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

    EnumIterator() : enum_() {}

    EnumIterator(EnumIterator const& enum_iterator) : enum_(enum_iterator.enum_) {}

    explicit EnumIterator(Enum_ value) : enum_(value) {}

<<<<<<< HEAD
=======
    ~EnumIterator() {}

>>>>>>> b1896f098ba125699a875919d288d9d87a7ceda6
    void Set(Enum_ value) {
        enum_ = value;
    }

//     EnumIterator& operator=(EnumIterator const& enum_iterator) {
//         enum_ = enum_iterator.enum_;
//         return *this;
//     }

    EnumIterator& operator++() {
<<<<<<< HEAD
        enum_ = Add(1);
=======
        Add(1);
>>>>>>> b1896f098ba125699a875919d288d9d87a7ceda6
        return *this;
    }

    EnumIterator operator++(int) {
        EnumIterator iterator(*this);
        ++*this;
        return iterator;
    }

    EnumIterator& operator+=(size_type size) {
<<<<<<< HEAD
        enum_ = Add(size);
        return *this;
    }

    friend  EnumIterator operator+(EnumIterator const& it, size_type size) {
        return it.Add(size);
    }

    friend  EnumIterator operator+(size_type size, EnumIterator const& it) {
=======
        Add(size);
        return *this;
    }

    friend EnumIterator operator+(EnumIterator const& it, size_type size) {
        return it.Add(size);
    }

    friend EnumIterator operator+(size_type size, EnumIterator const& it) {
>>>>>>> b1896f098ba125699a875919d288d9d87a7ceda6
        return it.Add(size);
    }

    EnumIterator& operator--() {
<<<<<<< HEAD
        enum_ = Substract(1);
=======
        Substract(1);
>>>>>>> b1896f098ba125699a875919d288d9d87a7ceda6
        return *this;
    }

    EnumIterator operator--(int) {
        EnumIterator iterator(*this);
        --*this;
        return iterator;
    }

    EnumIterator& operator-=(size_type size) {
<<<<<<< HEAD
        enum_ = Add(size);
        return *this;
    }

    friend  EnumIterator operator-(EnumIterator const& it, size_type size) {
=======
        Add(size);
        return *this;
    }

    friend EnumIterator operator-(EnumIterator const& it, size_type size) {
>>>>>>> b1896f098ba125699a875919d288d9d87a7ceda6
        return it.Substract(size);
    }

    friend  difference_type operator-(EnumIterator lhs, EnumIterator enum_iterator) {
        return static_cast<Type_>(lhs.enum_) - static_cast<Type_>(enum_iterator.enum_);
    }

    reference operator*() const {
        return enum_;
    }

<<<<<<< HEAD
    reference operator[](size_type size) const {
=======
    constexpr reference operator[](size_type size) const {
>>>>>>> b1896f098ba125699a875919d288d9d87a7ceda6
        return Add(size);
    }

    const Enum_* operator->() const {
        return &enum_;
    }

    friend bool operator==(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ == rhs.enum_;
    }

    friend bool operator!=(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ != rhs.enum_;
    }

    friend bool operator<(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ < rhs.enum_;
    }

    friend bool operator>(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ > rhs.enum_;
    }

    friend bool operator<=(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ <= rhs.enum_;
    }

    friend bool operator>=(EnumIterator const& lhs, EnumIterator const& rhs) {
        return lhs.enum_ >= rhs.enum_;
    }

    friend void swap(EnumIterator const& lhs, EnumIterator const& rhs) {
        std::swap(lhs.enum_, rhs.enum_);
    }
private:
    Enum_ enum_;
    
    using Type_ = typename std::underlying_type<Enum_>::type;

<<<<<<< HEAD
    Enum_ Add(size_type size) const {
        return static_cast<Enum_>(static_cast<Type_>(enum_) + size);
    }

    Enum_ Substract(size_type size) const {
        return static_cast<Enum_>(static_cast<Type_>(enum_) - size);
=======
    Enum_ Add(size_type size) {
        enum_ = static_cast<Enum_>(static_cast<Type_>(enum_) + size);
        return enum_;
    }

    Enum_ Substract(size_type size) {
        enum_ = static_cast<Enum_>(static_cast<Type_>(enum_) - size);
        return enum_;
>>>>>>> b1896f098ba125699a875919d288d9d87a7ceda6
    }

};

}
