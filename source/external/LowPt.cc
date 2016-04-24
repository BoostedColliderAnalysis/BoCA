//Example for a low_pt working point
#include "boca/external/LowPt.hh"
#include "boca/external/FWM.hh"

namespace hep
{

LowPt::LowPt() {};

bool LowPt::is_tagged(TopTagger2 const& htt)
{
    if (htt.is_tagged()) return true;
    if (!htt.is_masscut_passed()) return false;

    auto pt = htt.t().pt();
    auto m_rec = htt.t().m();
    auto m_ratio = (htt.W().m() / htt.t().m()) / (80.4 / 172.3);
    auto m12 = (htt.j1() + htt.j2()).m();
    auto m13 = (htt.j1() + htt.j3()).m();
    auto m23 = (htt.j2() + htt.j3()).m();
    auto atan_13_12 = atan(m12 / m13);
    auto m23_m123 = m23 / m_rec;

    auto FWM_W1W2_U1 = FWM(htt, 11).U(1);
    auto FWM_pW1W2_U1 = FWM(htt, 1011).U(2);
    auto FWM_pbW1W2_U1 = FWM(htt, 1111).U(2);
    auto FWM_pbW2_U1 = FWM(htt, 1101).U(1);

    if (pt < 150. || pt > 200.) return false;
    if (m_rec < 108. || m_rec > 282.) return false;
    if (m_ratio < 0.717 || m_ratio > 1.556) return false;
    if (atan_13_12 < 0.441 || atan_13_12 > 0.889) return false;
    if (m23_m123 < 0.412 || m23_m123 > 0.758) return false;
    if (FWM_W1W2_U1 < 0.048 || FWM_W1W2_U1 > 0.373) return false;
    if (FWM_pW1W2_U1 < 0.019 || FWM_pW1W2_U1 > 0.524) return false;
    if (FWM_pbW1W2_U1 < 0.044 || FWM_pbW1W2_U1 > 0.276) return false;
    if (FWM_pbW2_U1 < 0.145 || FWM_pbW2_U1 > 0.445) return false;

    return true;
};

}
