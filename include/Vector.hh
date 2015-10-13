/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Particles.hh"
#include "DetectorGeometry.hh"

namespace boca
{

typedef std::vector<fastjet::PseudoJet> Jets;

Jets CopyIfParticle(Jets const& jets, Id id);

Jets CopyIfParticles(Jets const& jets, Id id_1, Id id_2);

Jets CopyIfNeutrino(Jets const& jets);

Jets CopyIfLepton(Jets const& jets);

Jets CopyIfExactParticle(Jets const& jets, int id);

Jets RemoveIfExactParticle(Jets jets, int id);

Jets RemoveIfOutsidePtWindow(Jets jets, Momentum lower_cut, Momentum upper_cut);

Jets CopyIfFamily(Jets const& jets, Id id, Id mother_id);

/**
 * @brief returns only particles with the correct id and non fitting grand mother id
 *
 */
Jets RemoveIfGrandFamily(Jets jets, Id id, Id grand_mother_id);

Jets CopyIfParticle(Jets const& jets, Id id);

Jets RemoveIfParticle(Jets jets, Id id);

Jets CopyIfMother(Jets const& jets, Id mother_id);

Jets CopyIfGrandMother(Jets const& jets, Id grand_mother_id);

Jets CopyIfGrandGrandMother(Jets const& jets, Id grand_grand_mother_id);

Jets RemoveIfMother(const Jets jets, Id mother_id);

Jets RemoveIfSingleMother(Jets jets);

Jets RemoveIfLetpon(Jets jets);

Jets RemoveIfQuark(Jets jets);

Jets CopyIfQuark(Jets const& jets);

Jets CopyIf5Quark(Jets const& jets);

Jets RemoveIfSoft(Jets jets, Momentum pt_min);

struct Close {
    Close(fastjet::PseudoJet const& particle) {
        particle_ = particle;
    }
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet) {
        return (multiplet.Jet().delta_R(particle_) < detector_geometry_.JetConeSize());
    }
    bool operator()(fastjet::PseudoJet const& jet) {
        return (jet.delta_R(particle_) < detector_geometry_.JetConeSize());
    }
    fastjet::PseudoJet particle_;
    DetectorGeometry detector_geometry_;
};

template <typename Multiplet>
std::vector<Multiplet> RemoveIfClose(std::vector<Multiplet> jets, Jets const& particles)
{
    for (auto const & particle : particles) jets.erase(std::remove_if(jets.begin(), jets.end(), Close(particle)), jets.end());
    return jets;
}

template <typename Multiplet>
std::vector<Multiplet> CopyIfClose(std::vector<Multiplet> const& multiplets, Jets const& particles)
{
    if (multiplets.empty()) return multiplets;
    std::vector<Multiplet> final_multiplets;
    for (auto const & particle : particles) for (auto const & multiplet : multiplets) if (Close(particle)(multiplet)) final_multiplets.emplace_back(multiplet);
    return final_multiplets;

//     if (multiplets.empty()) return multiplets;
//     std::vector<Multiplet> final_multiplets(multiplets.size());
//     auto multiplet = std::copy_if(multiplets.begin(), multiplets.end(), final_multiplets.begin(), Close(particle)(multiplet));
//     final_multiplets.resize(std::distance(final_multiplets.begin(), multiplet));
//     return final_multiplets;
}

template <typename Element>
bool FindInVector(const std::vector<Element> vector, const Element element)
{
    return (std::find(vector.begin(), vector.end(), element) != vector.end());
}

template <typename Multiplet>
fastjet::PseudoJet ClosestJet(Jets const& jets, Multiplet const& multiplet)
{
    return *std::min_element(jets.begin(), jets.end(), [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        return jet_1.delta_R(multiplet.Jet()) < jet_2.delta_R(multiplet.Jet());
    });
}

/**
 * @brief Join two std::vector
 *
 */
template <typename Element>
std::vector<Element> Join(std::vector<Element> const& vector_1, std::vector<Element> const& vector_2)
{
    std::vector<Element> joined;
    joined.reserve(vector_1.size() + vector_2.size());
    joined.insert(joined.end(), vector_1.begin(), vector_1.end());
    joined.insert(joined.end(), vector_2.begin(), vector_2.end());
    return joined;
}

/**
 * @brief Join three std::vector
 *
 */
template <typename Element>
std::vector<Element> Join(std::vector<Element> const& vector_1, std::vector<Element> const& vector_2, std::vector<Element> const& vector_3)
{
    std::vector<Element> joined;
    joined.reserve(vector_1.size() + vector_2.size() + vector_3.size());
    joined.insert(joined.end(), vector_1.begin(), vector_1.end());
    joined.insert(joined.end(), vector_2.begin(), vector_2.end());
    joined.insert(joined.end(), vector_3.begin(), vector_3.end());
    return joined;
}

template < typename Element,
         typename Function,
         typename Result = typename std::result_of<Function&(Element, Element)>::type >
/**
 * @brief forms all \f$(n^2 - n)\f$ ordered pairs of vector elements, applies to them the function and returns a vector of its results
 *
 */
auto ordered_pairs(std::vector<Element> const& container, Function function)
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

template < typename Element, typename Function, typename Result = typename std::result_of<Function&(Element, Element)>::type >
/**
 * @brief forms all \f$(n^2 - n) / 2\f$ unordered pairs, applies to them the function and returns a vector of its results
 *
 */
auto unordered_pairs(std::vector<Element> const& container, Function function)
{
    std::vector<Result> results;
    for (auto element_1 = container.begin(); element_1 != container.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2)
            try {
                results.emplace_back(function(*element_1, *element_2));
            } catch (std::exception const&) {}
    }
    return results;
}

template < typename Element1, typename Element2, typename Function, typename Result = typename std::result_of<Function&(Element1, Element2)>::type >
/**
 * @brief forms all \f$n \times m\f$ pairs of the elements in the two containers, applies the function and returns a vector of its elements
 *
 */
auto pairs(std::vector<Element1> const& container_1, std::vector<Element2> const& container_2, Function function)
{
    std::vector<Result> results;
    for (auto const & element_1 : container_1) {
        for (auto const & element_2 : container_2) {
            try {
                results.emplace_back(function(element_1, element_2));
            } catch (std::exception const&) {}
        }
    }
    return results;
}

template < typename Element1, typename Element2, typename Function, typename Result = typename std::result_of<Function&(Element1, Element1, Element2)>::type >
/**
 * @brief forms all \f$(n^2 - n) / 2 \times m\f$ triples, applies to them the function and returns a vector of its results
 *
 */
auto triples(std::vector<Element1> const& container_1, std::vector<Element2> const& container_2, Function function)
{
    std::vector<Result> results;
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

template < typename Element1,
         typename Element2,
         typename Element3,
         typename Function,
         typename Result = typename std::result_of<Function&(Element1, Element2, Element3)>::type >
/**
 * @brief forms all \f$(n^2 - n) / 2 \times m\f$ triples, applies to them the function and returns a vector of its results
 *
 */
auto triples(std::vector<Element1> const& container_1, std::vector<Element2> const& container_2, std::vector<Element3> const& container_3, Function function)
{
    std::vector<Result> results;
    for (auto const & element_1 : container_1) {
        for (auto const & element_2 : container_2) {
            for (auto const& element_3 : container_3) {
                try {
                    results.emplace_back(function(element_1, element_2, element_3));
                } catch (std::exception const&) {}
            }
        }
    }
    return results;
}


}
