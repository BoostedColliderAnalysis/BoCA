/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/adaptors.hpp>
//
#include "DetectorGeometry.hh"

namespace boca
{

// For generic types, directly use the result of the signature of its 'operator()'
template <typename Function_>
struct function_traits : public function_traits<decltype(&Function_::operator())>
{};

// we specialize for pointers to member function
template <typename Class_, typename Return_, typename... Arguments_>
struct function_traits<Return_(Class_::*)(Arguments_...) const> {
    // arity is the number of arguments.
    enum { arity = sizeof...(Arguments_) };

    typedef Return_ result_type;

    template <std::size_t number>
    struct arg {
        // the i-th argument is equivalent to the i-th tuple element of a tuple composed of those arguments.
        typedef typename std::tuple_element<number, std::tuple<Arguments_...>>::type type;
    };
};

template <typename Input_, typename Function_>
auto Transform(Input_ const& inputs, Function_ function)
{
    using Result = typename function_traits<decltype(function)>::result_type;
    std::vector<Result> results;
    if (inputs.empty()) return results;
    results.reserve(inputs.size());
    boost::range::transform(inputs, std::back_inserter(results), function);
//     boost::range::push_back(results, inputs | boost::adaptors::transformed(function));
    return results;
}

template<typename Result_, typename Input_, typename Function_>
std::vector<Result_> TransformIf(Input_ const& inputs, Function_ const& function_1, Function_ const& function_2)
{
    std::vector<Result_> results;
    if (inputs.empty()) return results;
    boost::range::push_back(results, inputs | boost::adaptors::filtered(function_1) | boost::adaptors::transformed(function_2));
    return results;
}

template<typename Elements_, typename Function_>
std::vector<Elements_> CopyIf(std::vector<Elements_> const& inputs, Function_ const& function)
{
    std::vector<Elements_> results;
    return inputs.empty() ? results : boost::range::push_back(results, inputs | boost::adaptors::filtered(function));
}

template<typename Elements_, typename Function_>
std::vector<Elements_> CopyIf(std::vector<Elements_>& inputs, Function_ const& function)
{
    std::vector<Elements_> results;
    return inputs.empty() ? results : boost::range::push_back(results, inputs | boost::adaptors::filtered(function));
}

template <typename Multiplet_>
std::vector<Multiplet_> RemoveIfOutsidePtWindow(std::vector<Multiplet_> jets, Momentum lower_cut, Momentum upper_cut)
{
    return boost::range::remove_erase_if(jets, [lower_cut, upper_cut](Multiplet_ const & jet) {
        return jet.Pt() < lower_cut || jet.Pt() > upper_cut;
    });
}

/**
 * @brief Copy if Bdt value of multiplet is larger than value (default = 0)
 *
 */
template<typename Multiplet_>
std::vector<Multiplet_> CopyIfTag(std::vector<Multiplet_> const& multiplets, double value = 0)
{
    return CopyIf(multiplets, [value](Multiplet_ const & multiplet) {
        return multiplet.Bdt() > value;
    });
}

template<typename Multiplet_>
std::vector<Multiplet_> RemoveIfSoft(std::vector<Multiplet_> multiplets, Momentum pt_min)
{
    return boost::range::remove_erase_if(multiplets, [&](Multiplet_ const & multiplet) {
        return multiplet.Pt() < pt_min;
    });
}

template<typename Multiplet_>
std::vector<Multiplet_> RemoveIfHard(std::vector<Multiplet_> multiplets, Momentum pt_max)
{
    return boost::range::remove_erase_if(multiplets, [&](Multiplet_ const & multiplet) {
        return multiplet.Pt() > pt_max;
    });
}

template <typename Multiplet_1_>
class Close
{
public:
    Close(Multiplet_1_ const& particle) :
        particle_(particle) ,
        cone_size_(DetectorGeometry::JetConeSize())
    {}
    Close(Multiplet_1_ const& particle, Angle cone_size) :
        particle_(particle) ,
        cone_size_(cone_size)
    {}
    template <typename Multiplet_2_>
    bool operator()(Multiplet_2_ const& multiplet) {
        return multiplet.DeltaRTo(particle_) < cone_size_;
    }
private:
    Multiplet_1_ particle_;
    Angle cone_size_;
};

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> RemoveIfClose(std::vector<Multiplet_1_> jets, std::vector<Multiplet_2_> const& particles)
{
    for (auto const & particle : particles) jets = boost::range::remove_erase_if(jets, Close<Multiplet_2_>(particle));
    return jets;
}

template <typename Multiplet_1_, typename Multiplet_2_>
bool CrossComparison(Multiplet_1_ const& multiplet, std::pair<Multiplet_2_, Multiplet_2_> const& particles)
{
    return (Close<Multiplet_2_>(particles.first)(multiplet.Multiplet1()) && Close<Multiplet_2_>(particles.second)(multiplet.Multiplet2())) || (Close<Multiplet_2_>(particles.first)(multiplet.Multiplet2()) && Close<Multiplet_2_>(particles.second)(multiplet.Multiplet1()));
}

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> RemoveIfClose(std::vector<Multiplet_1_> jets, std::vector<std::pair<Multiplet_2_, Multiplet_2_>> const& particles)
{
    for (auto const & particle : particles) jets = boost::range::remove_erase_if(jets, [&](Multiplet_1_ const & multiplet) {
        return CrossComparison(multiplet, particle);
    });
    return jets;
}

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> CopyIfClose(std::vector<Multiplet_1_> const& multiplets, std::vector<Multiplet_2_> const& particles)
{
    if (multiplets.empty()) return multiplets;
    std::vector<Multiplet_1_> close_multiplets;
    for (auto const & particle : particles) Insert(close_multiplets, CopyIfClose(multiplets, particle));
    return close_multiplets;
}

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> CopyIfClose(std::vector<Multiplet_1_> const& multiplets, Multiplet_2_ const& particle)
{
    return CopyIf(multiplets, [&](Multiplet_1_ const & multiplet) {
        return Close<Multiplet_2_>(particle)(multiplet);
    });
}

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> CopyIfClose(std::vector<Multiplet_1_> const& multiplets, std::pair<Multiplet_2_, Multiplet_2_> const& particle)
{
    return CopyIf(multiplets, [&](Multiplet_1_ const & multiplet) {
        return CrossComparison(multiplet, particle);
    });
}

// template <typename Multiplet_>
// std::vector<Multiplet_> CopyIfClose(std::vector<Multiplet_> const& multiplets, std::vector<std::pair<Particle, Particle>> const& particles)
// {
//     if (multiplets.empty()) return multiplets;
//     std::vector<Multiplet_> final_multiplets;
//     for (auto const & particle : particles) for (auto const & multiplet : multiplets) if (CrossComparison(multiplet, particle)) final_multiplets.emplace_back(multiplet);
//     return final_multiplets;
// }

template <typename Element_>
int Position(std::vector<Element_> const& vector, Element_ const& element)
{
    return std::addressof(element) - vector.data();
}

template <typename Element_>
bool FindInVector(const std::vector<Element_> vector, const Element_ element)
{
    return boost::range::find(vector, element) != vector.end();
}

template <typename Multiplet_1_, typename Multiplet_2_>
Multiplet_1_ ClosestJet(std::vector<Multiplet_1_> const& multiplets, Multiplet_2_ const& multiplet)
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
std::vector<Element_> Combine(std::vector<Element_> const& vector_1, std::vector<Element_> const& vector_2)
{
    std::vector<Element_> combined;
    combined.reserve(vector_1.size() + vector_2.size());
    combined.insert(combined.end(), vector_1.begin(), vector_1.end());
    combined.insert(combined.end(), vector_2.begin(), vector_2.end());
    return combined;
}

/**
 * @brief Combine three std::vector
 *
 */
template <typename Element_>
std::vector<Element_> Combine(std::vector<Element_> const& vector_1, std::vector<Element_> const& vector_2, std::vector<Element_> const& vector_3)
{
    std::vector<Element_> combined;
    combined.reserve(vector_1.size() + vector_2.size() + vector_3.size());
    combined.insert(combined.end(), vector_1.begin(), vector_1.end());
    combined.insert(combined.end(), vector_2.begin(), vector_2.end());
    combined.insert(combined.end(), vector_3.begin(), vector_3.end());
    return combined;
}

/**
 * @brief Insert two std::vector
 *
 */
template <typename Element_>
void Insert(std::vector<Element_>& vector_1, std::vector<Element_> const& vector_2)
{
    vector_1.insert(vector_1.end(), vector_2.begin(), vector_2.end());
}

/**
 * @brief Insert three std::vector
 *
 */
template <typename Element_>
void Insert(std::vector<Element_>& vector_1, std::vector<Element_> const& vector_2, std::vector<Element_> const& vector_3)
{
    vector_1.insert(vector_1.end(), vector_2.begin(), vector_2.end());
    vector_1.insert(vector_1.end(), vector_3.begin(), vector_3.end());
}

/**
 * @brief forms all \f$(n^2 - n)\f$ ordered pairs of vector elements, applies to them the function and returns a vector of its results
 *
 */
template < typename Element_,
         typename Function,
         typename Result = typename std::result_of<Function&(Element_, Element_)>::type >
auto OrderedPairs(std::vector<Element_> const& container, Function function)
{
    std::vector<Result> results;
    for (auto element_1 = container.begin(); element_1 != container.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2) {
            try {
                results.emplace_back(function(*element_1, *element_2));
            } catch (std::exception const&) {}
            try {
                results.emplace_back(function(*element_2, *element_1));
            } catch (std::exception const&) {}
        }
    }
    return results;
}

/**
 * @brief forms all \f$(n^2 - n) / 2\f$ unordered pairs, applies to them the function and returns a vector of its results
 *
 */
template < typename Element_, typename Function_, typename Result_ = typename std::result_of<Function_&(Element_, Element_)>::type >
auto UnorderedPairs(std::vector<Element_> const& container, Function_ function)
{
    std::vector<Result_> results;
    for (auto element_1 = container.begin(); element_1 != container.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2)
            try {
                results.emplace_back(function(*element_1, *element_2));
            } catch (std::exception const&) {}
    }
    return results;
}

/**
 * @brief forms all \f$n \times m\f$ pairs of the elements in the two containers, applies the function and returns a vector of its elements
 *
 */
template < typename Element_1_, typename Element_2_, typename Function_, typename Result_ = typename std::result_of<Function_&(Element_1_, Element_2_)>::type >
auto Pairs(std::vector<Element_1_> const& container_1, std::vector<Element_2_> const& container_2, Function_ function)
{
    std::vector<Result_> results;
    for (auto const & element_1 : container_1) {
        for (auto const & element_2 : container_2) {
            try {
                results.emplace_back(function(element_1, element_2));
            } catch (std::exception const&) {}
        }
    }
    return results;
}

template < typename Element_1_, typename Element_2_, typename Function_, typename Result_ = typename std::result_of<Function_&(Element_1_, Element_1_, Element_2_)>::type >
/**
 * @brief forms all \f$(n^2 - n) / 2 \times m\f$ triples, applies to them the function and returns a vector of its results
 *
 */
auto Triples(std::vector<Element_1_> const& container_1, std::vector<Element_2_> const& container_2, Function_ function)
{
    std::vector<Result_> results;
    for (auto element_1 = container_1.begin(); element_1 != container_1.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container_1.end(); ++element_2)
            for (auto & element_3 : container_2) {
                try {
                    results.emplace_back(function(*element_1, *element_2, element_3));
                } catch (std::exception const&) {}
            }
    }
    return results;
}

template < typename Element_1_,
         typename Element_2_,
         typename Element_3_,
         typename Function_,
         typename Result_ = typename std::result_of<Function_&(Element_1_, Element_2_, Element_3_)>::type >
/**
 * @brief forms all \f$(n^2 - n) / 2 \times m\f$ triples, applies to them the function and returns a vector of its results
 *
 */
auto Triples(std::vector<Element_1_> const& container_1, std::vector<Element_2_> const& container_2, std::vector<Element_3_> const& container_3, Function_ function)
{
    std::vector<Result_> results;
    for (auto const & element_1 : container_1) {
        for (auto const & element_2 : container_2) {
            for (auto const & element_3 : container_3) {
                try {
                    results.emplace_back(function(element_1, element_2, element_3));
                } catch (std::exception const&) {}
            }
        }
    }
    return results;
}

}
