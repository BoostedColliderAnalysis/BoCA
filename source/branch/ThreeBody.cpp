/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/ThreeBody.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace branch
{

ThreeBody::ThreeBody()
{
    ht = InitialValue();
    bdt_1 = InitialValue();
    bdt_2 = InitialValue();
    bdt_3 = InitialValue();
    mass_12 = InitialValue();
    mass_23 = InitialValue();
    mass_13 = InitialValue();
    delta_pt_12 = InitialValue();
    delta_pt_23 = InitialValue();
    delta_pt_13 = InitialValue();
    pt_12 = InitialValue();
    pt_23 = InitialValue();
    pt_13 = InitialValue();
    ht_12 = InitialValue();
    ht_23 = InitialValue();
    ht_13 = InitialValue();
    rho_12 = InitialValue();
    rho_23 = InitialValue();
    rho_13 = InitialValue();
    delta_rap_12 = InitialValue();
    delta_rap_23 = InitialValue();
    delta_rap_13 = InitialValue();
    delta_phi_12 = InitialValue();
    delta_phi_23 = InitialValue();
    delta_phi_13 = InitialValue();
    delta_r_12 = InitialValue();
    delta_r_23 = InitialValue();
    delta_r_13 = InitialValue();
    delta_m_12 = InitialValue();
    delta_m_23 = InitialValue();
    delta_m_13 = InitialValue();
    delta_ht_23 = InitialValue();
    delta_ht_13 = InitialValue();
    pull_23 = InitialValue();
    pull_13 = InitialValue();
    pull_32 = InitialValue();
    pull_31 = InitialValue();
    dipolarity_23 = InitialValue();
    dipolarity_13 = InitialValue();
    sphericity = InitialValue();
    aplanarity = InitialValue();
}

Observables ThreeBody::Variables()
{
        auto substructure = Settings::SubStructure() ?
           OBSERVABLE(pull_23, "#theta_{23}") +
           OBSERVABLE(pull_13, "#theta_{13}") +
           OBSERVABLE(pull_32, "#theta_{32}") +
           OBSERVABLE(pull_31, "#theta_{31}") :
//            OBSERVABLE(dipolarity_23, "D_{23}") +
//            OBSERVABLE(dipolarity_13, "D_{13}") +
           boca::Observables{};
    return Particle::Variables() +
           OBSERVABLE(ht, "H_{T}") +
           OBSERVABLE(bdt_1, "BDT_{1}") +
           OBSERVABLE(bdt_2, "BDT_{2}") +
           OBSERVABLE(bdt_3, "BDT_{3}") +
           OBSERVABLE(mass_12, "m_{12}") +
           OBSERVABLE(mass_23, "m_{23}") +
           OBSERVABLE(mass_13, "m_{13}") +
           OBSERVABLE(pt_12, "p_{T}^{12}") +
           OBSERVABLE(pt_23, "p_{T}^{23}") +
           OBSERVABLE(pt_13, "p_{T}^{13}") +
           OBSERVABLE(delta_pt_12, "\\Delta p_{T}^{12}") +
           OBSERVABLE(delta_pt_23, "\\Delta p_{T}^{23}") +
           OBSERVABLE(delta_pt_13, "\\Delta p_{T}^{13}") +
           OBSERVABLE(ht_12, "H_{T}^{12}") +
           OBSERVABLE(ht_23, "H_{T}^{23}") +
           OBSERVABLE(ht_13, "H_{T}^{13}") +
           OBSERVABLE(rho_12, "\\rho_{12}") +
           OBSERVABLE(rho_23, "\\rho_{23}") +
           OBSERVABLE(rho_13, "\\rho_{13}") +
           OBSERVABLE(delta_rap_12, "\\Delta\\eta_{12}") +
           OBSERVABLE(delta_rap_23, "\\Delta\\eta_{23}") +
           OBSERVABLE(delta_rap_13, "\\Delta\\eta_{13}") +
           OBSERVABLE(delta_phi_12, "\\Delta\\phi_{12}") +
           OBSERVABLE(delta_phi_23, "\\Delta\\phi_{23}") +
           OBSERVABLE(delta_phi_13, "\\Delta\\phi_{13}") +
           OBSERVABLE(delta_r_12, "\\Delta R_{12}") +
           OBSERVABLE(delta_r_23, "\\Delta R_{23}") +
           OBSERVABLE(delta_r_13, "\\Delta R_{13}") +
           OBSERVABLE(delta_m_12, "\\Delta m_{12}") +
           OBSERVABLE(delta_m_23, "\\Delta m_{23}") +
           OBSERVABLE(delta_m_13, "\\Delta m_{13}") +
           OBSERVABLE(delta_ht_12, "\\Delta H_{T}^{12}") +
           OBSERVABLE(delta_ht_23, "\\Delta H_{T}^{23}") +
           OBSERVABLE(delta_ht_13, "\\Delta H_{T}^{13}") +
           substructure;
}

Observables ThreeBody::Spectators()
{
    return Particle::Spectators()
// + OBSERVABLE(aplanarity, "#slashed{P}") +  OBSERVABLE(sphericity, "S")
           ;
}

}

}
