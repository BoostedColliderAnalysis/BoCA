#pragma once

#include <vector>

#include "TLorentzVector.h"
#include "fastjet/PseudoJet.hh"

/**
 * @brief analysis namespace containing the general analysis and SM taggers
 *
 */
namespace analysis
{

typedef std::vector<fastjet::PseudoJet> Jets;
typedef std::vector<TLorentzVector> Vectors;
typedef std::vector<std::string> Strings;

template <typename Value>
int sgn(const Value value)
{
    return (Value(0) < value) - (value < Value(0));
}

int LargeNumber();

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

enum class Severity
{
    error,
    notification,
    information,
    debug,
    detailed
};

enum class Id
{
    empty = 0,
    down = 1,
    up = 2,
    strange = 3,
    charm = 4,
    bottom = 5,
    top = 6,
    top_partner = 8,
    electron = 11,
    electron_neutrino = 12,
    muon = 13,
    muon_neutrino = 14,
    tau = 15,
    tau_neutrino = 16,
    gluon = 21,
    photon = 22,
    Z = 23,
    W = 24,
    higgs = 25, //<Higgs boson
    heavy_higgs = 35,
    CP_odd_higgs = 36,
    charged_higgs = 37,
    any = 86,
    isr = 87,
    marker = 88,
    mixed_jet = 90,
    cluster = 91,
    string = 92,
    Pi0Meson = 111,
    Rho0Meson = 113,
    K0LMeson = 130,
    Pion = 211,
    RhoMeson = 213,
    RapMeson = 221,
    OmegaMeson = 223,
    K0SMeson = 310,
    KMeson0 = 311,
    KMeson0S = 313,
    KMeson = 321,
    KMesonS = 323,
    RapPMeson = 331,
    DMeson = 411,
    DMesonS = 413,
    DMesonS2 = 415,
    DMeson0 = 421,
    DMesonS0 = 423,
    RapCMeson = 441,
    BMeson0 = 511,
    BMeson0S = 513,
    BMeson = 521,
    BMesonS = 523,
    BMesonS0 = 531,
    BMesonSS0 = 533,
    down_down_1 = 1103,
    up_down_0 = 2101,
    up_down_1 = 2103,
    DeltaBaryon = 1114,
    neutron = 2112,
    up_up_1 = 2203,
    proton = 2212,
    Delta_2 = 2224,
    CP_violating_higgs = 5000000
};

template <typename Enumeration>
auto to_int(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

std::string Name(const int id);

std::string Name(const Id id);

float Mass(const Id id);

/**
 * @brief Initial user index
 *
 */
static const int EmptyUserIndex = -1;

/**
 * @brief Position outside of a vector
 *
 */
static const int EmptyPosition = -1;

}
