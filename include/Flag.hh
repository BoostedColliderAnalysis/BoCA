#pragma once
#include<type_traits>

namespace analysis
{

template<typename Enum>
struct Flag {
    static const bool enable = false;
};

template <typename Enum, typename Type>
using Return = typename std::enable_if<Flag<Enum>::enable, Type>;

template<typename Enum>
typename Return<Enum,typename std::underlying_type<Enum>::type>::type
Underlying(Enum enum_1)
{
    return static_cast<typename std::underlying_type<Enum>::type>(enum_1);
}

template<typename Enum>
typename Return<Enum, Enum>::type operator&(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) & Underlying(enum_2));
}

template<typename Enum>
typename Return<Enum, Enum>::type operator|(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) | Underlying(enum_2));
}

template<typename Enum>
typename Return<Enum, Enum>::type operator^(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) ^ Underlying(enum_2));
}

template<typename Enum>
typename Return<Enum, Enum>::type operator~(Enum enum_1)
{
    return static_cast<Enum>(~Underlying(enum_1));
}

template<typename Enum>
typename Return<Enum, Enum&>::type operator&=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) & Underlying(enum_2));
    return enum_1;
}

template<typename Enum>
typename Return<Enum, Enum&>::type operator|=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) | Underlying(enum_2));
    return enum_1;
}

template<typename Enum>
typename Return<Enum, Enum&>::type operator^=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) ^ Underlying(enum_2));
    return enum_1;
}

template<typename Enum>
typename Return<Enum, Enum&>::type operator<<=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) << Underlying(enum_2));
    return enum_1;
}

template <typename Enum>
typename Return<Enum, bool>::type to_bool(Enum const value)
{
    return Underlying(value);
}

template<typename Enum>
typename Return<Enum, bool>::type is(Enum enum_1, Enum enum_2)
{
    return to_bool(enum_1 & enum_2);
}

template<typename Enum, typename Function>
typename Return<Enum, void>::type FlagSwitch(Enum enum_1, Function function)
{
    Enum mask = Enum(1);
    while (to_bool(enum_1)) {
        function(enum_1 & mask);
        enum_1 &= ~mask;
        mask <<= Enum(1);
    }
}

}
