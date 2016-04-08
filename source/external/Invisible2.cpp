/****************************************************************************/
/* Solve an event with two decay chains, each containing 2 visible particles*/
/* Translated from Jack Gunion's Fortran code                               */
/* Reference arXiv: 0707.0030                                               */
/* Maintained by Zhenyu Han                                                 */
/****************************************************************************/

/****************************************************************************

                                USAGE

   The program solves for the momenta of the invisible particles in an event
   with two decay chains containing the same particles. Each decay chain
   has 2 visible particles, and an invisible particle at the end of decay chain.

   The visible momenta and the missing transverse momentum are stored in the
   structure:
   struct event22
   {
      double p3[4], p4[4], p5[4], p6[4];
      double pmiss[4];
   };

   The particles are labled such that particles 1,3,5 are in the same decay
   chain, with particle 1 denoting the invisible dark matter particle.
   Particles 3 and 5 are visible paritcles ordered from downstream to upstream
   (i.e., 3 is the one ajacent to the missing particle). Similarly, particles
   2,4,6 are in the other decay chain with particle 2 the other missing
   particle and so forth.

   One also need the masses of the unknown particles (mn < mx < my) to solve for
   the momenta of the missing particles. The syntax is

   void solve22(event22 & evt, double mn, double mx, double my, int & nsols,
                double p1[4][4], double p2[4][4])

   The output is "nsols", the number of real solutions, not exceeding 4, and
   "p1[0..nsols-1][0..3], p2[0..nsols-1][0..3]", the solutions of the 4-momenta
   of the invisible particles.

   see examples/example22.cpp for an example.
********************************************************************************/

#include <cmath>
#include <iostream>

#include "external/Invisible2.hh"

namespace wimpmass
{

namespace
{

double dot(double* p1, double* p2)
{
    return p1[0] * p2[0] - p1[1] * p2[1] - p1[2] * p2[2] - p1[3] * p2[3];
}

}

void cubic(double* a, double* x, int& l)
{
    double u[3];
    const double pi = 3.1415926535897932, third = 1 / 3.;
    double w, p, q, dis;
    if (a[3] != 0.) {
        w   = a[2] / a[3] * third;
        p   = a[1] / a[3] * third - w * w;
        p   = p * p * p;
        q   = - 0.5 * (2.*w * w * w - (a[1] * w - a[0]) / a[3]);
        dis = q * q + p;
        double phi;
        if (dis < 0.) {
            phi = std::acos(std::min(1., std::max(-1., q / std::sqrt(-p))));
            p   = 2.*std::sqrt(std::cbrt(-p));

            for (int i = 1; i < 4; i ++) u[i - 1] = p * std::cos((phi + 2.*i * pi) * third) - w;
            x[0] = std::min(u[0], std::min(u[1], u[2]));
            x[1] = std::max(std::min(u[0], u[1]), std::max(std::min(u[0], u[2]), std::min(u[1], u[2])));
            x[2] = std::max(u[0], std::min(u[1], u[2]));
            l = 3;
        } else {

//only one real solution!
            dis  = std::sqrt(dis);
            x[0] = std::cbrt(q + dis) + std::cbrt(q - dis) - w;
            l    = 1;
        }
    } else if (a[2] != 0.) {
//quadratic problem
        p   = 0.5 * a[1] / a[2];
        dis = p * p - a[0] / a[2];
        if (dis >= 0.) {
            x[0] = - p - std::sqrt(dis);
            x[1] = - p + std::sqrt(dis);
            l    = 2;
        } else l = 0;
    } else if (a[1] != 0.) {

//linear equation
        x[0] = -a[0] / a[1];
        l    = 1;

    } else l = 0;
    for (int i = 0; i < l; i ++) x[i] = x[i] - (a[0] + x[i] * (a[1] + x[i] * (a[2] + x[i] * a[3]))) / (a[1] + x[i] * (2.*a[2] + x[i] * 3.*a[3]));
}

void quartic(double* dd, double* sol, double* soli, int& nsol)
{
    double aa[4], z[3];
    int i;
    nsol = 0;
    double a, b, c, d, e;
    a = dd[4];
    b = dd[3];
    c = dd[2];
    d = dd[1];
    e = dd[0];
    if (std::abs(dd[4]) < 10e-30) {
        std::cout << "ERROR: NOT A QUARTIC EQUATION";
        return;
    };
    double p, q, r;
    p = (-3.*b * b + 8.*a * c) / (8.*a * a);
    q = (b * b * b - 4.*a * b * c + 8.*d * a * a) / (8.*a * a * a);
    r = (-3.*b * b * b * b + 16.*a * b * b * c - 64.*a * a * b * d +
         256.*a * a * a * e) / (256.*a * a * a * a);

//solve cubic resolvent
    aa[3] =  8.;
    aa[2] = -4.*p;
    aa[1] = -8.*r;
    aa[0] =  4.*p * r - q * q;
    int ncube;
    cubic(aa, z, ncube);
    double zsol;
    zsol = -1.e+99;
    for (i = 0; i < ncube; i ++)
        zsol = std::max(zsol, z[i]);
    z[0] = zsol;
    double xk2, xk;
    xk2 = 2. * z[0] - p;
    xk  = std::sqrt(xk2);
//-----------------------------------------------
    double xl2, xl;
    if (std::abs(xk) < 10.e-30) {
        xl2 = z[0] * z[0] - r;
        if (xl2 < 0.) {
            //std::cout<<"Sorry, no solution\n";
            return;
        }
        xl  = std::sqrt(xl2);
    } else {
        xl = q / (2.*xk);
    };

//-----------------------------------------------
    double sqp, sqm;
    sqp = xk2 - 4.*(z[0] + xl);
    sqm = xk2 - 4.*(z[0] - xl);

    for (i = 0; i < 4; i ++) soli[i] = 0.;

    if (sqp >= 0. && sqm >= 0.) {
        sol[0] = 0.5 * (xk + std::sqrt(sqp));
        sol[1] = 0.5 * (xk - std::sqrt(sqp));
        sol[2] = 0.5 * (-xk + std::sqrt(sqm));
        sol[3] = 0.5 * (-xk - std::sqrt(sqm));
        nsol = 4;
    } else if (sqp >= 0. && sqm < 0.) {
        sol[0] =  0.5 * (xk + std::sqrt(sqp));
        sol[1] =  0.5 * (xk - std::sqrt(sqp));
        sol[2] = -0.5 * xk;
        sol[3] = -0.5 * xk;
        soli[2] =  std::sqrt(-0.25 * sqm);
        soli[3] = -std::sqrt(-0.25 * sqm);
        nsol = 2;
    } else if (sqp < 0. && sqm >= 0.) {
        sol[0]  = 0.5 * (-xk + std::sqrt(sqm));
        sol[1]  = 0.5 * (-xk - std::sqrt(sqm));
        sol[2]  =  0.5 * xk;
        sol[3]  =  0.5 * xk;
        soli[2] =  std::sqrt(-0.25 * sqp);
        soli[3] = -std::sqrt(-0.25 * sqp);
        nsol    = 2;
    } else if (sqp < 0. && sqm < 0.) {
        sol[0]  = -0.5 * xk;
        sol[1]  = -0.5 * xk;
        soli[0] =  std::sqrt(-0.25 * sqm);
        soli[1] = -std::sqrt(-0.25 * sqm);
        sol[2]  =  0.5 * xk;
        sol[3]  =  0.5 * xk;
        soli[2] =  std::sqrt(-0.25 * sqp);
        soli[3] = -std::sqrt(-0.25 * sqp);
        nsol    = 0;
    }
    for (i = 0; i < 4; i ++)
        sol[i] = sol[i] - b / (4.*a);
}

void solve22(event22& evt, double mn, double mx, double my, int& nsols, double p1[][4], double p2[][4])
{

    double m3sq, m4sq, m5sq, m6sq, m531sq, m642sq, m31sq, m42sq, m1sq, m2sq;
    int i;
    double* p3, *p4, *p5, *p6, *pmiss;
    p3 = evt.p3;
    p4 = evt.p4;
    p5 = evt.p5;
    p6 = evt.p6;
    pmiss = evt.pmiss;


    m3sq = dot(p3, p3);
    if (m3sq < 0) m3sq = 0;

    m4sq = dot(p4, p4);
    if (m4sq < 0) m4sq = 0;

    m5sq = dot(p5, p5);
    if (m5sq < 0) m5sq = 0;

    m6sq = dot(p6, p6);
    if (m6sq < 0) m6sq = 0;

    m531sq = my * my;
    m642sq = my * my;
    m31sq  = mx * mx;
    m42sq  = mx * mx;
    m1sq   = mn * mn;
    m2sq   = mn * mn;

    double pvisz = 0;

    double pvisx = -pmiss[1];
    double pvisy = -pmiss[2];

    double p3dp5 = dot(p3, p5);
//    double p5dp3 = p3dp5;
    double p4dp6 = dot(p4, p6);
//    double p6dp4 = p4dp6;

    double del2b, del3b, del31, del531;
    del2b  = m3sq + m1sq - m31sq + m42sq - m2sq - m4sq;
    del3b  = m31sq + m5sq - m531sq + m642sq - m42sq - m6sq + 2.*p3dp5 - 2.*p4dp6;
    del31  = m31sq - m1sq - m3sq;
    del531 = m531sq - m31sq - m5sq - 2.0 * p3dp5;

    double e3, p3x, p3y, p3z, e4, p4x, p4y, p4z, e5, p5x, p5y, p5z, e6, p6x, p6y, p6z;
    e3  = evt.p3[0];
    p3x = evt.p3[1];
    p3y = evt.p3[2];
    p3z = evt.p3[3];

    e4  = evt.p4[0];
    p4x = evt.p4[1];
    p4y = evt.p4[2];
    p4z = evt.p4[3];

    e5  = evt.p5[0];
    p5x = evt.p5[1];
    p5y = evt.p5[2];
    p5z = evt.p5[3];

    e6  = evt.p6[0];
    p6x = evt.p6[1];
    p6y = evt.p6[2];
    p6z = evt.p6[3];

//    double detval = -4*p3z*p4z*p5y*p6x + 4*p3y*p4z*p5z*p6x + 4*p3z*p4z*p5x*p6y - 4*p3x*p4z*p5z*p6y - 4*p3z*p4y*p5x*p6z + 4*p3z*p4x*p5y*p6z -4*p3y*p4x*p5z*p6z + 4*p3x*p4y*p5z*p6z;

    double cxe1 = (-((-4 * e5 * p3z * p4z * p6y + 4 * e3 * p4z * p5z * p6y + 4 * e5 * p3z * p4y * p6z - 4 * e3 * p4y * p5z * p6z) / (-4 * p3z * p4z * p5y * p6x + 4 * p3y * p4z * p5z * p6x + 4 * p3z * p4z * p5x * p6y - 4 * p3x * p4z * p5z * p6y - 4 * p3z * p4y * p5x * p6z + 4 * p3z * p4x * p5y * p6z - 4 * p3y * p4x * p5z * p6z + 4 * p3x * p4y * p5z * p6z)));

    double cxe2 = (-((-4 * e6 * p3z * p4z * p5y + 4 * e6 * p3y * p4z * p5z + 4 * e4 * p3z * p5y * p6z - 4 * e4 * p3y * p5z * p6z) / (-4 * p3z * p4z * p5y * p6x + 4 * p3y * p4z * p5z * p6x + 4 * p3z * p4z * p5x * p6y - 4 * p3x * p4z * p5z * p6y - 4 * p3z * p4y * p5x * p6z + 4 * p3z * p4x * p5y * p6z - 4 * p3y * p4x * p5z * p6z + 4 * p3x * p4y * p5z * p6z)));

    double cye1 = (((e5 * p3z - e3 * p5z) * (p4z * p6x - p4x * p6z)) / (p5z * (-(p3y * p4z * p6x) + p3x * p4z * p6y + p3y * p4x * p6z - p3x * p4y * p6z) + p3z * (p4z * p5y * p6x - p4z * p5x * p6y + p4y * p5x * p6z - p4x * p5y * p6z)));

    double cye2 = (-(((p3z * p5x - p3x * p5z) * (e6 * p4z - e4 * p6z)) / (p5z * (p3y * p4z * p6x - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + p3z * (-(p4z * p5y * p6x) + p4z * p5x * p6y - p4y * p5x * p6z + p4x * p5y * p6z))));

    double cze1 = ((e5 * (p3y * p4z * p6x - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + e3 * (-(p4z * p5y * p6x) + p4z * p5x * p6y - p4y * p5x * p6z + p4x * p5y * p6z)) / (p5z * (p3y * p4z * p6x - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + p3z * (-(p4z * p5y * p6x) + p4z * p5x * p6y - p4y * p5x * p6z + p4x * p5y * p6z)));

    double cze2 = (((p3y * p5x - p3x * p5y) * (e6 * p4z - e4 * p6z)) / (p5z * (p3y * p4z * p6x - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + p3z * (-(p4z * p5y * p6x) + p4z * p5x * p6y - p4y * p5x * p6z + p4x * p5y * p6z)));

    double czte1 = ((e5 * (-(p3z * p4y * p6x) + p3y * p4z * p6x + p3z * p4x * p6y - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + e3 * (-(p4z * p5y * p6x) + p4y * p5z * p6x + p4z * p5x * p6y - p4x * p5z * p6y - p4y * p5x * p6z + p4x * p5y * p6z)) / (p5z * (p3y * p4z * p6x - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + p3z * (-(p4z * p5y * p6x) + p4z * p5x * p6y - p4y * p5x * p6z + p4x * p5y * p6z)));

    double czte2 = ((e6 * (-(p3z * p4y * p5x) + p3y * p4z * p5x + p3z * p4x * p5y - p3x * p4z * p5y - p3y * p4x * p5z + p3x * p4y * p5z) + e4 * (-(p3z * p5y * p6x) + p3y * p5z * p6x + p3z * p5x * p6y - p3x * p5z * p6y - p3y * p5x * p6z + p3x * p5y * p6z)) / (p5z * (p3y * p4z * p6x - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + p3z * (-(p4z * p5y * p6x) + p4z * p5x * p6y - p4y * p5x * p6z + p4x * p5y * p6z)));

    double cx = ((del3b * p4z * (p3z * p5y - p3y * p5z) - del31 * p4z * p5z * p6y - del2b * p3z * p5y * p6z - del31 * p3z * p5y * p6z + del2b * p3y * p5z * p6z + del31 * p3y * p5z * p6z + del31 * p4y * p5z * p6z + del531 * (-(p3y * p4z * p5z) + p3z * (p4z * (p5y + p6y) - p4y * p6z)) - 2 * p3z * p4z * p5y * p6x * pvisx + 2 * p3y * p4z * p5z * p6x * pvisx + 2 * p3z * p4x * p5y * p6z * pvisx - 2 * p3y * p4x * p5z * p6z * pvisx - 2 * p3z * p4z * p5y * p6y * pvisy + 2 * p3y * p4z * p5z * p6y * pvisy + 2 * p3z * p4y * p5y * p6z * pvisy - 2 * p3y * p4y * p5z * p6z * pvisy) / (2 * (p5z * (-(p3y * p4z * p6x) + p3x * p4z * p6y + p3y * p4x * p6z - p3x * p4y * p6z) + p3z * (p4z * p5y * p6x - p4z * p5x * p6y + p4y * p5x * p6z - p4x * p5y * p6z))));

    double cy = ((del3b * p4z * (p3z * p5x - p3x * p5z) - del31 * p4z * p5z * p6x - del2b * p3z * p5x * p6z - del31 * p3z * p5x * p6z + del2b * p3x * p5z * p6z + del31 * p3x * p5z * p6z + del31 * p4x * p5z * p6z + del531 * (-(p3x * p4z * p5z) + p3z * (p4z * (p5x + p6x) - p4x * p6z)) - 2 * p3z * p4z * p5x * p6x * pvisx + 2 * p3x * p4z * p5z * p6x * pvisx + 2 * p3z * p4x * p5x * p6z * pvisx - 2 * p3x * p4x * p5z * p6z * pvisx - 2 * p3z * p4z * p5x * p6y * pvisy + 2 * p3x * p4z * p5z * p6y * pvisy + 2 * p3z * p4y * p5x * p6z * pvisy - 2 * p3x * p4y * p5z * p6z * pvisy) / (2.*(p5z * (p3y * p4z * p6x - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + p3z * (-(p4z * p5y * p6x) + p4z * p5x * p6y - p4y * p5x * p6z + p4x * p5y * p6z))));

    double cz = ((del3b * p4z * (p3y * p5x - p3x * p5y) - del31 * p4z * p5y * p6x + del31 * p4z * p5x * p6y - del2b * p3y * p5x * p6z - del31 * p3y * p5x * p6z - del31 * p4y * p5x * p6z + del2b * p3x * p5y * p6z + del31 * p3x * p5y * p6z + del31 * p4x * p5y * p6z + del531 * (p3y * (p4z * (p5x + p6x) - p4x * p6z) - p3x * (p4z * (p5y + p6y) - p4y * p6z)) - 2 * p3y * p4z * p5x * p6x * pvisx + 2 * p3x * p4z * p5y * p6x * pvisx + 2 * p3y * p4x * p5x * p6z * pvisx - 2 * p3x * p4x * p5y * p6z * pvisx - 2 * p3y * p4z * p5x * p6y * pvisy + 2 * p3x * p4z * p5y * p6y * pvisy + 2 * p3y * p4y * p5x * p6z * pvisy - 2 * p3x * p4y * p5y * p6z * pvisy) / (2.*(p5z * (-(p3y * p4z * p6x) + p3x * p4z * p6y + p3y * p4x * p6z - p3x * p4y * p6z) + p3z * (p4z * p5y * p6x - p4z * p5x * p6y + p4y * p5x * p6z - p4x * p5y * p6z))));

    double czt = (del3b * (p3z * p4y * p5x - p3y * p4z * p5x - p3z * p4x * p5y + p3x * p4z * p5y + p3y * p4x * p5z - p3x * p4y * p5z) + del2b * p3z * p5y * p6x + del31 * p3z * p5y * p6x + del31 * p4z * p5y * p6x - del2b * p3y * p5z * p6x - del31 * p3y * p5z * p6x - del31 * p4y * p5z * p6x - del2b * p3z * p5x * p6y - del31 * p3z * p5x * p6y - del31 * p4z * p5x * p6y + del2b * p3x * p5z * p6y + del31 * p3x * p5z * p6y + del31 * p4x * p5z * p6y + del2b * p3y * p5x * p6z + del31 * p3y * p5x * p6z + del31 * p4y * p5x * p6z - del2b * p3x * p5y * p6z - del31 * p3x * p5y * p6z - del31 * p4x * p5y * p6z + del531 * (p3z * (p4y * (p5x + p6x) - p4x * (p5y + p6y)) + p3y * (-(p4z * (p5x + p6x)) + p4x * (p5z + p6z)) + p3x * (p4z * (p5y + p6y) - p4y * (p5z + p6z))) - 2 * p3z * p4y * p5x * p6x * pvisx + 2 * p3y * p4z * p5x * p6x * pvisx - 2 * p3x * p4z * p5y * p6x * pvisx + 2 * p3x * p4y * p5z * p6x * pvisx + 2 * p3z * p4x * p5x * p6y * pvisx - 2 * p3x * p4x * p5z * p6y * pvisx - 2 * p3y * p4x * p5x * p6z * pvisx + 2 * p3x * p4x * p5y * p6z * pvisx - 2 * p3z * p4y * p5y * p6x * pvisy + 2 * p3y * p4y * p5z * p6x * pvisy + 2 * p3y * p4z * p5x * p6y * pvisy + 2 * p3z * p4x * p5y * p6y * pvisy - 2 * p3x * p4z * p5y * p6y * pvisy - 2 * p3y * p4x * p5z * p6y * pvisy - 2 * p3y * p4y * p5x * p6z * pvisy + 2 * p3x * p4y * p5y * p6z * pvisy - 2 * p3z * p4z * p5y * p6x * pvisz + 2 * p3y * p4z * p5z * p6x * pvisz + 2 * p3z * p4z * p5x * p6y * pvisz - 2 * p3x * p4z * p5z * p6y * pvisz - 2 * p3z * p4y * p5x * p6z * pvisz + 2 * p3z * p4x * p5y * p6z * pvisz - 2 * p3y * p4x * p5z * p6z * pvisz + 2 * p3x * p4y * p5z * p6z * pvisz) / (2 * (p5z * (p3y * p4z * p6x - p3x * p4z * p6y - p3y * p4x * p6z + p3x * p4y * p6z) + p3z * (-(p4z * p5y * p6x) + p4z * p5x * p6y - p4y * p5x * p6z + p4x * p5y * p6z)));

    double a11 = -1 + cxe1 * cxe1 + cye1 * cye1 + cze1 * cze1;

    double b11 = cxe1 * cxe1 + cye1 * cye1 + cze1 * cze1 - 2 * cze1 * czte1 + czte1 * czte1;

    double a22 = cxe2 * cxe2 + cye2 * cye2 + cze2 * cze2;

    double b22 = -1 + cxe2 * cxe2 + cye2 * cye2 + cze2 * cze2 - 2 * cze2 * czte2 + czte2 * czte2;

    double a12 = 2 * cxe1 * cxe2 + 2 * cye1 * cye2 + 2 * cze1 * cze2;

    double b12 = 2 * cxe1 * cxe2 + 2 * cye1 * cye2 + 2 * cze1 * cze2 - 2 * cze2 * czte1 - 2 * cze1 * czte2 + 2 * czte1 * czte2;

    double a1  = 2 * cx * cxe1 + 2 * cy * cye1 + 2 * cz * cze1;

    double b1  = 2 * cx * cxe1 + 2 * cy * cye1 + 2 * cz * cze1 - 2 * cze1 * czt - 2 * cz * czte1 + 2 * czt * czte1 + 2 * cxe1 * pvisx + 2 * cye1 * pvisy + 2 * cze1 * pvisz - 2 * czte1 * pvisz;

    double a2  = 2 * cx * cxe2 + 2 * cy * cye2 + 2 * cz * cze2;

    double b2  = 2 * cx * cxe2 + 2 * cy * cye2 + 2 * cz * cze2 - 2 * cze2 * czt - 2 * cz * czte2 + 2 * czt * czte2 + 2 * cxe2 * pvisx + 2 * cye2 * pvisy + 2 * cze2 * pvisz - 2 * czte2 * pvisz;

    double a   = cx * cx + cy * cy + cz * cz + m1sq;

    double b   = cx * cx + cy * cy + cz * cz - 2 * cz * czt + czt * czt + m2sq + 2 * cx * pvisx + pvisx * pvisx + 2 * cy * pvisy + pvisy * pvisy + 2 * cz * pvisz - 2 * czt * pvisz + pvisz * pvisz;

    double af = a11 * a22 * a22 * b11 * b11 - a11 * a12 * a22 * b11 * b12 + a11 * a11 * a22 * b12 * b12 + a11 * a12 * a12 * b11 * b22 - 2 * a11 * a11 * a22 * b11 * b22 - a11 * a11 * a12 * b12 * b22 + a11 * a11 * a11 * b22 * b22;

    double bf = -(a11 * a12 * a22 * b1 * b11) + 2 * a11 * a2 * a22 * b11 * b11 + 2 * a11 * a11 * a22 * b1 * b12 - a11 * a12 * a2 * b11 * b12 - a1 * a11 * a22 * b11 * b12 + a11 * a11 * a2 * b12 * b12 + a11 * a12 * a12 * b11 * b2 - 2 * a11 * a11 * a22 * b11 * b2 - a11 * a11 * a12 * b12 * b2 - a11 * a11 * a12 * b1 * b22 + 2 * a1 * a11 * a12 * b11 * b22 - 2 * a11 * a11 * a2 * b11 * b22 - a1 * a11 * a11 * b12 * b22 + 2 * a11 * a11 * a11 * b2 * b22;

    double cf = a11 * a11 * a22 * b1 * b1 + a11 * a12 * a12 * b * b11 - 2 * a11 * a11 * a22 * b * b11 - a11 * a12 * a2 * b1 * b11 - a1 * a11 * a22 * b1 * b11 + a11 * a2 * a2 * b11 * b11 + 2 * a * a11 * a22 * b11 * b11 - a11 * a11 * a12 * b * b12 + 2 * a11 * a11 * a2 * b1 * b12 - a * a11 * a12 * b11 * b12 - a1 * a11 * a2 * b11 * b12 + a * a11 * a11 * b12 * b12 - a11 * a11 * a12 * b1 * b2 + 2 * a1 * a11 * a12 * b11 * b2 - 2 * a11 * a11 * a2 * b11 * b2 - a1 * a11 * a11 * b12 * b2 + a11 * a11 * a11 * b2 * b2 + 2 * a11 * a11 * a11 * b * b22 - a1 * a11 * a11 * b1 * b22 + a1 * a1 * a11 * b11 * b22 - 2 * a * a11 * a11 * b11 * b22;

    double df = -(a11 * a11 * a12 * b * b1) + a11 * a11 * a2 * b1 * b1 + 2 * a1 * a11 * a12 * b * b11 - 2 * a11 * a11 * a2 * b * b11 - a * a11 * a12 * b1 * b11 - a1 * a11 * a2 * b1 * b11 + 2 * a * a11 * a2 * b11 * b11 - a1 * a11 * a11 * b * b12 + 2 * a * a11 * a11 * b1 * b12 - a * a1 * a11 * b11 * b12 + 2 * a11 * a11 * a11 * b * b2 - a1 * a11 * a11 * b1 * b2 + a1 * a1 * a11 * b11 * b2 - 2 * a * a11 * a11 * b11 * b2;

    double ef = a11 * (a11 * b - a * b11) * (a11 * b - a * b11) + a1 * (a11 * b - a * b11) * (-(a11 * b1) + a1 * b11) + a * (-(a11 * b1) + a1 * b11) * (-(a11 * b1) + a1 * b11);

    double dd[5], sol[4], soli[4];
    dd[0] = ef;
    dd[1] = df;
    dd[2] = cf;
    dd[3] = bf;
    dd[4] = af;

    int nsolreal;
//     int nerr;
    double e1, e2;
    //double detjacf;

    nsols = 0;

    quartic(dd, sol, soli, nsolreal);

    if (nsolreal == 0) {
//       nerr = 1;
        //    std::cout<< "no real solutions, nerr=1"<<endl;
        return;
    };

    for (i = 0; i < nsolreal; i++) {
        e2 = sol[i];
// substitute e2 solution into general e1 solution in terms of e2
        e1 =
            (a11 * b - a * b11 - a2 * b11 * e2 + a11 * b2 * e2 -
             a22 * b11 * e2 * e2 + a11 * b22 * e2 * e2) /
            (-(a11 * b1) + a1 * b11 + a12 * b11 * e2 - a11 * b12 * e2);

// now evaluate jacobians and momenta
        /*      detjacf= -(a2*b1) + a1*b2 - a12*b1*e1 - 2*a2*b11*e1 + a1*b12*e1 +
              2*a11*b2*e1 - 2*a12*b11*e1*e1 + 2*a11*b12*e1*e1 -
              2*a22*b1*e2 - a2*b12*e2 + a12*b2*e2 + 2*a1*b22*e2 -
              4*a22*b11*e1*e2 + 4*a11*b22*e1*e2 - 2*a22*b12*e2*e2 +
              2*a12*b22*e2*e2;

              double jac=std::abs(detjacf*detval); */

        if (e1 <= 0. || e2 <= 0.) {
//             nerr = 3;
            //std::cout<< "e1 or e2 < 0"<<e1<<e2<<endl;
            continue;
        };

        //if(e1>2000.||e2>2000.) continue;

        double p1x   = cxe1 * e1 + cxe2 * e2 + cx;
        double p1y   = cye1 * e1 + cye2 * e2 + cy;
        double p1z   = cze1 * e1 + cze2 * e2 + cz;
        double ptotz = czte1 * e1 + czte2 * e2 + czt;
//       double etot  = e1 + e2 + e3 + e4 + e5 + e6;

        /*pg1[nsolutions][0]=(etot+ptotz)/2.;
        pg2[nsolutions][0]=(etot-ptotz)/2.;
        pg1[nsolutions][1]=0.;
        pg2[nsolutions][1]=0.;
        pg1[nsolutions][2]=0.;
        pg2[nsolutions][2]=0.;
        pg1[nsolutions][3]=pg1[nsolutions][0];
        pg2[nsolutions][3]=-pg2[nsolutions][0];*/

        double p2x = -pvisx - p1x;
        double p2y = -pvisy - p1y;
        double p2z = ptotz - p1z - pvisz;

        p1[nsols][0] = e1;
        p1[nsols][1] = p1x;
        p1[nsols][2] = p1y;
        p1[nsols][3] = p1z;

        p2[nsols][0] = e2;
        p2[nsols][1] = p2x;
        p2[nsols][2] = p2y;
        p2[nsols][3] = p2z;

        nsols++;

    }
    return;
}

}
