#pragma once

#include <functional>
#include "Global.hh"
#include "DetectorGeometry.hh"
#include "Constituent.hh"

namespace analysis
{

/**
 * @brief create a fastjet::PseudoJet from a LorentzVector
 *
 */
fastjet::PseudoJet PseudoJet(const TLorentzVector& vector);

fastjet::PseudoJet PseudoJet(const LorentzVector& vector);

Jets CopyIfParticle(const Jets& jets, Id id);

Jets CopyIfParticles(const Jets& jets, Id id_1, Id id_2);

Jets CopyIfNeutrino(const Jets& jets);

Jets CopyIfExactParticle(const Jets& jets, int id);

Jets RemoveIfExactParticle(const Jets& jets, int id);

Jets RemoveIfOutsidePtWindow(Jets& jets, float lower_cut, float upper_cut);

Jets CopyIfFamily(const Jets& jets, Id id, Id mother_id);

/**
 * @brief returns only particles with the correct id and non fitting grand mother id
 *
 */
Jets RemoveIfGrandFamily(const Jets& jets, Id id , Id grand_mother_id);

Jets CopyIfParticle(const Jets& jets, Id id);

Jets RemoveIfParticle(const Jets& jets, Id id);

Jets CopyIfMother(const Jets& jets, Id mother_id);

Jets RemoveIfMother(const Jets& jets, Id mother_id);

Jets RemoveIfSingleMother(const Jets& jets);

Jets RemoveIfLetpon(const Jets& jets);

Jets RemoveIfQuark(const Jets& jets);

Jets CopyIfQuark(const Jets& jets);

Jets CopyIf5Quark(const Jets& jets);

Jets RemoveIfSoft(const Jets& jets, float pt_min);


/**
 * @brief Calcualte distance in eta phi space
 *
 */
float Distance(float rapidity_1, float phi_1, float rapidity_2, float phi_2);

/**
 * @brief Calcualte distance from center in eta phi space
 *
 */
float Length(float rapidity, float phi);

/**
 * @brief Take care of phi angles around pi
 *
 */
float DeltaPhi(float phi_1, float phi_2);

float RestrictPhi(float phi);

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
    fastjet::PseudoJet particle_;
    DetectorGeometry detector_geometry_;
};

template <typename Multiplet>
std::vector<Multiplet> RemoveIfClose(const std::vector<Multiplet>& jets, const Jets& particles)
{
    std::vector<Multiplet> quarks = jets;
    for (const auto & particle : particles)
        quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Close(particle)), quarks.end());
    return quarks;
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

struct MinDeltaRTo {
    MinDeltaRTo(const fastjet::PseudoJet& jet) {
        jet_ = jet;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet& multiplet1, const Multiplet& multiplet2) {
        return multiplet1.Jet().delta_R(jet_)  < multiplet2.Jet().delta_R(jet_);
    }
    bool operator()(const fastjet::PseudoJet& jet1, const fastjet::PseudoJet& jet2) {
        return jet1.delta_R(jet_)  < jet2.delta_R(jet_);
    }
    fastjet::PseudoJet jet_;
};

template<typename Multiplet>
std::vector<Multiplet> SortedByMinDeltaRTo(std::vector<Multiplet>& multiplets, const fastjet::PseudoJet& jet)
{
    std::sort(multiplets.begin(), multiplets.end(), MinDeltaRTo(jet));
    return multiplets;
}

struct MaxDeltaRap {
    template <typename Multiplet>
    bool operator()(const Multiplet& multiplet_1, const Multiplet& multiplet_2) {
        return (multiplet_1.DeltaRap() > multiplet_2.DeltaRap());
    }
};

template <class Multiplet>
std::vector<Multiplet> SortByMaxDeltaRap(std::vector<Multiplet>& multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), MaxDeltaRap());
    return multiplets;
}

struct SortByMassTo {
    SortByMassTo(float mass) {
        mass_ = mass;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet& Multiplet1, const Multiplet& Multiplet2) {
        return std::abs(Multiplet1.Jet().m() - mass_) < std::abs(Multiplet2.Jet().m() - mass_);
    }
    float mass_;
};

template <class Multiplet>
std::vector<Multiplet> SortedByMassTo(std::vector<Multiplet>& multiplets, float mass)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByMassTo(mass));
    return multiplets;
}

struct SortByMass {
    template <typename Multiplet>
    bool operator()(const Multiplet& multiplet_1, const Multiplet& multiplet_2) {
        return multiplet_1.Mass() > multiplet_2.Mass();
    }
    bool operator()(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2) {
        return jet_1.m() > jet_2.m();
    }
};

template <class Multiplet>
std::vector<Multiplet> SortedByMass(std::vector<Multiplet>& multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByMass());
    return multiplets;
}


struct SortByPt {
    template <typename Multiplet>
    bool operator()(const Multiplet& multiplet_1, const Multiplet& multiplet_2) {
        return multiplet_1.Jet().pt() > multiplet_2.Jet().pt();
    }
    bool operator()(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2) {
        return jet_1.pt() > jet_2.pt();
    }
    bool operator()(const LorentzVector& lorentz_vector_1, const LorentzVector& lorentz_vector_2) {
        return (lorentz_vector_1.Pt() > lorentz_vector_2.Pt());
    }
    bool operator()(const Constituent& constituent_1, const Constituent& constituent_2) {
        return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
    }

};

template <class Multiplet>
std::vector<Multiplet> SortedByPt(std::vector<Multiplet>& multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByPt());
    return multiplets;
}

template <class Multiplet>
std::vector<Multiplet> SortedByPt(const std::vector<Multiplet>& multiplets)
{
    std::vector<Multiplet> final_multiplets = multiplets;
    std::sort(final_multiplets.begin(), final_multiplets.end(), SortByPt());
    return final_multiplets;
}

template <typename Element>
bool FindInVector(const std::vector<Element> vector, const Element element)
{
    return (std::find(vector.begin(), vector.end(), element) != vector.end());
}

/**
 * @brief provides an integer with the necessary information to work with range based for loop
 *
 */
class Range
{
public:
    Range(int sum) : last_(sum), iterator_(0) {}

    Range(int low, int sum) : last_(sum), iterator_(std::max(low - 1, 0)) {}

    const Range& begin() const {
        return *this;
    }
    const Range& end() const {
        return *this;
    }
    bool operator!=(const Range&) const {
        return iterator_ < last_;
    }
    void operator++() {
        ++iterator_;
    }
    int operator*() const {
        return iterator_;
    }
private:
    int last_;
    int iterator_;
};

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

template < typename Element,
         typename Function,
         typename Result = typename std::result_of<Function&(Element, Element)>::type >
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

template <typename Value>
int sgn(Value value)
{
    return (Value(0) < value) - (value < Value(0));
}

template <typename Value>
Value sqr(Value value)
{
  return value * value;
}

template <typename Enumeration>
auto to_int(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

}
