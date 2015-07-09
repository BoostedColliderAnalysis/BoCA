#pragma once

#include <vector>

#include "fastjet/PseudoJet.hh"
#include "TLorentzVector.h"
#include "LorentzVector.hh"

/**
 * @brief analysis namespace containing the general analysis and SM taggers
 *
 */
namespace analysis
{

// // dropin replacement for the slow TLorentzVector classes
// class Vector3
// {
//
// public:
//
//     float Pt() const {
//         return Perp();
//     };
//
//     float Perp() const {
//         return std::sqrt(std::pow(x_, 2) + std::pow(y_, 2));
//     }
//
//     void SetXYZ(float x, float y, float z) {
//         x_ = x;
//         y_ = y;
//         z_ = z;
//     }
//
//     void operator=(const TVector3 &vector){
//       x_ = vector.X();
//       y_ = vector.Y();
//       z_ = vector.Z();
//     }
//
// private:
//
//     float x_, y_, z_;
//
// };
//
//
// class LorentzVector
// {
//
// public:
//
//     float Perp() const {
//         return vector_.Perp();
//     }
//
//     float Pt() const {
//         return Perp();
//     }
//
//     void SetPtEtaPhiE(float pt, float eta, float phi, float e) {
//         pt = std::abs(pt);
//         SetXYZT(pt * std::cos(phi), pt * std::sin(phi), pt * std::sinh(eta) , e);
//     }
//
//     void SetXYZT(float  x, float  y, float  z, float t) {
//         vector_.SetXYZ(x, y, z);
//         SetT(t);
//     }
//
//     void SetPtEtaPhiM(float pt, float eta, float phi, float m) {
//         pt = std::abs(pt);
//         SetXYZM(pt * std::cos(phi), pt * std::sin(phi), pt * std::sinh(eta) , m);
//     }
//
//     void SetXYZM(float  x, float  y, float  z, float m) {
//         if (m  >= 0) SetXYZT(x, y, z, std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(m, 2)));
//         else SetXYZT(x, y, z, std::sqrt(std::max((std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) - std::pow(m, 2)), 0.)));
//     }
//
//     void SetT(float t) {
//         t_ = t;
//     }
//
//     void operator=(const TLorentzVector &lorentzvector){
//       vector_ = lorentzvector.Vect();
//       t_ = lorentzvector.T();
//     }
//
//     float Px() const { return X(); }
//     float Py() const { return Y(); }
//     float Pz() const { return Z(); }
//     float P()  const { return vector_.Mag(); }
//     float E()  const { return T(); }
//
//     float X() const { return vector_.X(); }
//     float Y() const { return vector_.Y(); }
//     float Z() const { return vector_.Z(); }
//     float T() const { return fE; }
//
// private:
//
//     Vector3 vector_;
//
//     float t_;
//
// };







typedef std::vector<fastjet::PseudoJet> Jets;
typedef std::vector<LorentzVector> Vectors;
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
