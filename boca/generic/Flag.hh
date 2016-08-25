/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include<type_traits>

namespace boca
{

/**
 * @ingroup Generic
 * @defgroup Flag
 * @brief Enables the usage of strongly typed enumerators as flags
 * @{
 */

/**
* @brief Mark a strongly typed enumerator as a flag
*/
template<typename Enum>
struct Flag {
    static const bool enable = false;
};

template <typename Enum, typename Type>
using FlagReturn = typename std::enable_if<Flag<Enum>::enable, Type>;

template<typename Enum>
typename FlagReturn<Enum, typename std::underlying_type<Enum>::type>::type
Underlying(Enum enum_1)
{
    return static_cast<typename std::underlying_type<Enum>::type>(enum_1);
}

template<typename Enum>
typename FlagReturn<Enum, Enum>::type operator&(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) & Underlying(enum_2));
}

template<typename Enum>
constexpr typename FlagReturn<Enum, Enum>::type operator|(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) | Underlying(enum_2));
}

template<typename Enum>
typename FlagReturn<Enum, Enum>::type operator^(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) ^ Underlying(enum_2));
}

template<typename Enum>
typename FlagReturn<Enum, Enum>::type operator~(Enum enum_1)
{
    return static_cast<Enum>(~Underlying(enum_1));
}

template<typename Enum>
typename FlagReturn<Enum, Enum&>::type operator&=(Enum& enum_1, Enum enum_2)
{
    enum_1 = enum_1 & enum_2;
    return enum_1;
}

template<typename Enum>
typename FlagReturn<Enum, Enum&>::type operator|=(Enum& enum_1, Enum enum_2)
{
    enum_1 = enum_1 | enum_2;
    return enum_1;
}

template<typename Enum>
typename FlagReturn<Enum, Enum&>::type operator^=(Enum& enum_1, Enum enum_2)
{
    enum_1 = enum_1 ^ enum_2;
    return enum_1;
}

template<typename Enum>
typename FlagReturn<Enum, Enum&>::type operator<<=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) << Underlying(enum_2));
    return enum_1;
}

template <typename Enum>
typename FlagReturn<Enum, bool>::type to_bool(Enum value)
{
    return Underlying(value);
}

template<typename Enum>
typename FlagReturn<Enum, bool>::type is(Enum enum_1, Enum enum_2)
{
    return to_bool(enum_1 & enum_2);
}

template<typename Enum, typename Function>
// typename FlagReturn<Enum, void>::type
void FlagSwitch(Enum enum_1, Function function)
{
    auto mask = Enum(1); // define mask of lowest enum value
    while (to_bool(enum_1)) {
        auto pure = enum_1 & mask; // project onto mask value
        if (pure != Enum(0)) function(pure); // if non-zero apply function
        enum_1 &= ~mask; // remove mask value from enum
        mask <<= Enum(1); // increment mask value
    }
}

/*
 * @}
 */

}
