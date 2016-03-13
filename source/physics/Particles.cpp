/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boost/range/algorithm/min_element.hpp"
#include "boost/range/algorithm/max_element.hpp"
#include "physics/Particles.hh"
#include "physics/Prefixes.hh"
#include "Types.hh"
#include "DEBUG.hh"

namespace boca
{

std::string Name(int id)
{
    std::string sign = (id < 0) ? "-" : " ";
    return sign + Name(Id(std::abs(id)));
}

std::string Name(Id id)
{
    switch (id) {
    case Id::none: return " ";
    case Id::down : return "d";
    case Id::up : return "u";
    case Id::strange : return "s";
    case Id::charm : return "c";
    case Id::bottom : return "b";
    case Id::top : return "t";
    case Id::bottom_partner : return "B";
    case Id::top_partner : return "T";
    case Id::electron : return "e";
    case Id::electron_neutrino : return "νe";
    case Id::muon : return "μ";
    case Id::muon_neutrino : return "νμ";
    case Id::tau : return "τ";
    case Id::tau_neutrino : return "ντ";
    case Id::tau_partner : return "Tau";
    case Id::tau_neutrino_partner : return "νTau";
    case Id::gluon : return "g";
    case Id::photon : return "gamma";
    case Id::Z : return "Z";
    case Id::W : return "W";
    case Id::higgs : return "h";
    case Id::Z_partner : return "Z_2";
    case Id::Z_partner_2 : return "Z_3";
    case Id::W_partner : return "W_2";
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
        DEFAULT(to_int(id), std::to_string(to_int(id)));
    }
}

Mass MassOf(Id id)
{
    switch (id) {
    case Id::strange : return 0.095_GeV;
    case Id::charm : return 1.28_GeV;
    case Id::bottom : return 4.18_GeV;
    case Id::top : return 173.5_GeV;
    case Id::electron : return 0.000511_GeV;
    case Id::electron_neutrino : return massless;
    case Id::muon : return 0.1134_GeV;
    case Id::muon_neutrino : return massless;
    case Id::tau : return 1.776_GeV;
    case Id::tau_neutrino : return massless;
    case Id::photon : return massless;
    case Id::Z : return 91.188_GeV;
    case Id::W : return 80.39_GeV;
    case Id::higgs : return 125._GeV;
    case Id::pi0 : return 0.13498_GeV;
    case Id::pion : return 0.13957_GeV;
    case Id::rho : return 0.77549_GeV;
    case Id::eta : return 0.54785_GeV;
    case Id::omega : return 0.78265_GeV;
    case Id::neutron : return 1.00866_GeV;
    case Id::proton : return 0.93827_GeV;
    case Id::top_partner: return 1_TeV; //< FIXME remove again
    case Id::CP_violating_higgs : return MassOf(Id::higgs);
        DEFAULT(Name(id), massless);
    }
}
std::string Name(MultiId multi_id)
{
    switch (multi_id) {
    case MultiId::quark : return "q";
    case MultiId::five_quark : return "5FS q";
    case MultiId::charged_lepton : return "l";
    case MultiId::neutrino : return "ν";
    case MultiId::neutral_boson : return "B0";
    case MultiId::bosons : return "B";
        DEFAULT(to_int(multi_id), "");
    }
}

Mass MassOf(MultiId multi_id)
{
    switch (multi_id) {
    case MultiId::neutrino : return massless;
        DEFAULT(Name(multi_id), massless);
    }
}

std::vector<Id> Resolve(MultiId multi_id)
{
    switch (multi_id) {
    case MultiId::neutrino : return {Id::electron_neutrino, Id::muon_neutrino, Id::tau_neutrino};
    case MultiId::charged_lepton : return {Id::electron, Id::muon, Id::tau};
    case MultiId::quark : return {Id::up, Id::down, Id::strange, Id::charm, Id::bottom, Id::top};
    case MultiId::five_quark : return {Id::up, Id::down, Id::strange, Id::charm, Id::bottom};
    case MultiId::neutral_boson : return {Id::higgs, Id::CP_violating_higgs, Id::Z};
    case MultiId::bosons : return {Id::higgs, Id::CP_violating_higgs, Id::Z, Id::W};
        DEFAULT(Name(multi_id), {});
    }
}

Id Lightest(MultiId multi_id)
{
    std::vector<Id> multi = Resolve(multi_id);
    return *boost::range::min_element(multi, [](Id id_1, Id id_2) {
        return MassOf(id_1) < MassOf(id_2);
    });
}

Id Heavyest(MultiId multi_id)
{
    std::vector<Id> multi = Resolve(multi_id);
    return *boost::range::max_element(multi, [](Id id_1, Id id_2) {
        return MassOf(id_1) < MassOf(id_2);
    });
}

}
