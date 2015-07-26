#pragma once
#include<type_traits>

namespace analysis
{

template<typename Enum>
struct enable_bitmask_operators {
    static const bool enable = false;
};

template<typename Enum>
auto Underlying(Enum enum_1)
{
    return static_cast<typename std::underlying_type<Enum>::type>(enum_1);
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum>::type operator|(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) | Underlying(enum_2));
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum>::type operator&(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) & Underlying(enum_2));
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum>::type operator^(Enum enum_1, Enum enum_2)
{
    return static_cast<Enum>(Underlying(enum_1) ^ Underlying(enum_2));
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum>::type operator~(Enum enum_1)
{
    return static_cast<Enum>(~Underlying(enum_1));
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum&>::type operator|=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) | Underlying(enum_2));
    return enum_1;
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum&>::type operator&=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) & Underlying(enum_2));
    return enum_1;
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum&>::type operator^=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) ^ Underlying(enum_2));
    return enum_1;
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum&>::type operator<<=(Enum& enum_1, Enum enum_2)
{
    enum_1 = static_cast<Enum>(Underlying(enum_1) << Underlying(enum_2));
    return enum_1;
}

template <typename Enum>
bool to_bool(Enum const value)
{
    return Underlying(value);
}

template<typename Enum>
bool is(Enum& enum_1, Enum enum_2)
{
    return to_bool(enum_1 & enum_2);
}

template<typename Enum, typename Function>
void FlagSwitch(Enum enum_1, Function function)
{
    Enum mask = Enum(1);
    while (to_bool(enum_1)) {
        function(enum_1 & mask);
        enum_1 &= ~mask;
        mask <<= Enum(1);
    }
}

}
