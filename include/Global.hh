# pragma once

# include <iostream>
# include <iomanip>
# include <cmath>
# include <vector>

# include "TLorentzVector.h"

# include "fastjet/PseudoJet.hh"

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

template <typename Element>
/**
 * @brief Join two std::vector
 *
 */
std::vector<Element> Join(const std::vector<Element> &vector_1, const std::vector<Element> &vector_2)
{
    std::vector<Element> joined;
    joined.reserve(vector_1.size() + vector_2.size());
    joined.insert(joined.end(), vector_1.begin(), vector_1.end());
    joined.insert(joined.end(), vector_2.begin(), vector_2.end());
    return joined;
}

enum class Tag
{
    Background = 0,
    Signal = 1

};

enum class Severity
{
    Error,
    Notification,
    Information,
    Debug,
    Detailed
};

enum class Id
{
    Empty = 0,
    Down = 1,
    Up = 2,
    Strange = 3,
    Charm = 4,
    Bottom = 5,
    Top = 6,
    TopPartner = 8,
    Electron = 11,
    ElectronNeutrino = 12,
    Muon = 13,
    MuonNeutrino = 14,
    Tau = 15,
    TauNeutrino = 16,
    Gluon = 21,
    Photon = 22,
    Z = 23,
    W = 24,
    Higgs = 25,
    HeavyHiggs = 35,
    CPOddHiggs = 36,
    ChargedHiggs = 37,
    Any = 86,
    Isr = 87,
    Marker = 88,
    MixedJet = 90,
    Cluster = 91,
    String = 92,
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
    DownDown1 = 1103,
    UpDown0 = 2101,
    UpDown1 = 2103,
    DeltaBaryon = 1114,
    Neutron = 2112,
    UpUp1 = 2203,
    Proton = 2212,
    DeltaBaryon2 = 2224,
    CpvHiggs = 5000000
};

enum class Status
{
    None = 0,
    Stable = 1,
    Unstable = 2,
    Generator = 3
};

template <typename Enumeration>
auto to_int(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

std::string Name(const int id);

std::string Name(const Id id);

std::string Name(const Tag tag);

float Mass(const Id id);

}
