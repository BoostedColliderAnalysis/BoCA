/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Particles.hh"
#include "Types.hh"

namespace boca
{

std::string Name(int id)
{
    std::string sign = "";
    if (id < 0) sign = "-";
    return sign + Name(Id(id));
}

std::string Name(Id id)
{
    switch (id) {
        //     case Id::empty: return "Empty";
    case Id::down : return "d";
    case Id::up : return "u";
    case Id::strange : return "s";
    case Id::charm : return "c";
    case Id::bottom : return "b";
    case Id::top : return "t";
    case Id::top_partner : return "T";
    case Id::electron : return "e";
    case Id::electron_neutrino : return "nue";
    case Id::muon : return "mu";
    case Id::muon_neutrino : return "numu";
    case Id::tau : return "tau";
    case Id::tau_neutrino : return "nutau";
    case Id::gluon : return "g";
    case Id::photon : return "gamma";
    case Id::Z : return "Z";
    case Id::W : return "W";
    case Id::higgs : return "h";
    case Id::heavy_higgs : return "H";
    case Id::CP_odd_higgs : return "A";
    case Id::charged_higgs : return "H+";
    case Id::isr : return "ISR";
    case Id::marker : return "TEMP";
    case Id::cluster : return "Cluster";
    case Id::string : return "String";
    case Id::mixed_jet : return "MixJet";
    case Id::pi0 : return "pi0";
    case Id::rho0 : return "rho0";
    case Id::K0l : return "K0l";
    case Id::pion : return "pi";
    case Id::rho : return "rho";
    case Id::eta : return "eta";
    case Id::omega : return "omega";
    case Id::K0s : return "K0s";
    case Id::K0 : return "K0";
    case Id::K0S : return "K0*";
    case Id::K : return "K";
    case Id::KS : return "K*";
    case Id::etaP : return "etaP";
    case Id::D : return "D";
    case Id::DS : return "D*";
    case Id::DS2 : return "D*2";
    case Id::D0 : return "D0";
    case Id::DS0 : return "D*0";
    case Id::etac : return "etac";
    case Id::B0 : return "B0";
    case Id::B0S : return "B0*";
    case Id::B : return "B";
    case Id::BS : return "B*";
    case Id::BS0 : return "B*0";
    case Id::BsS0 : return "Bs*0";
    case Id::down_down_1 : return "dd1";
    case Id::up_down_0 : return "ud0";
    case Id::up_down_1 : return "ud1";
    case Id::Delta : return "Delta";
    case Id::neutron : return "n";
    case Id::up_up_1 : return "uu1";
    case Id::proton : return "p";
    case Id::Delta_2 : return "Delta2";
    case Id::CP_violating_higgs : return "h";
    default : return std::to_string(to_int(id));
    }
}

float MassOf(Id id)
{
    switch (id) {
    case Id::strange : return 0.095;
    case Id::charm : return 1.28;
    case Id::bottom : return 4.18;
    case Id::top : return 173.5;
    case Id::electron : return 0.000511;
    case Id::electron_neutrino : return 0;
    case Id::muon : return 0.1134;
    case Id::muon_neutrino : return 0;
    case Id::tau : return 1.776;
    case Id::tau_neutrino : return 0;
    case Id::photon : return 0;
    case Id::Z : return 91.188;
    case Id::W : return 80.39;
    case Id::higgs : return 125;
    case Id::pi0 : return 0.13498;
    case Id::pion : return 0.13957;
    case Id::rho : return 0.77549;
    case Id::eta : return 0.54785;
    case Id::omega : return 0.78265;
    case Id::neutron : return 1.00866;
    case Id::proton : return 0.93827;
    case Id::CP_violating_higgs : return MassOf(Id::higgs);
    default : return 0;
    }
}

}
