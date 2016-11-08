/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/adaptors.hpp>

namespace boca
{

/**
 * @ingroup Generic
 * @defgroup Vector Vector
 * @brief Functions used for Container (mainly std::vector) manipulation
 * @{
 */

// For generic types, directly use the result of the signature of its 'operator()'
template <typename Function_>
struct function_traits : public function_traits<decltype(&Function_::operator())> {
};

// we specialize for pointers to member function
template <typename Class_, typename Result_, typename... Arguments_>
struct function_traits<Result_(Class_::*)(Arguments_...) const> {
    // arity is the number of arguments.
    enum { arity = sizeof...(Arguments_) };
    using result_type = Result_;

    template <std::size_t number>
    struct arg {
        // the i-th argument is equivalent to the i-th tuple element of a tuple composed of those arguments.
        using type = typename std::tuple_element<number, std::tuple<Arguments_...>>::type;
    };
};

template <typename Input_, typename Function_>
auto Transform(Input_ const &inputs, Function_ function)
{
    using Result_ = typename function_traits<decltype(function)>::result_type;
    auto results = std::vector<Result_> {};
    if (inputs.empty()) return results;
    results.reserve(inputs.size());
    boost::range::transform(inputs, std::back_inserter(results), function);
//     boost::range::push_back(results, inputs | boost::adaptors::transformed(function));
    return results;
}

template<typename Result_, typename Input_, typename Function_>
std::vector<Result_> TransformIf(Input_ const &inputs, Function_ const &function_1, Function_ const &function_2)
{
    auto results = std::vector<Result_> {};
    if (inputs.empty()) return results;
    boost::range::push_back(results, inputs | boost::adaptors::filtered(function_1) | boost::adaptors::transformed(function_2));
    return results;
}

template<typename Elements_, typename Function_>
std::vector<Elements_> CopyIf(std::vector<Elements_> const &inputs, Function_ function)
{
    std::vector<Elements_> results;
    return inputs.empty() ? results : boost::range::push_back(results, inputs | boost::adaptors::filtered(std::ref(function))); // http://stackoverflow.com/a/25907302
}

template <typename Element_>
std::size_t Position(std::vector<Element_> const &vector, Element_ const &element)
{
    return std::addressof(element) - vector.data();
}

template <typename Element_,  unsigned long size_>
std::size_t Position(std::array<Element_, size_> const &array, Element_ const &element)
{
    return std::addressof(element) - array.data();
}


template <typename Element_>
bool FindInVector(const std::vector<Element_> vector, const Element_ element)
{
    return boost::range::find(vector, element) != vector.end();
}

template <typename Multiplet_1_, typename Multiplet_2_>
Multiplet_1_ ClosestJet(std::vector<Multiplet_1_> const &multiplets, Multiplet_2_ const &multiplet)
{
    return *boost::range::min_element(multiplets, [&](Multiplet_1_ const & multiplet_1, Multiplet_1_ const & multiplet_2) {
        return multiplet.DeltaRTo(multiplet_1) < multiplet.DeltaRTo(multiplet_2);
    });
}

/**
 * @brief Combine two std::vector
 *
 */
template <typename Element_>
std::vector<Element_> Combine(std::vector<Element_> const &vector_1, std::vector<Element_> const &vector_2)
{
    auto combined = std::vector<Element_> {};
    combined.reserve(vector_1.size() + vector_2.size());
    if (!vector_1.empty()) combined.insert(combined.end(), vector_1.begin(), vector_1.end());
    if (!vector_2.empty()) combined.insert(combined.end(), vector_2.begin(), vector_2.end());
    return combined;
}

/**
 * @brief Combine three std::vector
 *
 */
template <typename Element_>
std::vector<Element_> Combine(std::vector<Element_> const &vector_1, std::vector<Element_> const &vector_2, std::vector<Element_> const &vector_3)
{
    auto combined = std::vector<Element_> {};
    combined.reserve(vector_1.size() + vector_2.size() + vector_3.size());
    if (!vector_1.empty()) combined.insert(combined.end(), vector_1.begin(), vector_1.end());
    if (!vector_2.empty()) combined.insert(combined.end(), vector_2.begin(), vector_2.end());
    if (!vector_3.empty()) combined.insert(combined.end(), vector_3.begin(), vector_3.end());
    return combined;
}

/**
 * @brief Insert two std::vector
 *
 */
template <typename Element_>
void Insert(std::vector<Element_> &vector_1, std::vector<Element_> const &vector_2)
{
    if (vector_2.empty()) return;
    vector_1.reserve(vector_1.size() + vector_2.size());
    vector_1.insert(vector_1.end(), vector_2.begin(), vector_2.end());
}

/**
 * @brief Insert three std::vector
 *
 */
template <typename Element_>
void Insert(std::vector<Element_> &vector_1, std::vector<Element_> const &vector_2, std::vector<Element_> const &vector_3)
{
    vector_1.reserve(vector_1.size() + vector_2.size() + vector_3.size());
    if (!vector_2.empty()) vector_1.insert(vector_1.end(), vector_2.begin(), vector_2.end());
    if (!vector_3.empty()) vector_1.insert(vector_1.end(), vector_3.begin(), vector_3.end());
}

/**
 * @brief forms all \f$(n^2 - n)\f$ ordered pairs of vector elements, applies to them the function and returns a vector of its results
 *
 */
template < typename Element_,
           typename Function,
           typename Result = typename std::result_of<Function&(Element_, Element_)>::type >
auto OrderedPairs(std::vector<Element_> const &container, Function function)
{
    auto results = std::vector<Result> {};
    for (auto element_1 = container.begin(); element_1 != container.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2) {
            try {
                results.emplace_back(function(*element_1, *element_2));
            } catch (std::exception const &) {}
            try {
                results.emplace_back(function(*element_2, *element_1));
            } catch (std::exception const &) {}
        }
    }
    return results;
}

/**
 * @brief forms all \f$(n^2 - n) / 2\f$ unordered pairs, applies to them the function and returns a vector of its results
 *
 */
template < typename Element_, typename Function_, typename Result_ = typename std::result_of<Function_&(Element_, Element_)>::type >
auto UnorderedPairs(std::vector<Element_> const &container, Function_ function)
{
    auto results = std::vector<Result_> {};
    for (auto element_1 = container.begin(); element_1 != container.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2)
            try {
                results.emplace_back(function(*element_1, *element_2));
            } catch (std::exception const &) {}
    }
    return results;
}

/**
 * @brief forms all \f$n \times m\f$ pairs of the elements in the two containers, applies the function and returns a vector of its elements
 *
 */
template < typename Element_1_, typename Element_2_, typename Function_, typename Result_ = typename std::result_of<Function_&(Element_1_, Element_2_)>::type >
auto Pairs(std::vector<Element_1_> const &container_1, std::vector<Element_2_> const &container_2, Function_ function)
{
    auto results = std::vector<Result_> {};
    for (auto const &element_1 : container_1) {
        for (auto const &element_2 : container_2) {
            try {
                results.emplace_back(function(element_1, element_2));
            } catch (std::exception const &) {}
        }
    }
    return results;
}

/**
 * @brief forms all \f$(n^2 - n) / 2 \times m\f$ triples, applies to them the function and returns a vector of its results
 *
 */
template < typename Element_1_,
           typename Element_2_,
           typename Function_,
           typename Result_ = typename std::result_of<Function_&(Element_1_, Element_1_, Element_2_)>::type >
auto Triples(std::vector<Element_1_> const &container_1, std::vector<Element_2_> const &container_2, Function_ function)
{
    auto results = std::vector<Result_> {};
    for (auto element_1 = container_1.begin(); element_1 != container_1.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container_1.end(); ++element_2)
            for (auto &element_3 : container_2) {
                try {
                    results.emplace_back(function(*element_1, *element_2, element_3));
                } catch (std::exception const &) {}
            }
    }
    return results;
}

/**
 * @brief forms all \f$(n^2 - n) / 2 \times m\f$ triples, applies to them the function and returns a vector of its results
 *
 */
template < typename Element_1_,
           typename Element_2_,
           typename Element_3_,
           typename Function_,
           typename Result_ = typename std::result_of<Function_&(Element_1_, Element_2_, Element_3_)>::type >
auto Triples(std::vector<Element_1_> const &container_1, std::vector<Element_2_> const &container_2, std::vector<Element_3_> const &container_3, Function_ function)
{
    auto results = std::vector<Result_> {};
    for (auto const &element_1 : container_1) {
        for (auto const &element_2 : container_2) {
            for (auto const &element_3 : container_3) {
                try {
                    results.emplace_back(function(element_1, element_2, element_3));
                } catch (std::exception const &) {}
            }
        }
    }
    return results;
}

/**
 * @brief forms all \f$(n^2 - n) / 2 \times m\f$ triples, applies to them the function and returns a vector of its results
 *
 */
template < typename Element_1_,
           typename Element_2_,
           typename Element_3_,
           typename Function_1_,
           typename Function_2_,
           typename Result_1_ = typename std::result_of<Function_1_&(Element_1_, Element_2_)>::type,
           typename Result_2_ = typename std::result_of<Function_2_&(Result_1_, Element_3_)>::type >
auto Triples(std::vector<Element_1_> const &container_1, std::vector<Element_2_> const &container_2, std::vector<Element_3_> const &container_3, Function_1_ function_1, Function_2_ function_2)
{
    auto results = std::vector<Result_2_> {};
    for (auto const &element_1 : container_1) {
        for (auto const &element_2 : container_2) {
            try {
                auto pair = function_1(element_1, element_2);
                for (auto const &element_3 : container_3) {
                    try {
                        results.emplace_back(function_2(pair, element_3));
                    } catch (std::exception const &) {}
                }
            } catch (std::exception const &) {}
        }
    }
    return results;
}

// @}

}
