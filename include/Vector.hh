/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
// #include <vector>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/find.hpp>

#include "Particles.hh"
#include "Particle.hh"
#include "Jet.hh"
#include "DetectorGeometry.hh"

namespace boca
{

  std::vector<Particle> CopyIfParticle(std::vector<Particle> const& jets, Id id);

  std::vector<Particle> CopyIfParticles(std::vector<Particle> const& jets, Id id_1, Id id_2);

  std::vector<Particle> CopyIfParticles(std::vector<Particle> const& jets, std::vector<Id> ids);

  std::vector<Particle> CopyIfNeutrino(std::vector<Particle> const& jets);

  std::vector<Particle> CopyIfLepton(std::vector<Particle> const& jets);

  std::vector<Particle> CopyIfExactParticle(std::vector<Particle> const& jets, int id);

  std::vector<Particle> RemoveIfExactParticle(std::vector<Particle> jets, int id);

  std::vector<Jet> RemoveIfOutsidePtWindow(std::vector<Jet> jets, Momentum lower_cut, Momentum upper_cut);

  std::vector<Particle> CopyIfFamily(std::vector<Particle> const& jets, Id id, Id mother_id);

/**
 * @brief returns only particles with the correct id and non fitting grand mother id
 *
 */
std::vector<Particle> RemoveIfGrandFamily(std::vector<Particle> jets, Id id, Id grand_mother_id);

std::vector<Particle> CopyIfParticle(std::vector<Particle> const& jets, Id id);

std::vector<Particle> RemoveIfParticle(std::vector<Particle> jets, Id id);

std::vector<Particle> CopyIfMother(std::vector<Particle> const& jets, Id mother_id);

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& jets, Id grand_mother_id);

std::vector<Particle> CopyIfGrandGrandMother(std::vector<Particle> const& jets, Id grand_grand_mother_id);

std::vector<Particle> RemoveIfMother(std::vector<Particle> jets, Id mother_id);

std::vector<Particle> RemoveIfSingleMother(std::vector<Particle> jets);

std::vector<Particle> RemoveIfLetpon(std::vector<Particle> jets);

std::vector<Particle> RemoveIfQuark(std::vector<Particle> jets);

std::vector<Particle> CopyIfQuark(std::vector<Particle> const& jets);

std::vector<Particle> CopyIf5Quark(std::vector<Particle> const& jets);

std::vector<Particle> CopyIfDaughter(std::vector<Particle> const& particles,std::vector<Particle> const& daughters);

std::vector<Particle> CopyIfGrandDaughter(std::vector<Particle> const& particles,std::vector<Particle> const& daughters);

template<typename Multiplet>
std::vector<Multiplet> RemoveIfSoft(std::vector<Multiplet> multiplets, Momentum pt_min)
{
    return boost::range::remove_erase_if(multiplets, [&](Multiplet const & multiplet) {
        return multiplet.Pt() < pt_min;
    });
}

template<typename Multiplet>
std::vector<Multiplet> RemoveIfHard(std::vector<Multiplet> multiplets, Momentum pt_max)
{
    return boost::range::remove_erase_if(multiplets, [&](Multiplet const & multiplet) {
        return multiplet.Pt() > pt_max;
    });
}

std::vector<Particle> RemoveIfSoft(std::vector<Particle> jets, Momentum pt_min);

std::vector<Particle> RemoveIfHard(std::vector<Particle> jets, Momentum pt_max);

struct Close {
    Close(Particle const& particle) : particle_(particle){}
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet) {
        return multiplet.DeltaRTo(particle_) < detector_geometry_.JetConeSize();
    }
    bool operator()(Jet const& jet) {
//       std::cout<< jet.delta_R(particle_) * rad << std::endl;
        return jet.delta_R(particle_) * rad < detector_geometry_.JetConeSize();
    }
    bool operator()(Particle const& jet) {
      //       std::cout<< jet.delta_R(particle_) * rad << std::endl;
      return jet.delta_R(particle_) * rad < detector_geometry_.JetConeSize();
    }
    Particle particle_;
    DetectorGeometry detector_geometry_;
};

template <typename Multiplet>
std::vector<Multiplet> RemoveIfClose(std::vector<Multiplet> jets,std::vector<Particle> const& particles)
{
    for (auto const & particle : particles) jets.erase(std::remove_if(jets.begin(), jets.end(), Close(particle)), jets.end());
    return jets;
}

template <typename Multiplet>
std::vector<Multiplet> CopyIfClose(std::vector<Multiplet> const& multiplets, std::vector<Particle> const& particles)
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
    return boost::range::find(vector, element) != vector.end();
}

template <typename Multiplet>
Particle ClosestJet(std::vector<Particle> const& jets, Multiplet const& multiplet)
{
  return *boost::range::min_element(jets, [&](Jet const & jet_1, Jet const & jet_2) {
        return jet_1.delta_R(multiplet.Jet()) < jet_2.delta_R(multiplet.Jet());
    });
}

template <typename Multiplet>
Jet ClosestJet(std::vector<Jet> const& jets, Multiplet const& multiplet)
{
  return *boost::range::min_element(jets, [&](Jet const & jet_1, Jet const & jet_2) {
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
