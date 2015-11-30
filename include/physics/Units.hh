/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <boost/units/cmath.hpp>

# include "physics/Prefixes.hh"

namespace boca
{

namespace units
{

/// sinh of theta in radians
template<class Y>
typename boost::units::dimensionless_quantity<boost::units::si::system, Y>::type
sinh(const boost::units::quantity<boost::units::si::plane_angle, Y>& theta)
{
    using std::sinh;
    return sinh(theta.value());
}

/// sinh of theta in radians
template<class Y>
typename boost::units::dimensionless_quantity<boost::units::si::system, Y>::type
exp(const boost::units::quantity<boost::units::si::plane_angle, Y>& theta)
{
  using std::exp;
  return exp(theta.value());
}

}

template<typename Value, typename Value_2>
using ValueProduct = typename boost::units::multiply_typeof_helper<Value, Value_2>::type;

template<typename Value>
using ValueSqr = typename boost::units::multiply_typeof_helper<Value, Value>::type;

template<typename Value>
using ValueSqrt = typename boost::units::root_typeof_helper<Value, int>::type;

template <typename> struct IsQuantity : std::false_type { };
template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type { };

template<typename Value>
using OnlyIfQuantity = typename std::enable_if <IsQuantity<Value>::value >::type;

template<typename Value>
using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value>::value >::type;


template<typename Value_2>
double GetValue(Value_2 const& value)
{
    return GetValue(value, IsQuantity<Value_2>());
}

template<typename Value_2>
double GetValue(Value_2 const& value, std::false_type)
{
    return value;
}

template<typename Value_2>
double GetValue(Value_2 const& value, std::true_type)
{
    return value.value();
}

template<typename Value>
ValueSqrt<Value> sqrt(Value const& value)
{
    return sqrt(value, IsQuantity<Value>());
}

template<typename Value>
ValueSqrt<Value> sqrt(Value const& value, std::false_type)
{
    return std::sqrt(value);
}

template<typename Value>
ValueSqrt<Value> sqrt(Value const& value, std::true_type)
{
    return boost::units::sqrt(value);
}

template<typename Value>
Angle atan2(Value const& value_1, Value const& value_2)
{
    return atan2(value_1, value_2, IsQuantity<Value>());
}

template<typename Value>
Angle atan2(Value const& value_1, Value const& value_2, std::false_type)
{
    return double(std::atan2(value_1, value_2)) * rad;
}

template<typename Value>
Angle atan2(Value const& value_1, Value const& value_2, std::true_type)
{
    return boost::units::atan2(value_1, value_2);
}

template<typename Value>
Value abs(Value const& value)
{
    return abs(value, IsQuantity<Value>());
}

template<typename Value>
Value abs(Value const& value, std::false_type)
{
    return std::abs(value);
}

template<typename Value>
Value abs(Value const& value, std::true_type)
{
    return boost::units::abs(value);
}

template<typename Value>
ValueSqr<Value> sqr(Value const& value)
{
  return value * value;
}

}


