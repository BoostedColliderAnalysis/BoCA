# include "Global.hh"

namespace analysis
{

int LargeNumber()
{
    return 999999999;
}

float Distance(const float rapidity_1, const float phi_1, const float rapidity_2, const float phi_2)
{
    return std::sqrt(std::pow((rapidity_2 - rapidity_1), 2) + std::pow(DeltaPhi(phi_2, phi_1), 2));
}

float Length(const float rapidity, const float phi)
{
    return std::sqrt(std::pow(rapidity, 2) + std::pow(phi, 2));
}

float DeltaPhi(const float phi_1, const float phi_2)
{
    float delta_phi = phi_1 - phi_2;
    while (std::abs(delta_phi) > M_PI) {
        if (delta_phi < - M_PI) {
            delta_phi += 2 * M_PI;
        } else if (delta_phi > M_PI) {
            delta_phi -= 2 * M_PI;
        } else {
//       Print(Severity::Error, "Delta Phi", delta_phi);
            break;
        }
    }
    return delta_phi;
}


std::string Name(const int id)
{
    std::string sign = "";
    if (id < 0) sign = "-";
    return sign + Name(Id(id));
}

std::string Name(const Id id)
{
    switch (id) {
        //     case Id::Empty: return "Empty";
    case Id::Down:
        return "d";
    case Id::Up:
        return "u";
    case Id::Strange:
        return "s";
    case Id::Charm:
        return "c";
    case Id::Bottom:
        return "b";
    case Id::Top:
        return "t";
    case Id::TopPartner:
        return "T";
    case Id::Electron:
        return "e";
    case Id::ElectronNeutrino:
        return "nue";
    case Id::Muon:
        return "mu";
    case Id::MuonNeutrino:
        return "numu";
    case Id::Tau:
        return "tau";
    case Id::TauNeutrino:
        return "nutau";
    case Id::Gluon:
        return "g";
    case Id::Photon:
        return "gamma";
    case Id::Z:
        return "Z";
    case Id::W:
        return "W";
    case Id::Higgs:
        return "h";
    case Id::HeavyHiggs:
        return "H";
    case Id::ChargedHiggs:
        return "H+";
    case Id::Isr:
        return "ISR";
    case Id::Marker:
        return "TEMP";
    case Id::Cluster:
        return "Cluster";
    case Id::String:
        return "String";
    case Id::MixedJet:
        return "MixJet";
    case Id::Pi0Meson:
        return "pi0";
    case Id::Rho0Meson:
        return "rho0";
    case Id::K0LMeson:
        return "K0l";
    case Id::Pion:
        return "pi";
    case Id::RhoMeson:
        return "rho";
    case Id::RapMeson:
        return "eta";
    case Id::OmegaMeson:
        return "omega";
    case Id::K0SMeson:
        return "K0s";
    case Id::KMeson0:
        return "K0";
    case Id::KMeson0S:
        return "K0*";
    case Id::KMeson:
        return "K";
    case Id::KMesonS:
        return "K*";
    case Id::RapPMeson:
        return "etaP";
    case Id::DMeson:
        return "D";
    case Id::DMesonS:
        return "D*";
    case Id::DMesonS2:
        return "D*2";
    case Id::DMeson0:
        return "D0";
    case Id::DMesonS0:
        return "D*0";
    case Id::RapCMeson:
        return "etac";
    case Id::BMeson0:
        return "B0";
    case Id::BMeson0S:
        return "B0*";
    case Id::BMeson:
        return "B";
    case Id::BMesonS:
        return "B*";
    case Id::BMesonS0:
        return "B*0";
    case Id::BMesonSS0:
        return "Bs*0";
    case Id::DownDown1:
        return "dd1";
    case Id::UpDown0:
        return "ud0";
    case Id::UpDown1:
        return "ud1";
    case Id::DeltaBaryon:
        return "Delta";
    case Id::Neutron:
        return "n";
    case Id::UpUp1:
        return "uu1";
    case Id::Proton:
        return "p";
    case Id::DeltaBaryon2:
        return "Delta2";
    case Id::CpvHiggs:
        return "h";
    default:
        return std::to_string(int(id));
    }
}

float Mass(const Id id)
{
    switch (id) {
    case Id::Strange:
        return 0.095;
    case Id::Charm:
        return 1.28;
    case Id::Bottom:
        return 4.18;
    case Id::Top:
        return 173.5;
    case Id::Electron:
        return 0.000511;
    case Id::ElectronNeutrino:
        return 0;
    case Id::Muon:
        return 0.1134;
    case Id::MuonNeutrino:
        return 0;
    case Id::Tau:
        return 1.776;
    case Id::TauNeutrino:
        return 0;
    case Id::Photon:
        return 0;
    case Id::Z:
        return 91.188;
    case Id::W:
        return 80.39;
    case Id::Higgs:
        return 125;
    case Id::Pi0Meson:
        return 0.13498;
    case Id::Pion:
        return 0.13957;
    case Id::RhoMeson:
        return 0.77549;
    case Id::RapMeson:
        return 0.54785;
    case Id::OmegaMeson:
        return 0.78265;
    case Id::Neutron:
        return 1.00866;
    case Id::Proton:
        return 0.93827;
    case Id::CpvHiggs:
        return Mass(Id::Higgs);
    default:
        return 0;
    }
}
std::string Name(const Tag tag)
{
    switch (tag) {
    case  Tag::Signal:
        return "Signal";
    case  Tag::Background:
        return "Background";
    }
}

}
