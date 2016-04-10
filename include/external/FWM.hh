#pragma once

#include "TopTagger2.hh"

namespace hep
{

class FWM
{
public:
    FWM();
    FWM(std::vector<fastjet::PseudoJet> jets);
    FWM(TopTagger2 htt, int selection);

    double U(unsigned order);
    double Pt(unsigned order);
    double Pt(unsigned order, fastjet::PseudoJet ref_pj);

private:
    double cos_Omega(fastjet::PseudoJet jet1, fastjet::PseudoJet jet2);
    double ATan2(double x, double y);
    double Theta(fastjet::PseudoJet j);
    double legendre(int l, double x);;

    std::vector<fastjet::PseudoJet> _jets;
};

}
