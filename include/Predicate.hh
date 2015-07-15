#pragma once

#include "DetectorGeometry.hh"
#include "Global.hh"
#include "LorentzVector.hh"

namespace analysis
{

struct MinDeltaRTo {
    MinDeltaRTo(const fastjet::PseudoJet &jet) {
        jet_ = jet;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet1, const Multiplet &multiplet2) {
        return multiplet1.Jet().delta_R(jet_)  < multiplet2.Jet().delta_R(jet_);
    }
    bool operator()(const fastjet::PseudoJet &jet1, const fastjet::PseudoJet &jet2) {
        return jet1.delta_R(jet_)  < jet2.delta_R(jet_);
    }
    fastjet::PseudoJet jet_;
};

template<typename Multiplet>
std::vector<Multiplet> SortedByMinDeltaRTo(std::vector<Multiplet> &multiplets, const fastjet::PseudoJet &jet)
{
    std::sort(multiplets.begin(), multiplets.end(), MinDeltaRTo(jet));
    return multiplets;
}

struct MaxDeltaRap {
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
        return (multiplet_1.DeltaRap() > multiplet_2.DeltaRap());
    }
};

template <class Multiplet>
std::vector<Multiplet> SortByMaxDeltaRap(std::vector<Multiplet> &multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), MaxDeltaRap());
    return multiplets;
}

struct SortByMassTo {
    SortByMassTo(const float mass) {
        mass_ = mass;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet &Multiplet1, const Multiplet &Multiplet2) {
        return std::abs(Multiplet1.Jet().m() - mass_) < std::abs(Multiplet2.Jet().m() - mass_);
    }
    float mass_;
};

template <class Multiplet>
std::vector<Multiplet> SortedByMassTo(std::vector<Multiplet> &multiplets, const float mass)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByMassTo(mass));
    return multiplets;
}

struct SortByMass {
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
        return multiplet_1.Mass() > multiplet_2.Mass();
    }
    bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2) {
        return jet_1.m() > jet_2.m();
    }
};

template <class Multiplet>
std::vector<Multiplet> SortedByMass(std::vector<Multiplet> &multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByMass());
    return multiplets;
}


struct SortByPt {
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
        return multiplet_1.Jet().pt() > multiplet_2.Jet().pt();
    }
    bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2) {
        return jet_1.pt() > jet_2.pt();
    }
    bool operator()(const LorentzVector &lorentz_vector_1, const LorentzVector &lorentz_vector_2) {
        return (lorentz_vector_1.Pt() > lorentz_vector_2.Pt());
    }

};

template <class Multiplet>
std::vector<Multiplet> SortedByPt(std::vector<Multiplet> &multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByPt());
    return multiplets;
}

template <typename Element>
bool FindInVector(const std::vector<Element> vector, const Element element)
{
    return (std::find(vector.begin(), vector.end(), element) != vector.end());
}

/**
 * @brief create a fastjet::PseudoJet from a LorentzVector
 *
 */
fastjet::PseudoJet PseudoJet(const TLorentzVector &vector);

fastjet::PseudoJet PseudoJet(const LorentzVector &vector);

Jets CopyIfAbsParticle(const Jets &jets, const Id id);

Jets CopyIfAbsParticle(const Jets &jets, const Id id_1, const Id id_2);

Jets copy_if_neutrino(const Jets &jets);

Jets CopyIfParticle(const Jets &jets, const int id);

Jets remove_if_particle(const Jets &jets, const int id);

Jets remove_if_not_in_pt_window(Jets &jets, const float lower_cut, const float upper_cut);

Jets RemoveIfWrongAbsFamily(const Jets &jets, const Id id, Id mother_id);

Jets RemoveIfWrongFamily(const Jets &jets, const int id, int mother_id);

Jets RemoveIfWrongAbsStepFamily(const Jets &jets, const Id id , const Id mother_2_id);

Jets RemoveIfWrongAbsStepMother(const Jets &jets, const int mother_2_id);

Jets RemoveIfWrongParticle(const Jets &jets, const int id);

Jets RemoveIfWrongAbsParticle(const Jets &jets, const Id id);

Jets RemoveIfWrongAbsMother(const Jets &jets, const Id mother_id);

Jets CopyIfAbsMother(const Jets &jets, const Id mother_id);

Jets RemoveIfAbsMother(const Jets &jets, const Id mother_id);

Jets RemoveIfLetpons(const Jets &jets);

Jets RemoveIfQuark(const Jets &jets);

Jets CopyIfQuark(const Jets &jets);

Jets RemoveIfNot5Quarks(const Jets &jets);

Jets RemoveIfSoft(const Jets &jets, const float pt_min);


struct Close {
    Close(const fastjet::PseudoJet &particle) {
        particle_ = particle;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet) {
        return (multiplet.Jet().delta_R(particle_) < detector_geometry_.JetConeSize()
//         & multiplet.Jet().delta_R(particle_) < multiplet.Radius()
               );
    }
    bool operator()(const fastjet::PseudoJet &jet) {
        return (jet.delta_R(particle_) < detector_geometry_.JetConeSize());
    }
    fastjet::PseudoJet particle_;
    DetectorGeometry detector_geometry_;
};

struct Close2 {
    Close2(const fastjet::PseudoJet &particle) {
        particle_ = particle;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet) {
        return (multiplet.Jet().delta_R(particle_) < detector_geometry_.JetConeSize());
    }
    bool operator()(const fastjet::PseudoJet &jet) {
        return (jet.delta_R(particle_) < detector_geometry_.JetConeSize());
    }
    fastjet::PseudoJet particle_;
    DetectorGeometry detector_geometry_;
};

template <typename Multiplet>
std::vector<Multiplet> RemoveIfClose(const std::vector<Multiplet> &jets, const Jets &particles)
{
    std::vector<Multiplet> quarks = jets;
    for (const auto & particle : particles) quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Close(particle)), quarks.end());
    return quarks;
}

template <typename Multiplet>
std::vector<Multiplet> CopyIfClose(const std::vector<Multiplet> &multiplets, const Jets &particles)
{
    if (multiplets.empty()) return multiplets;
    std::vector<Multiplet> final_multiplets;
    for (const auto & particle : particles) for (const auto & multiplet : multiplets) if (Close(particle)(multiplet)) final_multiplets.emplace_back(multiplet);
    return final_multiplets;
}

/**
 * @brief provides an integer with the necessary information to work with range based for loop
 *
 */
class Range
{
public:
    Range(const int sum) : last_(sum), iterator_(0) {}

    const Range &begin() const {
        return *this;
    }
    const Range &end() const {
        return *this;
    }
    bool operator!=(const Range &) const {
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
std::vector<Element> Join(const std::vector<Element> &vector_1, const std::vector<Element> &vector_2)
{
    std::vector<Element> joined;
    joined.reserve(vector_1.size() + vector_2.size());
    joined.insert(joined.end(), vector_1.begin(), vector_1.end());
    joined.insert(joined.end(), vector_2.begin(), vector_2.end());
    return joined;
}

template<typename Container, typename Result, typename Function>
auto ordered_pairs(const Container &container, Result &result, Function function)
{
    for (auto element_1 = container.begin(); element_1 != container.end() - 1; ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2) {
            result.emplace_back(function(*element_1, *element_2));
            result.emplace_back(function(*element_2, *element_1));
        }
    }
    return result;
}

template<typename Container, typename Result, typename Function>
auto unordered_pairs(const Container &container, Result &result, Function function)
{
    for (auto element_1 = container.begin(); element_1 != container.end() - 1; ++element_1) {
        for (auto element_2 = std::next(element_1); element_2 != container.end(); ++element_2) {
            result.emplace_back(function(*element_1, *element_2));
        }
    }
    return result;
}

template<typename Container1, typename Container2, typename Result, typename Function>
auto pairs(const Container1 &container_1, const Container1 &container_2, Result &result, Function function)
{
    for (const auto element_1 : container_1) {
        for (const auto element_2 : container_2) {
            result.emplace_back(function(element_1, element_2));
        }
    }
    return result;
}

template <typename Value>
int sgn(const Value value)
{
    return (Value(0) < value) - (value < Value(0));
}


/**
 * @brief Calcualte distance in eta phi space
 *
 */
float Distance(const float rapidity_1, const float phi_1, const float rapidity_2, const float phi_2);

/**
 * @brief Calcualte distance from center in eta phi space
 *
 */
float Length(const float rapidity, const float phi);

/**
 * @brief Take care of phi angles around pi
 *
 */
float DeltaPhi(const float phi_1, const float phi_2);

template <typename Enumeration>
auto to_int(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

}
