/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/TopHadronicHep.hh"
#include "boca/branch/Base.hh"
#include "boca/OBSERVABLE.hh"

namespace boca
{

namespace standardmodel
{

namespace branch
{

TopHadronicHep::TopHadronicHep()
{
    bottom_mass = InitialValue();
    w_mass = InitialValue();
}

Observables TopHadronicHep::Variables()
{
    return OBSERVABLE(mass, latex::String("m") + " [GeV]") +
           OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]"); // masses
    return OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") +
           OBSERVABLE(mass, latex::String("m") + " [GeV]") +
           OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") +
           OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") +
           OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) +
           OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) +
           OBSERVABLE(delta_r, latex::String("\\Delta R")) +
           OBSERVABLE(rho, latex::String("\\rho")) +
           OBSERVABLE(bottom_mass, latex::String("m_{b}") + " [GeV]") +
           OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]"); // kinematics
    return OBSERVABLE(mass, latex::String("m") + " [GeV]"); // just mass
    return BottomBase::Variables() +
           OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") +
           OBSERVABLE(mass, latex::String("m") + " [GeV]") +
           OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") +
           OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") +
           OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) +
           OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) +
           OBSERVABLE(delta_r, latex::String("\\Delta R")) +
           OBSERVABLE(rho, latex::String("\\rho")) +
           OBSERVABLE(bottom_mass, latex::String("m_{b}") + " [GeV]") +
           OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]") +
           OBSERVABLE(pull_1, latex::String("#theta_{1}")) +
           OBSERVABLE(pull_2, latex::String("#theta_{2}")) /*+
    OBSERVABLE(Dipolarity, latex::String("D"))*/; // bottom info
    return OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") +
           OBSERVABLE(mass, latex::String("m") + " [GeV]") +
           OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") +
           OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") +
           OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) +
           OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) +
           OBSERVABLE(delta_r, latex::String("\\Delta R")) +
           OBSERVABLE(rho, latex::String("\\rho")) +
           OBSERVABLE(bottom_mass, latex::String("m_{b}") + " [GeV]") +
           OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]") +
           OBSERVABLE(pull_1, latex::String("#theta_{1}")) +
           OBSERVABLE(pull_2, latex::String("#theta_{2}"))/* +
    OBSERVABLE(Dipolarity, latex::String("D"))*/; // subjet info
    return OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") +
           OBSERVABLE(mass, latex::String("m") + " [GeV]") +
           OBSERVABLE(pt, latex::String("p_T") + " [GeV]") +
           OBSERVABLE(ht, latex::String("H_{T}") + " [GeV]") +
           OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") +
           OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") +
           OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) +
           OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) +
           OBSERVABLE(delta_r, latex::String("\\Delta R")) +
           OBSERVABLE(rho, latex::String("\\rho")) +
           OBSERVABLE(pull_1, latex::String("#theta_{1}")) +
           OBSERVABLE(pull_2, latex::String("#theta_{2}")) /*+
    OBSERVABLE(Dipolarity, latex::String("D"))*/;
    return OBSERVABLE(lepton_pt) +
           OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") +
           OBSERVABLE(mass, latex::String("m") + " [GeV]") +
           OBSERVABLE(pt, latex::String("p_T") + " [GeV]") +
           OBSERVABLE(ht, latex::String("H_{T}") + " [GeV]") +
           OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") +
           OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") +
           OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) +
           OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) +
           OBSERVABLE(delta_r, latex::String("\\Delta R")) +
           OBSERVABLE(rho, latex::String("\\rho")) +
           OBSERVABLE(bdt_1, "BDT" + latex::String("_{W}")) +
           OBSERVABLE(bdt_2, "BDT" + latex::String("_{b}")) +
           OBSERVABLE(pull_1, latex::String("#theta_{1}")) +
           OBSERVABLE(pull_2, latex::String("#theta_{2}")) /*+
    OBSERVABLE(Dipolarity, latex::String("D"))*/;
}

Observables TopHadronicHep::Spectators()
{
    return Multi::Spectators() + BottomBase::Spectators();
}

}

}

}
