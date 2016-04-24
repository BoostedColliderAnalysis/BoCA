#include "Math/SpecFuncMathMore.h"

#include "fastjet/tools/Boost.hh"

#include "boca/external/FWM.hh"

namespace hep
{

FWM::FWM() {};

FWM::FWM(std::vector<fastjet::PseudoJet> const& jets) : _jets(jets) {}

FWM::FWM(TopTagger2 const& htt, int selection)
{
    auto top = htt.t();
    fastjet::Unboost rf(top);
    fastjet::PseudoJet a(-top.px(), -top.py(), -top.pz(), 0.);
    std::vector<fastjet::PseudoJet> jets;
    if (selection / 1000 == 1) jets.push_back(a);
    if ((selection % 1000) / 100 == 1) jets.push_back(rf(htt.b()));
    if ((selection % 100) / 10 == 1) jets.push_back(rf(htt.W1()));
    if ((selection % 10) == 1) jets.push_back(rf(htt.W2()));
    _jets = jets;
}

double perp(fastjet::PseudoJet const& v_pj, fastjet::PseudoJet const& ref_pj)
{
    auto v = v_pj.four_mom();
    auto ref = ref_pj.four_mom();
    ref[3] = 0.;
    auto mag2 = ref[0] * ref[0] + ref[1] * ref[1] + ref[2] * ref[2];
    auto v_ref = v[0] * ref[0] + v[1] * ref[1] + v[2] * ref[2];
    auto v_perp = v - (v_ref / mag2) * ref;
    return sqrt(v_perp[0] * v_perp[0] + v_perp[1] * v_perp[1] + v_perp[2] * v_perp[2]);
}

double FWM::ATan2(double y, double x)
{
    if (x != 0) return std::atan2(y, x);
    if (y == 0) return 0;
    if (y > 0) return M_PI / 2;
    else return -M_PI / 2;
}

double FWM::Theta(fastjet::PseudoJet const& j)
{
    return j.px() == 0.0 && j.py() == 0.0 && j.pz() == 0.0 ? 0.0 : ATan2(j.perp(), j.pz());
}

double FWM::cos_Omega(fastjet::PseudoJet const& jet1, fastjet::PseudoJet const& jet2)
{
    return std::cos(Theta(jet1)) * std::cos(Theta(jet2)) + std::sin(Theta(jet1)) * std::sin(Theta(jet2)) * std::cos(jet1.phi_std() - jet2.phi_std());
}

double FWM::U(unsigned order)
{
    auto H = 0.;
    double norm = (_jets.size() * _jets.size());
    for (unsigned ii = 0; ii < _jets.size(); ii++) {
        for (unsigned jj = 0; jj < _jets.size(); jj++) {
            auto W = 1.;
            double cos_O;
            if (ii == jj) cos_O = 1.0;
            else cos_O = cos_Omega(_jets[ii], _jets[jj]);
            H += W * legendre(order, cos_O);
        }
    }
    if (norm > 0.) H /= norm;
    return H;
}

double FWM::Pt(unsigned order)
{
    fastjet::PseudoJet zaxis(0., 0., 1., 0.);
    return FWM::Pt(order, zaxis);
}

double FWM::Pt(unsigned order, fastjet::PseudoJet const& ref_pj)
{
    auto H = 0.;
    auto norm = 0.;
    for (unsigned ii = 0; ii < _jets.size(); ii++) {
        norm += perp(_jets[ii], ref_pj) * perp(_jets[ii], ref_pj);
        for (unsigned jj = 0; jj < _jets.size(); jj++) {
            auto W = perp(_jets[ii], ref_pj) * perp(_jets[jj], ref_pj);
            auto cos_O = ii == jj ? 1. : cos_Omega(_jets[ii], _jets[jj]);
            H += W * legendre(order, cos_O);
        }
    }
    if (norm > 0.) H /= norm;
    return H;
}

double FWM::legendre(int l, double x)
{
    return ROOT::Math::legendre(l, x);
//     return gsl_sf_legendre_Pl(l, x);
}

}
