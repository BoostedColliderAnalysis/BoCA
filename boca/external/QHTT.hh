#pragma once

#include "boca/external/TopTagger2.hh"

namespace hep
{

class QHTT
{
public:
    QHTT();
    void set_iterations(int niter);
    void set_q_zcut(double zcut);
    void set_q_dcut_fctr(double dcut_fctr);
    void set_q_exp(double a, double b);
    void set_q_rigidity(double rigidity);
    void set_q_truncation_fctr(double truncation_fctr);

    void run(hep::TopTagger2 const& htt);
    TopTagger2 leading();
    TopTagger2 subleading();
    double weight_leading();
    double weight_subleading();
    double eps_q();
    double m_mean();
    double m2_mean();

private:
    int _niter;
    double _q_zcut, _q_dcut_fctr, _q_exp_min, _q_exp_max, _q_rigidity, _q_truncation_fctr;
    int _qtags;
    double _weight_q1, _weight_q2;
    TopTagger2 _htt_q, _htt_q1, _htt_q2;
    double _m_sum, _m2_sum;
    double _eps_q;
};

}
