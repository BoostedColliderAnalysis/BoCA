#pragma once

namespace mt2
{

class Mt2
{
public:

    Mt2();
    void mt2_bisect();
    void mt2_massless();
    void set_momenta ( double* pa0, double* pb0, double* pmiss0 );
    void set_mn ( double mn );
    double get_mt2();
    void print();
    int nevt;

private:

    bool solved;
    bool momenta_set;
    double mt2_b;

    int nsols ( double Dsq );
    int nsols_massless ( double Dsq );
    inline int signchange_n ( long double t1, long double t2, long double t3, long double t4, long double t5 );
    inline int signchange_p ( long double t1, long double t2, long double t3, long double t4, long double t5 );
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

    double scale;
    double precision;
};

}

// #include "mt2_bisect.h"
// #include <iostream>
// using namespace std;
// int main()
// {
// cout << " Example Event:" << endl;
// cout << endl;
//
// //pa, pb = {mass, px, py}
// //pmiss = {NULL, pxmiss, pymiss}
// //mn = invisible particle mass
// double pa[3] = { 0.106, 39.0, 12.0 };
// double pb[3] = { 0.106, 119.0, -33.0 };
// double pmiss[3] = { 0, -29.9, 35.9 };
// double mn = 50.;
//
// mt2::Mt2 mt2_event;
//
// mt2_event.set_momenta(pa,pb,pmiss);
// mt2_event.set_mn(mn);
// mt2_event.print();
//
// cout << endl << " mt2 = " << mt2_event.get_mt2() << endl;
//
// return 1;
//
// }

