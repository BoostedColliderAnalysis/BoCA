/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/TopHadronic.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace boca
{

namespace standardmodel
{

namespace branch
{

TopHadronic::TopHadronic()
{
  bottom_mass = InitialValue();
    w_mass = InitialValue();
}

Observables TopHadronic::Variables()
{
    return Multi::Variables() + BottomBase::Variables() /*+ LeptonVeto::Variables() */ + OBSERVABLE(w_mass) + OBSERVABLE(bottom_mass);
    return BottomBase::Variables() + OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(bdt_1, "BDT" + latex::String("_{W}")) + OBSERVABLE(bdt_2, "BDT" + latex::String("_{b}")) + OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) + OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) + OBSERVABLE(delta_r, latex::String("\\Delta R")) + OBSERVABLE(rho, latex::String("\\rho")) + OBSERVABLE(bottom_mass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]") + OBSERVABLE(pull_1, latex::String("#theta_{1}")) + OBSERVABLE(pull_2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/; // everything
    return OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]"); // masses
    return BottomBase::Variables() + OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) + OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) + OBSERVABLE(delta_r, latex::String("\\Delta R")) + OBSERVABLE(rho, latex::String("\\rho")) + OBSERVABLE(bottom_mass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]") + OBSERVABLE(pull_1, latex::String("#theta_{1}")) + OBSERVABLE(pull_2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/; // bottom
    return OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) + OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) + OBSERVABLE(delta_r, latex::String("\\Delta R")) + OBSERVABLE(rho, latex::String("\\rho")) + OBSERVABLE(bottom_mass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]"); // kinematics
    return OBSERVABLE(mass, latex::String("m") + " [GeV]"); // just mass
    return OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) + OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) + OBSERVABLE(delta_r, latex::String("\\Delta R")) + OBSERVABLE(rho, latex::String("\\rho")) + OBSERVABLE(bottom_mass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]") + OBSERVABLE(pull_1, latex::String("#theta_{1}")) + OBSERVABLE(pull_2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/; // subjet info
    return OBSERVABLE(delta_ht, latex::String("\\Delta H_{T}") + " [GeV]") + OBSERVABLE(bdt_1, "BDT" + latex::String("_{W}")) + OBSERVABLE(bdt_2, "BDT" + latex::String("_{b}")) + OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(delta_pt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(delta_m, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(delta_rap, latex::String("\\Delta \\eta")) + OBSERVABLE(delta_phi, latex::String("\\Delta \\phi")) + OBSERVABLE(delta_r, latex::String("\\Delta R")) + OBSERVABLE(rho, latex::String("\\rho")) + OBSERVABLE(bottom_mass, latex::String("m_{b}") + " [GeV]") + OBSERVABLE(w_mass, latex::String("m_{W}") + " [GeV]"); // kinematics + bdts
    return OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(bdt_1, "BDT" + latex::String("_{W}")); // mass and W bdt
    return OBSERVABLE(mass, latex::String("m") + " [GeV]") + OBSERVABLE(bdt_1, "BDT" + latex::String("_{W}")) + OBSERVABLE(bdt_2, "BDT" + latex::String("_{b}")); // mass and bdt
    return Multi::Variables() + BottomBase::Variables(); // FIXME usually we use the lepton pt
}

Observables TopHadronic::Spectators()
{
    return Multi::Spectators() + BottomBase::Spectators() + LeptonVeto::Spectators() + LeptonVeto::Variables();
}

}

}

}
