#pragma once

#include "Particles.hh"
#include "DetectorGeometry.hh"

namespace analysis
{

typedef std::vector<fastjet::PseudoJet> Jets;

Jets CopyIfParticle(const Jets& jets, Id id);

Jets CopyIfParticles(const Jets& jets, Id id_1, Id id_2);

Jets CopyIfNeutrino(const Jets& jets);

Jets CopyIfExactParticle(const Jets& jets, int id);

Jets RemoveIfExactParticle(Jets jets, int id);

Jets RemoveIfOutsidePtWindow(Jets jets, float lower_cut, float upper_cut);

Jets CopyIfFamily(const Jets& jets, Id id, Id mother_id);

/**
 * @brief returns only particles with the correct id and non fitting grand mother id
 *
 */
Jets RemoveIfGrandFamily(Jets jets, Id id, Id grand_mother_id);

Jets CopyIfParticle(const Jets& jets, Id id);

Jets RemoveIfParticle(Jets jets, Id id);

Jets CopyIfMother(const Jets& jets, Id mother_id);

Jets CopyIfGrandMother(const Jets& jets, Id grand_mother_id);

Jets RemoveIfMother(const Jets jets, Id mother_id);

Jets RemoveIfSingleMother(Jets jets);

Jets RemoveIfLetpon(Jets jets);

Jets RemoveIfQuark(Jets jets);

Jets CopyIfQuark(const Jets& jets);

Jets CopyIf5Quark(const Jets& jets);

Jets CopyIfPosition(const Jets& particles, const std::vector<int> & positions);

Jets RemoveIfSoft(Jets jets, float pt_min);

Jets RemoveIfLargeRap(Jets jets, float rap_max);

struct Close {
    Close(const fastjet::PseudoJet& particle) {
        particle_ = particle;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet& multiplet) {
        return (multiplet.Jet().delta_R(particle_) < detector_geometry_.JetConeSize());
    }
    bool operator()(const fastjet::PseudoJet& jet) {
        return (jet.delta_R(particle_) < detector_geometry_.JetConeSize());
    }
    bool operator()(const fastjet::PseudoJet& jet, float cone_size) {
      return (jet.delta_R(particle_) < cone_size);
    }
    fastjet::PseudoJet particle_;
    DetectorGeometry detector_geometry_;
};

template <typename Multiplet>
std::vector<Multiplet> RemoveIfClose(std::vector<Multiplet> multiplets, const Jets& particles)
{
  for (const auto & particle : particles) multiplets.erase(std::remove_if(multiplets.begin(), multiplets.end(), Close(particle)), multiplets.end());
    return multiplets;
}

template <typename Multiplet>
std::vector<Multiplet> CopyIfClose(const std::vector<Multiplet>& multiplets, const Jets& particles)
{
    if (multiplets.empty()) return multiplets;
    std::vector<Multiplet> final_multiplets;
    for (const auto & particle : particles) for (const auto & multiplet : multiplets) if (Close(particle)(multiplet)) final_multiplets.emplace_back(multiplet);
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
fastjet::PseudoJet ClosestJet(const Jets& jets, const Multiplet& multiplet){
    return *std::min_element(jets.begin(), jets.end(), [&](const fastjet::PseudoJet& jet_1,const fastjet::PseudoJet& jet_2){
      return jet_1.delta_R(multiplet.Jet()) < jet_2.delta_R(multiplet.Jet());
    });
}

/**
 * @brief Join two std::vector
 *
 */
template <typename Element>
std::vector<Element> Join(const std::vector<Element>& vector_1, const std::vector<Element>& vector_2)
{
    std::vector<Element> joined;
    joined.reserve(vector_1.size() + vector_2.size());
    joined.insert(joined.end(), vector_1.begin(), vector_1.end());
    joined.insert(joined.end(), vector_2.begin(), vector_2.end());
    return joined;
}

/**
 * @brief Join two std::vector
 *
 */
template <typename Element>
std::vector<Element> Join(const std::vector<Element>& vector_1, const std::vector<Element>& vector_2, const std::vector<Element>& vector_3)
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
         auto ordered_pairs(const std::vector<Element>& container, Function function)
{
    std::vector<Result> results;
    for (auto element_1 = container.begin(); element_1 != container.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2) {
            try {
                results.emplace_back(function(*element_1, *element_2));
            } catch (...) {}
            try {
                results.emplace_back(function(*element_2, *element_1));
            } catch (...) {}
        }
    }
    return results;
}

template < typename Element, typename Function, typename Result = typename std::result_of<Function&(Element, Element)>::type >
/**
 * @brief forms all \f$(n^2 - n) / 2\f$ unordered pairs, applies to them the function and returns a vector of its results
 *
 */
auto unordered_pairs(const std::vector<Element>& container, Function function)
{
    std::vector<Result> results;
    for (auto element_1 = container.begin(); element_1 != container.end(); ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2)
            try {
                results.emplace_back(function(*element_1, *element_2));
            } catch (...) {}
    }
    return results;
}

template < typename Element1, typename Element2, typename Function, typename Result = typename std::result_of<Function&(Element1, Element2)>::type >
/**
 * @brief forms all \f$n^2\f$ pairs of the elements in the two containers, applies the function and returns a vector of its elements
 *
 */
auto pairs(const std::vector<Element1>& container_1, const std::vector<Element2>& container_2, Function function)
{
    std::vector<Result> results;
    for (const auto element_1 : container_1) {
        for (const auto element_2 : container_2) {
            try {
                results.emplace_back(function(element_1, element_2));
            } catch (...) {}
        }
    }
    return results;
}

template < typename Element1, typename Element2, typename Function, typename Result = typename std::result_of<Function&(Element1,Element1, Element2)>::type >
/**
 * @brief forms all \f$(n^2 - n) / 2\f$ unordered pairs, applies to them the function and returns a vector of its results
 *
 */
auto triples(const std::vector<Element1>& container1, const std::vector<Element2>& container2,Function function)
{
  std::vector<Result> results;
  for (auto element_1 = container1.begin(); element_1 != container1.end(); ++element_1) {
    for (auto element_2 = std::next(element_1); element_2 != container1.end(); ++element_2)
      for(const auto element_3 : container2){
        try {
          results.emplace_back(function(*element_1, *element_2, element_3));
       } catch (...) {}
  }
  }
  return results;
}


}
