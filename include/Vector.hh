/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
// #include <vector>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/range/adaptors.hpp>

#include "physics/Particles.hh"
#include "Particle.hh"
#include "Jet.hh"
#include "DetectorGeometry.hh"

namespace boca
{

std::vector<Particle> CopyIfRelativeIs(std::vector<Particle> const& particles, Relative relative, Id id);

std::vector<Particle> CopyIfRelativeIs(std::vector<Particle> const& particles, Relative relative, std::vector<Id> ids);

std::vector<Particle> CopyIfParticle(std::vector<Particle> const& particles, Id id);

std::vector<Particle> CopyIfParticles(std::vector<Particle> const& particles, std::vector<Id> ids);

std::vector<Particle> CopyIfNeutrino(std::vector<Particle> const& particles);

std::vector<Particle> CopyIfLepton(std::vector<Particle> const& particles);

std::vector<Particle> CopyIfExactParticle(std::vector<Particle> const& particles, int id);

std::vector<Particle> RemoveIfExactParticle(std::vector<Particle> particles, int id);

template <typename Multiplet_>
std::vector<Multiplet_> RemoveIfOutsidePtWindow(std::vector<Multiplet_> jets, Momentum lower_cut, Momentum upper_cut)
{
    return boost::range::remove_erase_if(jets, [lower_cut, upper_cut](Multiplet_ const & jet) {
        return jet.Pt() < lower_cut || jet.Pt() > upper_cut;
    });
}

std::vector<Particle> CopyIfFamily(std::vector<Particle> const& particles, Id id, Id mother_id);

/**
 * @brief returns only particles with the correct id and non fitting grand mother id
 *
 */
std::vector<Particle> RemoveIfGrandFamily(std::vector<Particle> particles, Id id, Id grand_mother_id);

std::vector<Particle> CopyIfParticle(std::vector<Particle> const& particles, Id id);

std::vector<Particle> RemoveIfParticle(std::vector<Particle> particles, Id id);

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, Id mother_id);

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, std::vector<Id> mother_id);

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, Particle mother);

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& particles, Id grand_mother_id);

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& particles, Particle grand_mother);

std::vector<Particle> CopyIfGreatGrandMother(std::vector<Particle> const& particles, Id grand_grand_mother_id);

std::vector<Particle> RemoveIfMother(std::vector<Particle> particles, Id mother_id);

std::vector<Particle> RemoveIfMother(std::vector<Particle> particles, std::vector<Id> mother_ids);

std::vector<Particle> RemoveIfSingleMother(std::vector<Particle> particles);

std::vector<Particle> RemoveIfLetpon(std::vector<Particle> particles);

std::vector<Particle> RemoveIfQuark(std::vector<Particle> particles);

std::vector<Particle> CopyIfQuark(std::vector<Particle> const& particles);

std::vector<Particle> CopyIf5Quark(std::vector<Particle> const& particles);

std::vector<Particle> CopyIfDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& daughters);

std::vector<Particle> CopyIfGrandDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& daughters);

std::vector<Particle> CopyIfPosition(std::vector<Particle> const& particles, int position_1, int position_2);

template<typename Multiplet_>
std::vector<Multiplet_> CopyIfTag(std::vector<Multiplet_> const& multiplets, float value = 0){
  std::vector<Multiplet_> tags;
  boost::range::copy(multiplets | boost::adaptors::filtered([value](Multiplet_ const& multiplet){
    return multiplet.Bdt() > 0;
  }), std::back_inserter(tags));
  return tags;
}

/**
 * @brief Copy the two particles which are on the DY position
 *
 * here we assume that the DY particle are always on position 6 and 7
 */
std::vector<Particle> CopyIfDrellYan(std::vector<Particle> const& particles);

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

class Close
{
public:
    Close(PseudoJet const& particle) :
        particle_(particle) ,
        cone_size_(DetectorGeometry::JetConeSize())
    {}
    Close(PseudoJet const& particle, Angle cone_size) :
        particle_(particle) ,
        cone_size_(cone_size)
    {}
    template <typename Multiplet_>
    bool operator()(Multiplet_ const& multiplet) {
        return multiplet.DeltaRTo(particle_) < cone_size_;
    }
private:
    PseudoJet particle_;
    Angle cone_size_;
};

template <typename Multiplet_>
std::vector<Multiplet_> RemoveIfClose(std::vector<Multiplet_> jets, std::vector<Particle> const& particles)
{
    for (auto const & particle : particles) jets.erase(boost::range::remove_if(jets, Close(particle)), jets.end());
    return jets;
}

template <typename Multiplet_>
std::vector<Multiplet_> CopyIfClose(std::vector<Multiplet_> const& multiplets, std::vector<Particle> const& particles)
{
    if (multiplets.empty()) return multiplets;
    std::vector<Multiplet_> final_multiplets;
    for (auto const & particle : particles) for (auto const & multiplet : multiplets) if (Close(particle)(multiplet)) final_multiplets.emplace_back(multiplet);
    return final_multiplets;

//     if (multiplets.empty()) return multiplets;
//     std::vector<Multiplet_> final_multiplets(multiplets.size());
//     auto multiplet = std::copy_if(multiplets.begin(), multiplets.end(), final_multiplets.begin(), Close(particle)(multiplet));
//     final_multiplets.resize(std::distance(final_multiplets.begin(), multiplet));
//     return final_multiplets;
}

template <typename Element>
bool FindInVector(const std::vector<Element> vector, const Element element)
{
    return boost::range::find(vector, element) != vector.end();
}

template <typename Multiplet_>
Particle ClosestJet(std::vector<Particle> const& particles, Multiplet_ const& multiplet)
{
    return *boost::range::min_element(particles, [&](Jet const & jet_1, Jet const & jet_2) {
        return jet_1.DeltaRTo(multiplet.Jet()) < jet_2.DeltaRTo(multiplet.Jet());
    });
}

template <typename Multiplet_>
Jet ClosestJet(std::vector<Jet> const& jets, Multiplet_ const& multiplet)
{
    return *boost::range::min_element(jets, [&](Jet const & jet_1, Jet const & jet_2) {
        return jet_1.DeltaRTo(multiplet.Jet()) < jet_2.DeltaRTo(multiplet.Jet());
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

/**
 * @brief forms all \f$(n^2 - n)\f$ ordered pairs of vector elements, applies to them the function and returns a vector of its results
 *
 */
template < typename Element,
         typename Function,
         typename Result = typename std::result_of<Function&(Element, Element)>::type >
auto OrderedPairs(std::vector<Element> const& container, Function function)
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
template < typename Element, typename Function, typename Result = typename std::result_of<Function&(Element, Element)>::type >
auto UnorderedPairs(std::vector<Element> const& container, Function function)
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

/**
 * @brief forms all \f$n \times m\f$ pairs of the elements in the two containers, applies the function and returns a vector of its elements
 *
 */
template < typename Element1, typename Element2, typename Function, typename Result = typename std::result_of<Function&(Element1, Element2)>::type >
auto Pairs(std::vector<Element1> const& container_1, std::vector<Element2> const& container_2, Function function)
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
auto Triples(std::vector<Element1> const& container_1, std::vector<Element2> const& container_2, Function function)
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
auto Triples(std::vector<Element1> const& container_1, std::vector<Element2> const& container_2, std::vector<Element3> const& container_3, Function function)
{
    std::vector<Result> results;
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
