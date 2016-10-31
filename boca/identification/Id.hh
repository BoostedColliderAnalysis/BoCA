/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>
#include <vector>

#include "boca/units/ElectronVolt.hh"

/**
 * @ingroup Boca
 * @brief Boosted Collider %Analysis
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
    none = 0,
    down = 1, ///< Down Quark
    up = 2, ///< Up Quark
    strange = 3, ///< Strange Quark
    charm = 4, ///< Charm Quark
    bottom = 5, ///< Bottom Quark
    top = 6, ///< Top Quark
    bottom_partner = 7, ///< Bottom Partner Quark
    top_partner = 8, ///< Top Partner Quark
    electron = 11,                                          ///< %Electron
    electron_neutrino = 12,
    muon = 13,
    muon_neutrino = 14,
    tau = 15,
    tau_neutrino = 16,
    tau_partner = 17,
    tau_neutrino_partner = 18,
    gluon = 21,
    photon = 22,
    Z = 23,
    W = 24,
    higgs = 25, ///< Higgs boson
    Z_partner = 32,
    Z_partner_2 = 33,
    W_partner = 34,
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
    Dpm = 411,
    DS = 413,
    DS2 = 415,
    D0 = 421,
    DS0 = 423,
    etac = 441,
    B0 = 511,
    B0S = 513,
    Bpm = 521,
    BS = 523,
    BS0 = 531,
    BsS0 = 533,
    ypsilon = 553,
    down_down_1 = 1103,
    up_down_0 = 2101,
    up_down_1 = 2103,
    Delta = 1114,
    neutron = 2112,
    up_up_1 = 2203,
    proton = 2212,
    Delta_2 = 2224,
    CP_violating_higgs = 5000000,
    higgs_coupling = 9010221
};

/**
 * @brief Name of a particle with given PDG number
 *
 */
std::string Name(int id);

/**
 * @brief Name of a particle with given Id
 *
 */
std::string Name(Id id);

/**
 * @brief Stream the name of a particle with given Id
 *
 */
std::ostream& operator<<(std::ostream & stream, Id id);

/**
 * @brief Mass of particle with given Id
 *
 */
Mass MassOf(Id id);

/**
 * @brief Groups of PDG particles
 *
 */
enum class MultiId
{
    quark,
    five_quark,
    charged_lepton,
    neutrino,
    neutral_boson, ///< Multi particle containing neutral bosons
    bosons ///< Multi particle containing bosons
};

/**
 * @brief Names of PDG particle groups
 *
 */
std::string Name(MultiId multi_id);

/**
 * @brief Stream the name of a particle with given MultiId
 *
 */
std::ostream& operator<<(std::ostream & stream, MultiId id);

/**
 * @brief Common mass of a multi particle
 *
 */
Mass MassOf(MultiId multi_id);

/**
 * @brief Vector if PDG particle Ids for a given MultiId
 *
 */
std::vector<Id> Resolve(MultiId multi_id);

/**
 * @brief Lightest particle of a given MultiID
 *
 */
Id Lightest(MultiId multi_id);

/**
 * @brief Heaviest particle of a given MultiId
 *
 */
Id Heavyest(MultiId multi_id);

}
