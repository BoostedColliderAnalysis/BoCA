/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/units/cmath.hpp>

#include "boca/physics/Prefixes.hh"

namespace boost
{

namespace units
{

/// specialize root typeof helper
template<class Y>
struct root_typeof_helper<quantity<Y>, static_rational<1, 2>> {
    using type = quantity < typename root_typeof_helper<Y, static_rational<1, 2> >::type
    >;
    static type value(const quantity<Y>& x) {
        return sqrt(x);
    }
};

/// specialize root typeof helper
template<>
struct root_typeof_helper<double, double> {
    using type = double;
    static type value(double x) {
        return std::sqrt(x);
    }
};

}

}

namespace boca
{

template <typename> struct IsQuantity : std::false_type { };
template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type { };

template<typename Value>
using OnlyIfQuantity = typename std::enable_if <IsQuantity<Value>::value >::type;

template<typename Value>
using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value>::value >::type;

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

/// exp of theta in radians
template<class Y>
typename boost::units::dimensionless_quantity<boost::units::si::system, Y>::type
exp(const boost::units::quantity<boost::units::si::plane_angle, Y>& theta)
{
    using std::exp;
    return exp(theta.value());
}

/// log returning Angle
template<class Y>
typename boost::units::quantity<boost::units::si::plane_angle, Y>::type
log(const boost::units::dimensionless_quantity<boost::units::si::system, Y>& number)
{
    using std::log;
    return log(number.value()) * rad;
}

/// log returning Angle
template<class Y>
typename boost::units::quantity<boost::units::si::plane_angle, Y>::type
log(const boost::units::dimensionless_quantity<electronvolt::System, Y>& number)
{
    using std::log;
    return log(number.value()) * rad;
}

// template
template<class Y , typename = OnlyIfNotQuantity<Y>>
inline Angle log(Y const& number)
{
    using std::log;
    return log(number) * rad;
}

template<class Unit, class Y>
inline typename boost::units::root_typeof_helper <boost::units::quantity<Unit, Y>, boost::units::static_rational<3>>::type
        cbrt(const boost::units::quantity<Unit, Y>& q)
{
    using boost::math::cbrt;
    using quantity_type = typename boost::units::root_typeof_helper <boost::units::quantity<Unit, Y>, boost::units::static_rational<3>>::type;
    return quantity_type::from_value(cbrt(q.value()));
}

template<class Unit, class Y>
inline boost::units::quantity<Unit, Y> max BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::units::quantity<Unit, Y>& q1, const boost::units::quantity<Unit, Y>& q2)
{
    using std::max;
    using result_type = boost::units::quantity<Unit, Y>;
    return result_type::from_value(max BOOST_PREVENT_MACRO_SUBSTITUTION(q1.value(), q2.value()));
}

template<class Unit, class Y>
inline boost::units::quantity<Unit, Y> min BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::units::quantity<Unit, Y>& q1, const boost::units::quantity<Unit, Y>& q2)
{
    using std::min;
    using quantity_type = boost::units::quantity<Unit, Y>;
    return quantity_type::from_value(min BOOST_PREVENT_MACRO_SUBSTITUTION(q1.value(), q2.value()));
}

}

template<typename Value, typename Value_2>
using ValueProduct = typename boost::units::multiply_typeof_helper<Value, Value_2>::type;

template<typename Value, typename Value_2>
using ValueQuotient = typename boost::units::divide_typeof_helper<Value, Value_2>::type;

template<typename Value>
using ValueInverse = typename boost::units::divide_typeof_helper<double, Value>::type;

template<typename Value>
using ValueSquare = typename boost::units::multiply_typeof_helper<Value, Value>::type;

template<typename Value>
using ValueSqrt = typename boost::units::root_typeof_helper<Value, double>::type;

template<typename Value>
using ValueCubed = typename boost::units::multiply_typeof_helper<ValueSquare<Value>, Value>::type;

template<typename Value>
using ValueCubed = typename boost::units::multiply_typeof_helper<ValueSquare<Value>, Value>::type;

template<typename Value>
using Value4 = typename boost::units::multiply_typeof_helper<ValueSquare<Value>, ValueSquare<Value>>::type;

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
    return std::atan2(value_1, value_2) * rad;
}

template<typename Value>
Angle atan2(Value const& value_1, Value const& value_2, std::true_type)
{
    return boost::units::atan2(value_1, value_2);
}

template<typename Value>
Angle acos(Value const& value_1)
{
    return acos(value_1, IsQuantity<Value>());
}

template<typename Value>
Angle acos(Value const& value_1, std::false_type)
{
    return std::acos(value_1) * rad;
}

template<typename Value>
Angle acos(Value const& value_1, std::true_type)
{
    return boost::units::acos(value_1);
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
Value max(Value const& value_1, Value const& value_2)
{
  return max2(value_1, value_2, IsQuantity<Value>());
}

template<typename Value>
Value max2(Value const& value_1, Value const& value_2, std::false_type)
{
  return std::max(value_1, value_2);
}

template<typename Value>
Value max2(Value const& value_1, Value const& value_2, std::true_type)
{
  return units::max(value_1, value_2);
}

template<typename Value>
ValueSquare<Value> sqr(Value const& value)
{
    return value * value;
}

template<typename Value>
ValueCubed<Value> cube(Value const& value)
{
  return value * value * value;
}



}


