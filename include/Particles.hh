/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <string>
/**
 * @brief contains the general analysis and SM taggers
 *
 */
namespace boca
{

/**
 * @brief PDG particle naming conventions
 *
 */
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
    higgs = 25, ///< Higgs boson
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
    K0l = 130,
    pion = 211,
    rho = 213,
    eta = 221,
    omega = 223,
    K0s = 310,
    K0 = 311,
    K0S = 313,
    K = 321,
    KS = 323,
    etaP = 331,
    D = 411,
    DS = 413,
    DS2 = 415,
    D0 = 421,
    DS0 = 423,
    etac = 441,
    B0 = 511,
    B0S = 513,
    B = 521,
    BS = 523,
    BS0 = 531,
    BsS0 = 533,
    down_down_1 = 1103,
    up_down_0 = 2101,
    up_down_1 = 2103,
    Delta = 1114,
    neutron = 2112,
    up_up_1 = 2203,
    proton = 2212,
    Delta_2 = 2224,
    CP_violating_higgs = 5000000
};

std::string Name(int id);

std::string Name(Id id);

float Mass(Id id);

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

}