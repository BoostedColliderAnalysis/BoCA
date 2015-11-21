/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <string>

namespace boca
{

bool Exists(std::string const& name);


/**
 * @brief provides an integer with the necessary information to act as counter for a range based for loop
 *
 */
class Range
{
public:
    Range(int sum) : last_(sum), iterator_(0) {}

    Range(int low, int sum) : last_(sum), iterator_(std::max(low - 1, 0)) {}

    Range const& begin() const {
        return *this;
    }
    Range const& end() const {
        return *this;
    }
    bool operator!=(Range const&) const {
        return iterator_ < last_;
    }
    void operator++() {
        ++iterator_;
    }
    int operator*() const {
        return iterator_;
    }
private:
    int last_;
    int iterator_;
};

template <typename Enumeration>
auto to_int(Enumeration value) -> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template <typename Enumeration>
using Unsigned = typename std::make_unsigned<typename std::underlying_type<Enumeration>::type>;

template <typename Enumeration>
auto to_unsigned(Enumeration value) -> typename Unsigned<Enumeration>::type {
    return static_cast<typename Unsigned<Enumeration>::type>(value);
}

}
