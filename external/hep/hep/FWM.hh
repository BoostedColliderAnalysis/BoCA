#pragma once

#include "hep/TopTagger2.hh"

namespace hep
{

class FWM
{
public:
    FWM();
    FWM(const std::vector< fastjet::PseudoJet >& jets);
    FWM(hep::TopTagger2 const& htt, int selection);

    double U(unsigned order);
    double Pt(unsigned order);
    double Pt(unsigned order, const fastjet::PseudoJet& ref_pj);

private:
    double cos_Omega(fastjet::PseudoJet const& jet1, fastjet::PseudoJet const& jet2);
    double ATan2(double x, double y);
    double Theta(const fastjet::PseudoJet& j);
    double legendre(int l, double x);

    std::vector<fastjet::PseudoJet> _jets;
};

}
