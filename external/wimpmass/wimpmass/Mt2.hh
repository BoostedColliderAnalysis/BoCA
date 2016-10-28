#pragma once

#include "boca/physics/Units.hh"
#include "boca/fastjet/Jet.hh"

/**
* \ingroup Wimpmass
* @brief <a href="http://particle.physics.ucdavis.edu/hefti/projects/doku.php?id=wimpmass">Wimpmass</a> contains a few packages useful for determining the mass of the dark matter particle at the LHC.
*/
namespace wimpmass
{

class Mt2
{
public:

    Mt2(boca::Mass const& mass = boca::massless);
    double Get(boca::LorentzVector<boca::Momentum> const& jet_1, boca::LorentzVector<boca::Momentum> const& jet_2, boca::LorentzVector<boca::Momentum> const& missing_et);

protected:

    void SetMomenta ( double* pa0, double* pb0, double* pmiss0 );
    void SetMass ( double mn );
    double GetMt2();

private:

    void GetMomentum(boca::LorentzVector<boca::Momentum> const& jet_1,  double *momentum);
    double Bisect();
    double Massless();
    void Print();

    int nevt;
    bool solved = false;
    bool momenta_set = false;
    double mt2_b = 0.;
    double scale = 1.;

    int nsols ( double Dsq );
    int nsols_massless ( double Dsq );
    int signchange_n ( double t1, double t2, double t3, double t4, double t5 );
    int signchange_p ( double t1, double t2, double t3, double t4, double t5 );
    int scan_high ( double& Deltasq_high );
    int find_high ( double& Deltasq_high );
//data members
    double pax, pay, ma, Ea;
    double pmissx, pmissy;
    double pbx, pby, mb, Eb;
    double mn, mn_unscale;

//auxiliary definitions
    double masq, Easq;
    double mbsq, Ebsq;
    double pmissxsq, pmissysq;
    double mnsq;

//auxiliary coefficients
    double a1, b1, c1, a2, b2, c2, d1, e1, f1, d2, e2, f2;
    double d11, e11, f12, f10, d21, d20, e21, e20, f22, f21, f20;

    double precision;
};

}
