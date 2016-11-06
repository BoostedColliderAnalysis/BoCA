/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include "boca/generic/Debug.hh"

// defined by cmake for debug runs
#ifndef NDEBUG
#define NOTIFICATION
#endif
// #define DEBUGGING
// #define INFORMATION
// #define NOTIFICATION



// #define COMMA_IF_PARENS(...) ,
//
// #define LPAREN (
//
// #define EXPAND(...) __VA_ARGS__
//
// #define NORMAL(number) LOG ## number, impossible, LOG ## number
//
// #define SPECIAL LOG1, LOG0, LOG1,
//
// #define CHOOSE(...) EXPAND(LOG LPAREN __VA_ARGS__ COMMA_IF_PARENS __VA_ARGS__ COMMA_IF_PARENS __VA_ARGS__ (), NORMAL(4), NORMAL(3), NORMAL(2), SPECIAL))
//
// #define LOG(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg, ...) arg



/**
 * @ingroup Debug
 * @{
 */

#define FILE_NAME ::boca::FileName(__FILE__)

#define NAMESPACE_NAME ::boca::NameSpaceName(__PRETTY_FUNCTION__)

#define CLASS_NAME ::boca::ClassName(__PRETTY_FUNCTION__)

#define FUNCTION_NAME ::boca::FunctionName(__PRETTY_FUNCTION__)

#define NAMES FILE_NAME, __LINE__, NAMESPACE_NAME, CLASS_NAME, FUNCTION_NAME

#define VARIABLE(value) #value, value

#define STREAM(value) ::boca::Stream2(VARIABLE(value))

#define LOG0 ::boca::Log(NAMES)

#define LOG1(value) ::boca::Log(NAMES, VARIABLE(value))

#define LOG2(value, value2) ::boca::Log(NAMES, VARIABLE(value), VARIABLE(value2))

#define LOG3(value, value2, value3) ::boca::Log(NAMES, VARIABLE(value), VARIABLE(value2), VARIABLE(value3))

#define LOG4(value, value2, value3, value4) ::boca::Log(NAMES, VARIABLE(value), VARIABLE(value2), VARIABLE(value3), VARIABLE(value4))

#define LOG5(value, value2, value3, value4, value5) ::boca::Log(NAMES, VARIABLE(value), VARIABLE(value2), VARIABLE(value3), VARIABLE(value4), VARIABLE(value5))

#define LOG(arg0, arg1, arg2, arg3, arg4, arg5, arg, ...) arg

#define CHOOSE(...) LOG(__VA_ARGS__, , LOG5, LOG4, LOG3, LOG2, LOG1, )

#define ALIVE(...) CHOOSE(__VA_ARGS__)(__VA_ARGS__)

#define DEAD(...) do { if (0) ALIVE(__VA_ARGS__); } while (0)

#define DEAD0 do { if (0) LOG0; } while (0)

#define ERROR(...) ALIVE(__VA_ARGS__)
#define ERROR0 LOG0

#if defined(DETAILED)
#define DETAIL(...) ALIVE(__VA_ARGS__)
#define DETAIL0 LOG0
#else
#define DETAIL(...) DEAD(__VA_ARGS__)
#define DETAIL0 DEAD0
#endif

#if defined(DETAILED) || defined(DEBUGGING)
#define DEBUG(...) ALIVE(__VA_ARGS__)
#define DEBUG0 LOG0
#else
#define DEBUG(...) DEAD(__VA_ARGS__)
#define DEBUG0 DEAD0
#endif

#if defined(DETAILED) || defined(DEBUGGING) || defined(INFORMATION)
#define INFO(...) ALIVE(__VA_ARGS__)
#define INFO0 LOG0
#else
#define INFO(...) DEAD(__VA_ARGS__)
#define INFO0 DEAD0
#endif

#if defined(DETAILED) || defined(DEBUGGING) || defined(INFORMATION) || defined(NOTIFICATION)
#define NOTE(...) ALIVE(__VA_ARGS__)
#define NOTE0 LOG0
#else
#define NOTE(...) DEAD(__VA_ARGS__)
#define NOTE0 DEAD0
#endif

#define CHECK(condition, ...) if(!(condition)) { ERROR("Check failed", __VA_ARGS__); }
#define DEBUG_CHECK(condition, ...) if(!(condition)) { DEBUG(__VA_ARGS__); }

#define DEFAULT_1(condition) default : ERROR("Switch Default", condition); break;
#define DEFAULT_2(condition, value) default : ERROR("Switch Default", condition); return value;

#define DEFAULT_ARGUMENTS(arg1, arg2, arg, ...) arg
#define DEFAULT_CHOOSE(...) DEFAULT_ARGUMENTS(__VA_ARGS__, DEFAULT_2, DEFAULT_1, )

#define DEFAULT(...) DEFAULT_CHOOSE(__VA_ARGS__)(__VA_ARGS__)

// #include "boca/Logging.hh"

// #define HAS_ARGS_IMPL2(_1, _2, _3, N, ...) N
// #define HAS_ARGS_SOURCE() MULTI, MULTI, ONE, ERROR
//
// #define HAS_ARGS_IMPL(...) HAS_ARGS_IMPL2(__VA_ARGS__)
// #define HAS_ARGS(...) HAS_ARGS_IMPL(__VA_ARGS__, HAS_ARGS_SOURCE())
//
// #define MACRO_ONE(x) ONE_ARG: x
// #define MACRO_MULTI(...) MULTI_ARG: __VA_ARGS__
//
// #define DISAMBIGUATE2(args, ...) MACRO_ ## args (__VA_ARGS__)
// #define DISAMBIGUATE(args, ...) DISAMBIGUATE2(args, __VA_ARGS__)
// #define ERROR(...) DISAMBIGUATE(HAS_ARGS(__VA_ARGS__), __VA_ARGS__)

/*
 * @}
 */
