// rpoly.cpp - Program for calculating the roots of a polynomial of real coefficients.
// Written in Visual C++ 2005 Express Edition
// 14 July 2007
//
// The sub-routines listed below are translations of the FORTRAN routines included in RPOLY.FOR,
// posted off the NETLIB site as TOMS/493:
//
// http://www.netlib.org/toms/493
//
// TOMS/493 is based on the Jenkins-Traub algorithm.
//
//
// Following is a list of the major changes made in the course of translating the TOMS/493 routines
// to the C++ versions posted below:
// 1) All global variables have been eliminated.
// 2) The "FAIL" parameter passed into RPOLY.FOR has been eliminated.
// 3) RPOLY.FOR solves polynomials of degree up to 100, but does not explicitly state this limit.
//     rpoly explicitly states this limit; uses the macro name MAXDEGREE to specify this limit;
//     and does a check to ensure that the user input variable Degree is not greater than MAXDEGREE
//     (if it is, an error message is output and rpoly terminates). If a user wishes to compute
//     roots of polynomials of degree greater than MAXDEGREE, using a macro name like MAXDEGREE provides
//     the simplest way of offering this capability.
// 4) All "GO TO" statements have been eliminated.
//
// A small main program is included also, to provide an example of how to use rpoly. In this
// example, data is input from a file to eliminate the need for a user to type data in via
// the console.

#include <iostream>
#include <fstream>
#include <cctype>
#include <cfloat>

#include "external/PolynomialRoots.hh"
#include "generic/Types.hh"

namespace polynomialroots
{

std::vector<std::complex<double>> PolynomialRoots::rpoly(std::vector<double> coefficients)
{
    std::vector<std::complex<double>> zeros(coefficients.size());

//     int i, j, jj, l, N, NM1, NN, NZ, zerok;

//     double K[MDP1], p[MDP1], pt[MDP1], qp[MDP1], temp[MDP1];
//     double bnd, df, dx, factor, ff, moduli_max, moduli_min, sc, x, xm;
//     double aa, bb, cc, lzi, lzr, sr, szi, szr, t, u, xx, xxx, yy;

    const double RADFAC = 3.14159265358979323846 / 180; // Degrees-to-radians conversion factor = pi/180
    const double lb2 = std::log(2.0); // Dummy variable to avoid re-calculating this value in loop below
    const double lo = DBL_MIN / DBL_EPSILON;
    const double cosr = cos(94.0 * RADFAC); // = -0.069756474
    const double sinr = sin(94.0 * RADFAC); // = 0.99756405

    int Degree = coefficients.size();

    if (Degree > MAXDEGREE) {
        std::cout << "\nThe entered Degree is greater than MAXDEGREE. Exiting rpoly. No further action taken.\n";
        return zeros;
    }

//Do a quick check to see if leading coefficient is 0
if (coefficients.at(0) == 0) {
    std::cout << "\nThe leading coefficient is zero. No further action taken. Program terminated.\n";
    return zeros;
}
        double xx = std::sqrt(0.5); // = 0.70710678
        double yy = -xx;

// Remove zeros at the origin, if any
        int j = 0;
        int N = Degree;
        while (coefficients[N] == 0) {
            zeros[j] = 0;
            N--;
            j++;
        }

        int NN = N + 1;

// Make a copy of the coefficients
//         for (i = 0; i < NN; i++) {
//             p[i] = coefficients[i];
//         }
            auto cs = coefficients;

        while (N >= 1) {
            // Start the algorithm for one zero
            if (N <= 2) {
                // Calculate the final zero or pair of zeros
              if (N < 2) zeros[(Degree) - 1] = -cs[1] / cs[0];
                else {
                  auto roots = Quadratic(cs[0], cs[1], cs[2]);
                    zeros[(Degree) - 2] = roots.first;
                    zeros[(Degree) - 1] = roots.second;
                }
                break;
            }

            // Find the largest and smallest moduli of the coefficients
            double moduli_max = 0.0;
            double moduli_min = DBL_MAX;
            for (auto const& c : cs) {
              double x = std::abs(c);
                if (x > moduli_max) moduli_max = x;
                if (x != 0 && x < moduli_min) moduli_min = x;
            }

            // Scale if there are large or very small coefficients
            // Computes a scale factor to multiply the coefficients of the polynomial. The scaling
            // is done to avoid overflow and to avoid undetected underflow interfering with the
            // convergence criterion.
            // The factor is a power of the base.

            double sc = lo / moduli_min;
            if ((sc <= 1.0 && moduli_max >= 10) || (sc > 1.0 && DBL_MAX / sc >= moduli_max)) {
                sc = (sc == 0 ? DBL_MIN : sc);
                double l = std::log(sc) / lb2 + 0.5;
                double factor = pow(2.0, l);
                if (factor != 1.0) for (i = 0; i < NN; i++) cs[i] *= factor;
            }

            // Compute lower bound on moduli of zeros
            std::vector<double> pt(Degree);
            for (i = 0; i < NN; i++) pt[i] = std::abs(p[i]);
            pt[N] = -(pt[N]);


            // Compute upper estimate of bound
            double x = std::exp((std::log(-pt[N]) - std::log(pt[0])) / N);

            int NM1 = N - 1;
            if (pt[NM1] != 0) {
                // If Newton step at the origin is better, use it
                double xm = -pt[N] / pt[NM1];
                x = (xm < x ? xm : x);
            }

            // Chop the interval (0, x) until ff <= 0
            double xm = x;
            double ff;
            do {
                x = xm;
                xm = 0.1 * x;
                ff = pt[0];
                for (i = 1; i < NN; i++) {
                    ff = ff * xm + pt[i];
                }
            } while (ff > 0); // End do-while loop

            double dx = x;

            // Do Newton iteration until x converges to two decimal places
            do {
                double df = ff = pt[0];
                for (i = 1; i < N; i++) {
                    ff = x * ff + pt[i];
                    df = x * df + ff;
                } // End for i
                ff = x * ff + pt[N];
                dx = ff / df;
                x -= dx;
            } while (std::abs(dx / x) > 0.005); // End do-while loop

            double bnd = x;

            // Compute the derivative as the initial K polynomial and do 5 steps with no shift
            std::vector<double> K(Degree);
            for (i = 1; i < N; i++) K[i] = double(N - i) * p[i] / N;
            K[0] = p[0];

            double aa = p[N];
            double bb = p[NM1];
            int zerok = K[NM1] == 0 ? 1 : 0;

            for (int jj = 0; jj < 5; jj++) {
                double cc = K[NM1];
                if (zerok) {
                    // Use unscaled form of recurrence
                    for (i = 0; i < NM1; i++) {
                        j = NM1 - i;
                        K[j] = K[j - 1];
                    } // End for i
                    K[0] = 0;
                    zerok = ((K[NM1] == 0) ? 1 : 0);
                } // End if (zerok)

                else { // else !zerok
                    // Used scaled form of recurrence if value of K at 0 is nonzero
                    t = -aa / cc;
                    for (i = 0; i < NM1; i++) {
                        j = NM1 - i;
                        K[j] = t * K[j - 1] + p[j];
                    } // End for i
                    K[0] = p[0];
                    zerok = ((std::abs(K[NM1]) <= std::abs(bb) * DBL_EPSILON * 10.0) ? 1 : 0);
                } // End else !zerok

            } // End for jj

            // Save K for restarts with new shifts
            std::vector<double> temp(Degree);
            for (i = 0; i < N; i++) {
                temp[i] = K[i];
            }

            // Loop to select the quadratic corresponding to each new shift

            for (int jj = 1; jj <= 20; jj++) {

                // Quadratic corresponds to a double shift to a non-real point and its
                // complex conjugate. The point has modulus BND and amplitude rotated
                // by 94 degrees from the previous shift.

                double xxx = -(sinr * yy) + cosr * xx;
                yy = sinr * xx + cosr * yy;
                xx = xxx;
                double sr = bnd * xx;
                double u = -(2.0 * sr);

                // Second stage calculation, fixed quadratic

                Fxshfr(20 * jj, &NZ, sr, bnd, K, N, p, NN, qp, u, &lzi, &lzr, &szi, &szr);

                if (NZ != 0) {

                    // The second stage jumps directly to one of the third stage iterations and
                    // returns here if successful. Deflate the polynomial, store the zero or
                    // zeros, and return to the main algorithm.

                    j = (Degree) - N;
                    zeror[j] = szr;
                    zeroi[j] = szi;
                    NN = NN - NZ;
                    N = NN - 1;
                    for (i = 0; i < NN; i++) {
                        p[i] = qp[i];
                    }
                    if (NZ != 1) {
                        zeror[j + 1] = lzr;
                        zeroi[j + 1] = lzi;
                    } // End if (NZ != 1)
                    break;
                } // End if (NZ != 0)
                else { // Else (NZ == 0)

                    // If the iteration is unsuccessful, another quadratic is chosen after restoring K
                    for (i = 0; i < N; i++) {
                        K[i] = temp[i];
                    }
                } // End else (NZ == 0)

            } // End for jj

            // Return with failure if no convergence with 20 shifts

            if (jj > 20) {
                std::cout << "\nFailure. No convergence after 20 shifts. Program terminated.\n";
                Degree -= N;
                break;
            } // End if (jj > 20)

        } // End while (N >= 1)

    return;
} // End rpoly

void PolynomialRoots::Fxshfr(int L2, int* NZ, double sr, double v, double K[MDP1], int N, double p[MDP1], int NN, double qp[MDP1], double u, double* lzi, double* lzr, double* szi, double* szr)
{

// Computes up to L2 fixed shift K-polynomials, testing for convergence in the linear or
// quadratic case. Initiates one of the variable shift iterations and returns with the
// number of zeros found.

// L2 limit of fixed shift steps
// NZ number of zeros found

    int fflag, i, iFlag = 1, j, spass, stry, tFlag, vpass, vtry;
    double a, a1, a3, a7, b, betas, betav, c, d, e, f, g, h, oss, ots, otv, ovv, s, ss, ts, tss, tv, tvv, ui, vi, vv;
    otv = 0;
    ots = 0;
    double qk[MDP1], svk[MDP1];

    *NZ = 0;
    betav = betas = 0.25;
    oss = sr;
    ovv = v;

//Evaluate polynomial by synthetic division
    QuadSD(NN, u, v, p, qp, &a, &b);

    tFlag = calcSC(N, a, b, &a1, &a3, &a7, &c, &d, &e, &f, &g, &h, K, u, v, qk);

    for (j = 0; j < L2; j++) {

        fflag = 1;
        //Calculate next K polynomial and estimate v
        nextK(N, tFlag, a, b, a1, &a3, &a7, K, qk, qp);
        tFlag = calcSC(N, a, b, &a1, &a3, &a7, &c, &d, &e, &f, &g, &h, K, u, v, qk);
        newest(tFlag, &ui, &vi, a, a1, a3, a7, b, c, d, f, g, h, u, v, K, N, p);

        vv = vi;

        // Estimate s

        ss = ((K[N - 1] != 0.0) ? -(p[N] / K[N - 1]) : 0.0);

        ts = tv = 1.0;

        if ((j != 0) && (tFlag != 3)) {

            // Compute relative measures of convergence of s and v sequences

            tv = ((vv != 0.0) ? std::abs((vv - ovv) / vv) : tv);
            ts = ((ss != 0.0) ? std::abs((ss - oss) / ss) : ts);

            // If decreasing, multiply the two most recent convergence measures

            tvv = ((tv < otv) ? tv * otv : 1.0);
            tss = ((ts < ots) ? ts * ots : 1.0);

            // Compare with convergence criteria

            vpass = ((tvv < betav) ? 1 : 0);
            spass = ((tss < betas) ? 1 : 0);

            if ((spass) || (vpass)) {

                // At least one sequence has passed the convergence test.
                // Store variables before iterating

                for (i = 0; i < N; i++) {
                    svk[i] = K[i];
                }

                s = ss;

                // Choose iteration according to the fastest converging sequence

                stry = vtry = 0;

                while(true) {

                    if ((fflag && ((fflag = 0) == 0)) && ((spass) && (!vpass || (tss < tvv)))) {
                        ; // Do nothing. Provides a quick "short circuit".
                    } // End if (fflag)

                    else { // else !fflag
                        QuadIT(N, NZ, ui, vi, szr, szi, lzr, lzi, qp, NN, &a, &b, p, qk, &a1, &a3, &a7, &c, &d, &e, &f, &g, &h, K);

                        if ((*NZ) > 0) {
                            return;
                        }

                        // Quadratic iteration has failed. Flag that it has been tried and decrease the
                        // convergence criterion

                        iFlag = vtry = 1;
                        betav *= 0.25;

                        // Try linear iteration if it has not been tried and the s sequence is converging
                        if (stry || (!spass)) {
                            iFlag = 0;
                        } // End if (stry || (!spass))
                        else {
                            for (i = 0; i < N; i++) {
                                K[i] = svk[i];
                            }
                        } // End if (stry || !spass)

                    } // End else fflag

                    if (iFlag != 0) {
                        auto  complex = RealIT(&s, N, p, NN, qp, K, qk);
                        *szr = complex.sz.real();
                        *szr = complex.sz.imag();
                        *NZ = complex.number_of_zeros;
                        iFlag = complex.flag;

                        if ((*NZ) > 0) {
                            return;
                        }

                        // Linear iteration has failed. Flag that it has been tried and decrease the
                        // convergence criterion

                        stry = 1;
                        betas *= 0.25;

                        if (iFlag != 0) {

                            // If linear iteration signals an almost double real zero, attempt quadratic iteration

                            ui = -(s + s);
                            vi = s * s;
                            continue;

                        } // End if (iFlag != 0)
                    } // End if (iFlag != 0)

                    // Restore variables
                    for (i = 0; i < N; i++) {
                        K[i] = svk[i];
                    }

                    // Try quadratic iteration if it has not been tried and the v sequence is converging

                    if (!vpass || vtry) {
                        break;    // Break out of infinite for loop
                    }

                } // End infinite for loop

                // Re-compute qp and scalar values to continue the second stage

                QuadSD(NN, u, v, p, qp, &a, &b);
                tFlag = calcSC(N, a, b, &a1, &a3, &a7, &c, &d, &e, &f, &g, &h, K, u, v, qk);

            } // End if ((spass) || (vpass))

        } // End if ((j != 0) && (tFlag != 3))

        ovv = vv;
        oss = ss;
        otv = tv;
        ots = ts;
    } // End for j

    return;
} // End Fxshfr

void PolynomialRoots::QuadSD(int NN, double u, double v, double p[MDP1], double q[MDP1], double* a, double* b)
{

// Divides p by the quadratic 1, u, v placing the quotient in q and the remainder in a, b

    int i;

    q[0] = *b = p[0];
    q[1] = *a = -((*b) * u) + p[1];

    for (i = 2; i < NN; i++) {
        q[i] = -((*a) * u + (*b) * v) + p[i];
        *b = (*a);
        *a = q[i];
    } // End for i

    return;
} // End QuadSD

int PolynomialRoots::calcSC(int N, double a, double b, double* a1, double* a3, double* a7, double* c, double* d, double* e, double* f, double* g, double* h, double K[MDP1], double u, double v, double qk[MDP1])
{

// This routine calculates scalar quantities used to compute the next K polynomial and
// new estimates of the quadratic coefficients.

// calcSC - integer variable set here indicating how the calculations are normalized
// to avoid overflow.

    int dumFlag = 3; // TYPE = 3 indicates the quadratic is almost a factor of K

// Synthetic division of K by the quadratic 1, u, v
    QuadSD(N, u, v, K, qk, c, d);

    if (std::abs((*c)) <= (100.0 * DBL_EPSILON * std::abs(K[N - 1]))) {
        if (std::abs((*d)) <= (100.0 * DBL_EPSILON * std::abs(K[N - 2]))) {
            return dumFlag;
        }
    } // End if (std::abs(c) <= (100.0*DBL_EPSILON*std::abs(K[N - 1])))

    *h = v * b;
    if (std::abs((*d)) >= std::abs((*c))) {
        dumFlag = 2; // TYPE = 2 indicates that all formulas are divided by d
        *e = a / (*d);
        *f = (*c) / (*d);
        *g = u * b;
        *a3 = (*e) * ((*g) + a) + (*h) * (b / (*d));
        *a1 = -a + (*f) * b;
        *a7 = (*h) + ((*f) + u) * a;
    } // End if(std::abs(d) >= std::abs(c))
    else {
        dumFlag = 1; // TYPE = 1 indicates that all formulas are divided by c;
        *e = a / (*c);
        *f = (*d) / (*c);
        *g = (*e) * u;
        *a3 = (*e) * a + ((*g) + (*h) / (*c)) * b;
        *a1 = -(a * ((*d) / (*c))) + b;
        *a7 = (*g) * (*d) + (*h) * (*f) + a;
    } // End else

    return dumFlag;
} // End calcSC

void PolynomialRoots::nextK(int N, int tFlag, double a, double b, double a1, double* a3, double* a7, double K[MDP1], double qk[MDP1], double qp[MDP1])
{

// Computes the next K polynomials using the scalars computed in calcSC

    int i;
    double temp;

    if (tFlag == 3) { // Use unscaled form of the recurrence
        K[1] = K[0] = 0.0;

        for (i = 2; i < N; i++) {
            K[i] = qk[i - 2];
        }

        return;
    } // End if (tFlag == 3)

    temp = ((tFlag == 1) ? b : a);

    if (std::abs(a1) > (10.0 * DBL_EPSILON * std::abs(temp))) {
        // Use scaled form of the recurrence

        (*a7) /= a1;
        (*a3) /= a1;
        K[0] = qp[0];
        K[1] = -((*a7) * qp[0]) + qp[1];

        for (i = 2; i < N; i++) {
            K[i] = -((*a7) * qp[i - 1]) + (*a3) * qk[i - 2] + qp[i];
        }

    } // End if (std::abs(a1) > (10.0*DBL_EPSILON*std::abs(temp)))
    else {
        // If a1 is nearly zero, then use a special form of the recurrence

        K[0] = 0.0;
        K[1] = -(*a7) * qp[0];

        for (i = 2; i < N; i++) {
            K[i] = -((*a7) * qp[i - 1]) + (*a3) * qk[i - 2];
        }
    } // End else

    return;

} // End nextK

void PolynomialRoots::newest(int tFlag, double* uu, double* vv, double a, double a1, double a3, double a7, double b, double c, double d, double f, double g, double h, double u, double v, double K[MDP1], int N, double p[MDP1])
{
// Compute new estimates of the quadratic coefficients using the scalars computed in calcSC

    double a4, a5, b1, b2, c1, c2, c3, c4, temp;

    (*vv) = (*uu) = 0.0; // The quadratic is zeroed

    if (tFlag != 3) {

        if (tFlag != 2) {
            a4 = a + u * b + h * f;
            a5 = c + (u + v * f) * d;
        } // End if (tFlag != 2)
        else { // else tFlag == 2
            a4 = (a + g) * f + h;
            a5 = (f + u) * c + v * d;
        } // End else tFlag == 2

        // Evaluate new quadratic coefficients

        b1 = -K[N - 1] / p[N];
        b2 = -(K[N - 2] + b1 * p[N - 1]) / p[N];
        c1 = v * b2 * a1;
        c2 = b1 * a7;
        c3 = b1 * b1 * a3;
        c4 = -(c2 + c3) + c1;
        temp = -c4 + a5 + b1 * a4;
        if (temp != 0.0) {
            *uu = -((u * (c3 + c2) + v * (b1 * a1 + b2 * a7)) / temp) + u;
            *vv = v * (1.0 + c4 / temp);
        } // End if (temp != 0)

    } // End if (tFlag != 3)

    return;
} // End newest

void PolynomialRoots::QuadIT(int N, int* NZ, double uu, double vv, double* szr, double* szi, double* lzr, double* lzi, double qp[MDP1], int NN, double* a, double* b, double p[MDP1], double qk[MDP1], double* a1, double* a3, double* a7, double* c, double* d, double* e, double* f, double* g, double* h, double K[MDP1])
{

// Variable-shift K-polynomial iteration for a quadratic factor converges only if the
// zeros are equimodular or nearly so.

    int i, j = 0, tFlag, triedFlag = 0;
    double ee, mp, omp, relstp, t, u, ui, v, vi, zm;
    relstp = 0;
    omp = 0;

    *NZ = 0; // Number of zeros found
    u = uu; // uu and vv are coefficients of the starting quadratic
    v = vv;

    do {
        auto roots = Quadratic(1, u, v);
        *szr = roots.first.real();
        *szi = roots.first.imag();
        *lzr = roots.first.real();
        *lzi = roots.first.imag();


        // Return if roots of the quadratic are real and not close to multiple or nearly
        // equal and of opposite sign.

        if (std::abs(std::abs(*szr) - std::abs(*lzr)) > 0.01 * std::abs(*lzr)) {
            break;
        }

        // Evaluate polynomial by quadratic synthetic division

        QuadSD(NN, u, v, p, qp, a, b);

        mp = std::abs(-((*szr) * (*b)) + (*a)) + std::abs((*szi) * (*b));

        // Compute a rigorous bound on the rounding error in evaluating p

        zm = std::sqrt(std::abs(v));
        ee = 2.0 * std::abs(qp[0]);
        t = -((*szr) * (*b));

        for (i = 1; i < N; i++) {
            ee = ee * zm + std::abs(qp[i]);
        }

        ee = ee * zm + std::abs((*a) + t);
        ee = (9.0 * ee + 2.0 * std::abs(t) - 7.0 * (std::abs((*a) + t) + zm * std::abs((*b)))) * DBL_EPSILON;

        // Iteration has converged sufficiently if the polynomial value is less than 20 times this bound

        if (mp <= 20.0 * ee) {
            *NZ = 2;
            break;
        } // End if (mp <= 20.0*ee)

        j++;

        // Stop iteration after 20 steps
        if (j > 20) {
            break;
        }

        if (j >= 2) {
            if ((relstp <= 0.01) && (mp >= omp) && (!triedFlag)) {
                // A cluster appears to be stalling the convergence. Five fixed shift
                // steps are taken with a u, v close to the cluster.

                relstp = ((relstp < DBL_EPSILON) ? std::sqrt(DBL_EPSILON) : std::sqrt(relstp));

                u -= u * relstp;
                v += v * relstp;

                QuadSD(NN, u, v, p, qp, a, b);

                for (i = 0; i < 5; i++) {
                    tFlag = calcSC(N, *a, *b, a1, a3, a7, c, d, e, f, g, h, K, u, v, qk);
                    nextK(N, tFlag, *a, *b, *a1, a3, a7, K, qk, qp);
                } // End for i

                triedFlag = 1;
                j = 0;

            } // End if ((relstp <= 0.01) && (mp >= omp) && (!triedFlag))

        } // End if (j >= 2)

        omp = mp;

        // Calculate next K polynomial and new u and v

        tFlag = calcSC(N, *a, *b, a1, a3, a7, c, d, e, f, g, h, K, u, v, qk);
        nextK(N, tFlag, *a, *b, *a1, a3, a7, K, qk, qp);
        tFlag = calcSC(N, *a, *b, a1, a3, a7, c, d, e, f, g, h, K, u, v, qk);
        newest(tFlag, &ui, &vi, *a, *a1, *a3, *a7, *b, *c, *d, *f, *g, *h, u, v, K, N, p);

        // If vi is zero, the iteration is not converging
        if (vi != 0) {
            relstp = std::abs((-v + vi) / vi);
            u = ui;
            v = vi;
        } // End if (vi != 0)
    } while (vi != 0); // End do-while loop

    return;

}


GradedComplex PolynomialRoots::RealIT(double* sss, int N, double const p[101], int NN, double qp[101], double K[101], double qk[101]) const
{

// Variable-shift H-polynomial iteration for a real zero

// sss - starting iterate
// NZ - number of zeros found
// iFlag - flag to indicate a pair of zeros near real axis

    GradedComplex complex;

    int counter = 0;
    double t = 0;
    double omp = 0;
    double s = *sss;
    while(true) {
        double pv = p[0];
        // Evaluate p at s
        qp[0] = pv;
        for (int i = 1; i < NN; i++) qp[i] = pv = pv * s + p[i];
        double mp = std::abs(pv);
        // Compute a rigorous bound on the error in evaluating p
        double ms = std::abs(s);
        double ee = 0.5 * std::abs(qp[0]);
        for (int i = 1; i < NN; i++) ee = ee * ms + std::abs(qp[i]);
        // Iteration has converged sufficiently if the polynomial value is less than
        // 20 times this bound
        if (mp <= 20.0 * DBL_EPSILON * (2.0 * ee - mp)) {
            complex.number_of_zeros = 1;
            complex.sz = s;
            break;
        }
        counter++;
        // Stop iteration after 10 steps
        if (counter > 10) break;
        if (counter >= 2) {
            if ((std::abs(t) <= 0.001 * std::abs(-t + s)) && (mp > omp)) {
                // A cluster of zeros near the real axis has been encountered;
                // Return with iFlag set to initiate a quadratic iteration
                complex.flag = 1;
                *sss = s;
                break;
            }
        }
        // Return if the polynomial value has increased significantly
        omp = mp;
        // Compute t, the next polynomial and the new iterate
        qk[0] = K[0];
        double kv = K[0];
        for (int i = 1; i < N; i++) qk[i] = kv = kv * s + K[i];

        if (std::abs(kv) > std::abs(K[N - 1]) * 10.0 * DBL_EPSILON) {
            // Use the scaled form of the recurrence if the value of K at s is non-zero
            t = -(pv / kv);
            K[0] = qp[0];
            for (int i = 1; i < N; i++) K[i] = t * qk[i - 1] + qp[i];
        } else {
            // Use unscaled form
            K[0] = 0.0;
            for (int i = 1; i < N; i++) K[i] = qk[i - 1];
        }
        kv = K[0];
        for (int i = 1; i < N; i++) kv = kv * s + K[i];
        t = ((std::abs(kv) > (std::abs(K[N - 1]) * 10.0 * DBL_EPSILON)) ? -(pv / kv) : 0.0);
        s += t;
    }
    return complex;
}

// Calculates the zeros of the quadratic a*Z^2 + b1*Z + c
// The quadratic formula, modified to avoid overflow, is used to find the larger zero if the
// zeros are real and both zeros are complex. The smaller real zero is found directly from
// the product of the zeros c/a.
std::pair<std::complex<double>,std::complex<double>> PolynomialRoots::Quadratic(double quadratic, double linear, double constant) const
{
    std::complex<double> s(0);
    std::complex<double> l(0);

    if (quadratic == 0) {
        if (linear != 0) s = - constant / linear;
        return std::make_pair(s,l);
    }

    if (constant == 0) {
        l = - linear / quadratic;
        return std::make_pair(s,l);
    }

// Compute discriminant avoiding overflow
    auto lin = linear / 2;
    double root, discriminant;
    if (std::abs(lin) < std::abs(constant)) {
        discriminant = constant >= 0 ? quadratic : -quadratic;
        discriminant = -discriminant + lin * (lin / std::abs(constant));
        root = std::sqrt(std::abs(discriminant)) * std::sqrt(std::abs(constant));
    } else {
        discriminant = -((quadratic / lin) * (constant / lin)) + 1.0;
        root = std::sqrt(std::abs(discriminant)) * (std::abs(lin));
    }

    if (discriminant >= 0) {
        // Real zeros
        root = lin >= 0 ? -root : root;
        l = (root -lin) / quadratic;
        s = l.real() != 0 ? constant / l / quadratic : s;
    } else {
        // Complex conjugate zeros
        l = s = - lin / quadratic;
        s.imag(std::abs(root / quadratic));
        l.imag(- s.imag());
    }
    return std::make_pair(s,l);
}

}

/*int main()
{char rflag = 0; //Readiness flag

std::cout << "                                           rpoly (14 July 2007)\n";
std::cout << "=========================================================================== \n";
std::cout << "This program calculates the roots of a polynomial of real coefficients:\n";
std::cout << "\nop[0]*x^N + op[1]*x^(N-1) + op[2]*x^(N-2) + . . . + op[N]*x^0 = 0 \n";
std::cout << "\n--------------------------------------------------------------------------- \n";
std::cout << "\nThis program can accept polynomials of degree 100 or less, specified by the\n";
std::cout << "constant MAXDEGREE. If a higher order polynomial is to be input, redefine\n";
std::cout << "MAXDEGREE and re-compile the program.\n";
std::cout << "\n--------------------------------------------------------------------------- \n";
std::cout << "\nAll relevant data for the polynomial whose roots will be sought should have\n";
std::cout << "been saved beforehand in a file named rpolydat.txt.\n";
std::cout << "rpolydat.txt should be in the same folder as the rpoly executable. \n";
std::cout << "--------------------------------------------------------------------------- \n";
std::cout << "\nThe first entry of this file must be the degree, N, of the polynomial for\n";
std::cout << "which the roots are to be calculated.\n";
std::cout << "Entries for the coefficients of the polynomial should follow, starting with\n";
std::cout << "the coefficient for the highest power of x and working down to the coefficient\n";
std::cout << "for the x^0 term.\n";
std::cout << "\nThe data is assumed to be of type double. Variables used within this program\n";
std::cout << "are type double.\n";
std::cout << "\n--------------------------------------------------------------------------- \n";
std::cout << "\nThe output is written to the file rpolyout.txt.\n";
std::cout << "\nNote the returned value of the variable Degree.\n";
std::cout << "If Degree > 0, it specifies the number of zeros found.\n";
std::cout << "If Degree = 0, the leading coefficient of the input polynomial was 0.\n";
std::cout << "If Degree = -1, the input value of Degree was greater than MAXDEGREE.\n";
std::cout << "\n--------------------------------------------------------------------------- \n";
std::cout << "\nAdditional information is posted at the following URL:\n";
std::cout << "http://www.akiti.ca/rpoly_Intro.html\n";
std::cout << "--------------------------------------------------------------------------- \n";
std::cout << "\nIs everything ready (are you ready to continue?)? If yes, Enter y. \n";
std::cout << "Otherwise Enter any other key. \n";
cin >> rflag;

if (toupper(rflag) == 'Y') {

    int Degree; // The degree of the polynomial to be solved
    std::cout << "Appear to be ready. \n";

    ifstream in("rpolydat.txt", ios::in);

    if (!in) {
        std::cout << "Cannot open the input file.\n";
        return 0;
    }

    in >> Degree; //Input the polynomial degree from the file
    if (Degree < 0) {
        std::cout << "Invalid polynomial degree entered. Program terminated. \n";
        in.close(); //Close the input file before terminating
        return 0;
    }

    ofstream out("rpolyout.txt", ios::out);
    if (!out) {
        std::cout << "Cannot open the output file. Program terminated.\n";
        in.close(); //Close the input file before terminating
        return 0;
    }

    double op[MDP1], zeroi[MAXDEGREE], zeror[MAXDEGREE]; // Coefficient vectors
    int i; // vector index

    //Input the polynomial coefficients from the file and put them in the op vector
    for (i = 0; i < (Degree+1); i++){
        in >> op[i];
    }//End for i

    in.close(); //Close the input file

    rpoly(op, &Degree, zeror, zeroi);

    out << "Degree = " << Degree << ".\n";
    out << "\n";

    if (Degree <= 0){
        std::cout << "\nReturned from rpoly and Degree had a value <= 0.\n";
    } // End if (Degree <= 0)
    else { // else Degree > 0
        out.precision(DBL_DIG);
        out << "The roots follow:\n";
        out << "\n";
        for (i = 0; i < Degree; i++){
            out << zeror[i] << " + " << zeroi[i] << "i" << " \n";
        }//End for i
    } // End else Degree > 0

    out.close(); // Close the output file
} //End if rflag = 'Y'
else std::cout << "\nNot ready. Try again when ready with information. \n";
std::cout << "\nEnter any key to continue. \n";
cin >> rflag;
return 0;
} // End main program.*/

