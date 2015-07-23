#pragma once

#include <vector>
#include <string>

namespace fastjet {
class PseudoJet;
}

/**
 * @brief analysis namespace containing the general analysis and SM taggers
 *
 */
namespace analysis {

class LorentzVector;

typedef std::vector<fastjet::PseudoJet> Jets;
typedef std::vector<LorentzVector> Vectors;
typedef std::vector<std::string> Strings;



enum class Severity {
    error,
    notification,
    information,
    debug,
    detailed
};

enum class Id {
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
    pi0 = 111,
    rho0 = 113,
    K0L = 130,
    pion = 211,
    rho = 213,
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

std::string Name(int id);

std::string Name(const Id id);

float Mass(const Id id);

/**
 * @brief Initial user index
 *
 */
static int EmptyUserIndex = -1;

/**
 * @brief Position outside of a vector
 *
 */
static int EmptyPosition = -1;


int LargeNumber();

}
