#include "external/FWM.hh"
#include "fastjet/tools/Boost.hh"

namespace hep
{

double perp(fastjet::PseudoJet v_pj, fastjet::PseudoJet ref_pj)
{
    double pt = 0.;
    std::valarray<double> v = v_pj.four_mom();
    std::valarray<double> ref = ref_pj.four_mom();
    ref[3] = 0.;
    double mag2 = ref[0] * ref[0] + ref[1] * ref[1] + ref[2] * ref[2];
    double v_ref =  v[0] * ref[0] + v[1] * ref[1] + v[2] * ref[2];
    std::valarray<double> v_perp = v - (v_ref / mag2) * ref;
    pt = sqrt(v_perp[0] * v_perp[0] + v_perp[1] * v_perp[1] + v_perp[2] * v_perp[2]);
    return pt;
}

FWM::FWM() {};

FWM::FWM(std::vector<fastjet::PseudoJet> jets) : _jets(jets) {}

FWM::FWM(TopTagger2 htt, int selection)
{
    fastjet::PseudoJet top = htt.t();
    fastjet::Unboost rf(top);
    fastjet::PseudoJet a(-top.px(), -top.py(), -top.pz(), 0.);

    std::vector<fastjet::PseudoJet> jets;
    if (selection / 1000 == 1)  {
        jets.push_back(a);
    }
    if ((selection % 1000) / 100 == 1) {
        jets.push_back(rf(htt.b()));
    }
    if ((selection % 100) / 10 == 1) {
        jets.push_back(rf(htt.W1()));
    }
    if ((selection % 10) == 1) {
        jets.push_back(rf(htt.W2()));
    }
    _jets = jets;
}

inline double FWM::ATan2(double y, double x)
{
    if (x != 0) return  atan2(y, x);
    if (y == 0) return  0;
    if (y >  0) return  M_PI / 2;
    else        return -M_PI / 2;
}

double FWM::Theta(fastjet::PseudoJet j)
{
    return j.px() == 0.0 && j.py() == 0.0 && j.pz() == 0.0 ? 0.0 : ATan2(j.perp(), j.pz());
}

double FWM::cos_Omega(fastjet::PseudoJet jet1, fastjet::PseudoJet jet2)
{
    double cos_omega = cos(Theta(jet1)) * cos(Theta(jet2))
                       + sin(Theta(jet1)) * sin(Theta(jet2)) * cos(jet1.phi_std() - jet2.phi_std());
    return cos_omega;
}

double FWM::U(unsigned order)
{
    double H = 0.;
    double norm = (_jets.size() * _jets.size());
    for (unsigned ii = 0; ii < _jets.size(); ii++) {
        for (unsigned jj = 0; jj < _jets.size(); jj++) {
            double W = 1.;
            double cos_O;
            if (ii == jj) {
                cos_O = 1.0;
            } else {
                cos_O = cos_Omega(_jets[ii], _jets[jj]);
            }
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

double FWM::Pt(unsigned order, fastjet::PseudoJet ref_pj)
{
    double H = 0.;
    double norm = 0.;
    for (unsigned ii = 0; ii < _jets.size(); ii++) {
        norm += perp(_jets[ii], ref_pj) * perp(_jets[ii], ref_pj);
        for (unsigned jj = 0; jj < _jets.size(); jj++) {
            double W = perp(_jets[ii], ref_pj) * perp(_jets[jj], ref_pj);
            double cos_O;
            if (ii == jj) {
                cos_O = 1.0;
            } else {
                cos_O = cos_Omega(_jets[ii], _jets[jj]);
            }
            H += W * legendre(order, cos_O);
        }
    }
    if (norm > 0.) H /= norm;
    return H;
}

}
