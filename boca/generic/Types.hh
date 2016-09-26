/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>
#include <boost/range/irange.hpp>

namespace boca
{

/**
 * @ingroup Generic
 * @{
 */

template<typename Integer>
decltype(auto) IntegerRange(Integer last) {
  return boost::integer_range<Integer>(0, last);
}

template<typename Integer>
decltype(auto) IntegerRange(Integer first, Integer last) {
  BOOST_ASSERT( first <= last );
  return boost::integer_range<Integer>(first, last);
}

template <typename Enumeration>
decltype(auto) to_int(Enumeration value) {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template <typename Enumeration>
using Unsigned = typename std::make_unsigned<typename std::underlying_type<Enumeration>::type>;

template <typename Enumeration>
decltype(auto) to_unsigned(Enumeration value) {
    return static_cast<typename Unsigned<Enumeration>::type>(value);
}

// @}

}
