/***********************************************************************/
/* */
/* Finding mt2 by Bisection */
/* */
/* Authors: Hsin-Chia Cheng, Zhenyu Han */
/* Dec 11, 2008, v1.01a */
/* */
/***********************************************************************/

// This program calculates MT2 using the bisection method described in arXiv:0810.5178.

/*******************************************************************************
 * Usage:
 *
 * 1. Define an object of type "mt2":
 *
 * mt2_bisect::mt2 mt2_event;
 *
 * 2. Set momenta and the mass of the invisible particle, mn:
 *
 * mt2_event.set_momenta( pa, pb, pmiss );
 * mt2_event.set_mass( mn );
 *
 * where array pa[0..2], pb[0..2], pmiss[0..2] contains (mass,px,py)
 * for the visible particles and the missing momentum. pmiss[0] is not used.
 * All quantities are given in double.
 *
 * 3. Use mt2::get_mt2() to obtain the value of mt2:
 *
 * double mt2_value = mt2_event.get_mt2();
 *
 *******************************************************************************/

#include <iostream>
#include <cmath>

#include "wimpmass/Mt2.hh"

namespace wimpmass
{

namespace
{
/*The user can change the desired precision below, the larger one of the following two definitions is used. Relative precision less than 0.00001 is not guaranteed to be achievable--use with caution*/

const double RELATIVE_PRECISION = 0.00001; //defined as precision = RELATIVE_PRECISION * scale, where scale = max{Ea, Eb}
const double ABSOLUTE_PRECISION = 0.0; //absolute precision for mt2, unused by default


//Reserved for expert
const double MIN_MASS = 0.1; //if ma<MINMASS and mb<MINMASS, use massless code
const double ZERO_MASS = 0.000; //give massless particles a small mass
const double SCANSTEP = 0.1;
}

Mt2::Mt2(boca::Mass const& mass)
{
    if (mass != boca::massless) SetMass(mass.value());
}

double Mt2::Get(boca::Jet const& jet_1,  boca::Jet const& jet_2,  boca::MissingEt const& missing_et) {
    double pa0[3],  pb0[3], pmiss0[3];
    GetMomentum(jet_1, pa0);
    GetMomentum(jet_2, pb0);
    GetMomentum(missing_et, pmiss0);
    SetMomenta(pa0, pb0, pmiss0);
    return GetMt2();
}

void Mt2::GetMomentum(boca::Jet const& jet_1,  double *momentum) {
    momentum[0] = jet_1.Mass().value();
    momentum[1] = jet_1.Px().value();
    momentum[2] = jet_1.Py().value();
}

double Mt2::GetMt2()
{
    if (!momenta_set) {
        std::cout << " Please set momenta first!" << '\n';
        return 0;
    }
    if (!solved) Bisect();
    return mt2_b * scale;
}

void Mt2::SetMomenta(double *pa0, double *pb0, double *pmiss0)
{
    solved = false; //reset solved tag when momenta are changed.
    momenta_set = true;

    ma = std::abs(pa0[0]); // mass cannot be negative

    if (ma < ZERO_MASS) ma = ZERO_MASS;
    pax = pa0[1];
    pay = pa0[2];
    masq = ma * ma;
    Easq = masq + pax * pax + pay * pay;
    Ea = std::sqrt(Easq);

    mb = std::abs(pb0[0]);
    if (mb < ZERO_MASS) mb = ZERO_MASS;
    pbx = pb0[1];
    pby = pb0[2];
    mbsq = mb * mb;
    Ebsq = mbsq + pbx * pbx + pby * pby;
    Eb = std::sqrt(Ebsq);

    pmissx = pmiss0[1];
    pmissy = pmiss0[2];
    pmissxsq = pmissx * pmissx;
    pmissysq = pmissy * pmissy;

    // set ma>= mb
    if (masq < mbsq) {
        auto temp = pax;
        pax = pbx;
        pbx = temp;
        temp = pay;
        pay = pby;
        pby = temp;
        temp = Ea;
        Ea = Eb;
        Eb = temp;
        temp = Easq;
        Easq = Ebsq;
        Ebsq = temp;
        temp = masq;
        masq = mbsq;
        mbsq = temp;
        temp = ma;
        ma = mb;
        mb = temp;
    }
    //normalize max{Ea, Eb} to 100
    if (Ea > Eb) scale = Ea / 100.;
    else scale = Eb / 100.;

    if (std::sqrt(pmissxsq + pmissysq) / 100 > scale) scale = std::sqrt(pmissxsq + pmissysq) / 100;
    //scale = 1;
    auto scalesq = scale * scale;
    ma = ma / scale;
    mb = mb / scale;
    masq = masq / scalesq;
    mbsq = mbsq / scalesq;
    pax = pax / scale;
    pay = pay / scale;
    pbx = pbx / scale;
    pby = pby / scale;
    Ea = Ea / scale;
    Eb = Eb / scale;

    Easq = Easq / scalesq;
    Ebsq = Ebsq / scalesq;
    pmissx = pmissx / scale;
    pmissy = pmissy / scale;
    pmissxsq = pmissxsq / scalesq;
    pmissysq = pmissysq / scalesq;
    mn = mn_unscale / scale;
    mnsq = mn * mn;

    if (ABSOLUTE_PRECISION > 100.*RELATIVE_PRECISION) precision = ABSOLUTE_PRECISION;
    else precision = 100.*RELATIVE_PRECISION;
}

void Mt2::SetMass(double mn0)
{
    solved = false; //reset solved tag when mn is changed.
    mn_unscale = std::abs(mn0); //mass cannot be negative
    mn = mn_unscale / scale;
    mnsq = mn * mn;
}

void Mt2::Print()
{
    std::cout << " pax = " << pax *scale << "; pay = " << pay *scale << "; ma = " << ma *scale << ";" << '\n';
    std::cout << " pbx = " << pbx *scale << "; pby = " << pby *scale << "; mb = " << mb *scale << ";" << '\n';
    std::cout << " pmissx = " << pmissx *scale << "; pmissy = " << pmissy *scale << ";" << '\n';
    std::cout << " mn = " << mn_unscale << ";" << '\n';
}

//special case, the visible particle is massless
void Mt2::Massless()
{
    //rotate so that pay = 0
    auto theta = atan(pay / pax);
    auto s = sin(theta);
    auto c = cos(theta);

    Easq = pax * pax + pay * pay;
    Ebsq = pbx * pbx + pby * pby;
    Ea = std::sqrt(Easq);
    Eb = std::sqrt(Ebsq);

    auto pxtemp = pax * c + pay * s;
    pax = pxtemp;
    pay = 0;
    pxtemp = pbx * c + pby * s;
    auto pytemp = -s * pbx + c * pby;
    pbx = pxtemp;
    pby = pytemp;
    pxtemp = pmissx * c + pmissy * s;
    pytemp = -s * pmissx + c * pmissy;
    pmissx = pxtemp;
    pmissy = pytemp;

    a2 = 1 - pbx * pbx / (Ebsq);
    b2 = -pbx * pby / (Ebsq);
    c2 = 1 - pby * pby / (Ebsq);

    d21 = (Easq * pbx) / Ebsq;
    d20 = - pmissx + (pbx * (pbx * pmissx + pby * pmissy)) / Ebsq;
    e21 = (Easq * pby) / Ebsq;
    e20 = - pmissy + (pby * (pbx * pmissx + pby * pmissy)) / Ebsq;
    f22 = -(Easq * Easq / Ebsq);
    f21 = -2 * Easq * (pbx * pmissx + pby * pmissy) / Ebsq;
    f20 = mnsq + pmissxsq + pmissysq - (pbx * pmissx + pby * pmissy) * (pbx * pmissx + pby * pmissy) / Ebsq;

    auto Deltasq0 = 0.;
    auto Deltasq_low = Deltasq0 + precision;
    auto nsols_low = nsols_massless(Deltasq_low);

    if (nsols_low > 1) {
        mt2_b = std::sqrt(Deltasq0 + mnsq);
        return;
    }

    /*
     *    if( nsols_massless(Deltasq_high) > 0 )
     *    {
     *    mt2_b = std::sqrt(mnsq+Deltasq0);
     *    return;
    }*/

    //look for when both parablos contain origin
    auto Deltasq_high1 = 2 * Eb * std::sqrt(pmissx * pmissx + pmissy * pmissy + mnsq) - 2 * pbx * pmissx - 2 * pby * pmissy;
    auto Deltasq_high2 = 2 * Ea * mn;

    auto Deltasq_high = Deltasq_high1 < Deltasq_high2 ?  Deltasq_high2 : Deltasq_high1;
    auto nsols_high = nsols_massless(Deltasq_high);

    if (nsols_high == nsols_low) {
        auto foundhigh = 0;
        auto minmass = mn ;
        auto maxmass = std::sqrt(mnsq + Deltasq_high);
        for (auto mass = minmass + SCANSTEP; mass < maxmass; mass += SCANSTEP) {
            Deltasq_high = mass * mass - mnsq;
            nsols_high = nsols_massless(Deltasq_high);
            if (nsols_high > 0) {
                foundhigh = 1;
                Deltasq_low = (mass - SCANSTEP) * (mass - SCANSTEP) - mnsq;
                break;
            }
        }
        if (foundhigh == 0) {
            std::cout << "Deltasq_high not found at event " << nevt << '\n';
            mt2_b = std::sqrt(Deltasq_low + mnsq);
            return;
        }
    }

    if (nsols_high == nsols_low) {
        std::cout << "error: nsols_low=nsols_high=" << nsols_high << '\n';
        std::cout << "Deltasq_high=" << Deltasq_high << '\n';
        std::cout << "Deltasq_low= " << Deltasq_low << '\n';
        mt2_b = std::sqrt(mnsq + Deltasq_low);
        return;
    }
    auto minmass = std::sqrt(Deltasq_low + mnsq);
    auto maxmass = std::sqrt(Deltasq_high + mnsq);
    while (maxmass - minmass > precision) {
        auto midmass = (minmass + maxmass) / 2.;
        auto Delta_mid = midmass * midmass - mnsq;
        auto nsols_mid = nsols_massless(Delta_mid);
        if (nsols_mid != nsols_low) maxmass = midmass;
        if (nsols_mid == nsols_low) minmass = midmass;
    }
    mt2_b = minmass;
    return;
}

int Mt2::nsols_massless(double Dsq)
{
    auto delta = Dsq / (2 * Easq);
    d1 = d11 * delta;
    e1 = e11 * delta;
    f1 = f12 * delta * delta + f10;
    d2 = d21 * delta + d20;
    e2 = e21 * delta + e20;
    f2 = f22 * delta * delta + f21 * delta + f20;

    auto a = pax > 0 ? Ea / Dsq : -Ea / Dsq;

    auto b = pax > 0 ? -Dsq / (4 * Ea) + mnsq * Ea / Dsq : Dsq / (4 * Ea) - mnsq * Ea / Dsq;

    auto A4 = a * a * a2;
    auto A3 = 2 * a * b2 / Ea;
    auto A2 = (2 * a * a2 * b + c2 + 2 * a * d2) / (Easq);
    auto A1 = (2 * b * b2 + 2 * e2) / (Easq * Ea);
    auto A0 = (a2 * b * b + 2 * b * d2 + f2) / (Easq * Easq);

    auto A3sq = A3 * A3;

    auto B3 = 4 * A4;
    auto B2 = 3 * A3;
    auto B1 = 2 * A2;
    auto B0 = A1;

    auto C2 = -(A2 / 2 - 3 * A3sq / (16 * A4));
    auto C1 = -(3 * A1 / 4. - A2 * A3 / (8 * A4));
    auto C0 = -A0 + A1 * A3 / (16 * A4);

    auto D1 = -B1 - (B3 * C1 * C1 / C2 - B3 * C0 - B2 * C1) / C2;
    auto D0 = -B0 - B3 * C0 * C1 / (C2 * C2) + B2 * C0 / C2;

    auto E0 = -C0 - C2 * D0 * D0 / (D1 * D1) + C1 * D0 / D1;

    //find the coefficients for the leading term in the Sturm sequence
    auto t1 = A4;
    auto t2 = A4;
    auto t3 = C2;
    auto t4 = D1;
    auto t5 = E0;

    auto nsol = signchange_n(t1, t2, t3, t4, t5) - signchange_p(t1, t2, t3, t4, t5);
    if (nsol < 0) nsol = 0;
    return nsol;
}

void Mt2::Bisect()
{
    solved = true;
    std::cout.precision(11);

    //if masses are very small, use code for massless case.
    if (masq < MIN_MASS && mbsq < MIN_MASS) {
        Massless();
        return;
    }

    auto Deltasq0 = ma * (ma + 2 * mn); //The minimum mass square to have two ellipses
    // find the coefficients for the two quadratic equations when Deltasq=Deltasq0.
    a1 = 1 - pax * pax / (Easq);
    b1 = -pax * pay / (Easq);
    c1 = 1 - pay * pay / (Easq);
    d1 = -pax * (Deltasq0 - masq) / (2 * Easq);
    e1 = -pay * (Deltasq0 - masq) / (2 * Easq);
    a2 = 1 - pbx * pbx / (Ebsq);
    b2 = -pbx * pby / (Ebsq);
    c2 = 1 - pby * pby / (Ebsq);
    d2 = -pmissx + pbx * (Deltasq0 - mbsq) / (2 * Ebsq) + pbx * (pbx * pmissx + pby * pmissy) / (Ebsq);
    e2 = -pmissy + pby * (Deltasq0 - mbsq) / (2 * Ebsq) + pby * (pbx * pmissx + pby * pmissy) / (Ebsq);
    f2 = pmissx * pmissx + pmissy * pmissy - ((Deltasq0 - mbsq) / (2 * Eb) +
            (pbx * pmissx + pby * pmissy) / Eb) * ((Deltasq0 - mbsq) / (2 * Eb) +
                    (pbx * pmissx + pby * pmissy) / Eb) + mnsq;

    // find the center of the smaller ellipse
    auto x0 = (c1 * d1 - b1 * e1) / (b1 * b1 - a1 * c1);
    auto y0 = (a1 * e1 - b1 * d1) / (b1 * b1 - a1 * c1);


    // Does the larger ellipse contain the smaller one?
    auto dis = a2 * x0 * x0 + 2 * b2 * x0 * y0 + c2 * y0 * y0 + 2 * d2 * x0 + 2 * e2 * y0 + f2;

    if (dis <= 0.01) {
        mt2_b = std::sqrt(mnsq + Deltasq0);
        return;
    }

    /* find the coefficients for the two quadratic equations */
    /* coefficients for quadratic terms do not change */
    /* coefficients for linear and constant terms are polynomials of */
    /* delta=(Deltasq-m7sq)/(2 E7sq) */
    d11 = -pax;
    e11 = -pay;
    f10 = mnsq;
    f12 = -Easq;
    d21 = (Easq * pbx) / Ebsq;
    d20 = ((masq - mbsq) * pbx) / (2.*Ebsq) - pmissx +
          (pbx * (pbx * pmissx + pby * pmissy)) / Ebsq;
    e21 = (Easq * pby) / Ebsq;
    e20 = ((masq - mbsq) * pby) / (2.*Ebsq) - pmissy +
          (pby * (pbx * pmissx + pby * pmissy)) / Ebsq;
    f22 = -Easq * Easq / Ebsq;
    f21 = (-2 * Easq * ((masq - mbsq) / (2.*Eb) + (pbx * pmissx + pby * pmissy) / Eb)) / Eb;
    f20 = mnsq + pmissx * pmissx + pmissy * pmissy -
          ((masq - mbsq) / (2.*Eb) + (pbx * pmissx + pby * pmissy) / Eb)
          * ((masq - mbsq) / (2.*Eb) + (pbx * pmissx + pby * pmissy) / Eb);

    //Estimate upper bound of mT2
    //when Deltasq > Deltasq_high1, the larger encloses the center of the smaller
    auto p2x0 = pmissx - x0;
    auto p2y0 = pmissy - y0;
    auto Deltasq_high1 = 2 * Eb * std::sqrt(p2x0 * p2x0 + p2y0 * p2y0 + mnsq) - 2 * pbx * p2x0 - 2 * pby * p2y0 + mbsq;

    //Another estimate, if both ellipses enclose the origin, Deltasq > mT2

    auto Deltasq_high21 = 2 * Eb * std::sqrt(pmissx * pmissx + pmissy * pmissy + mnsq) - 2 * pbx * pmissx - 2 * pby * pmissy + mbsq;
    auto Deltasq_high22 = 2 * Ea * mn + masq;

    auto Deltasq_high2 = Deltasq_high21 < Deltasq_high22 ? Deltasq_high22 : Deltasq_high21;

    //pick the smaller upper bound
    auto Deltasq_high = Deltasq_high1 < Deltasq_high2 ? Deltasq_high1 : Deltasq_high2;

    //lower bound
    auto Deltasq_low = Deltasq0;

    //number of solutions at Deltasq_low should not be larger than zero
    if (nsols(Deltasq_low) > 0) {
        //std::cout << "nsolutions(Deltasq_low) > 0"<<'\n';
        mt2_b = std::sqrt(mnsq + Deltasq0);
        return;
    }
    auto nsols_low = nsols(Deltasq_low);
    int foundhigh;

    //if nsols_high=nsols_low, we missed the region where the two ellipse overlap
    //if nsols_high=4, also need a scan because we may find the wrong tangent point.

    auto nsols_high = nsols(Deltasq_high);
    if (nsols_high == nsols_low || nsols_high == 4) {
        //foundhigh = scan_high(Deltasq_high);
        foundhigh = find_high(Deltasq_high);
        if (foundhigh == 0) {
            std::cout << "Deltasq_high not found at event " << nevt << '\n';
            mt2_b = std::sqrt(Deltasq_low + mnsq);
            return;
        }
    }
    while (std::sqrt(Deltasq_high + mnsq) - std::sqrt(Deltasq_low + mnsq) > precision) {
        //bisect
        auto Deltasq_mid = (Deltasq_high + Deltasq_low) / 2.;
        auto nsols_mid = nsols(Deltasq_mid);
        // if nsols_mid = 4, rescan for Deltasq_high
        if (nsols_mid == 4) {
            Deltasq_high = Deltasq_mid;
            //scan_high(Deltasq_high);
            find_high(Deltasq_high);
            continue;
        }
        if (nsols_mid != nsols_low) Deltasq_high = Deltasq_mid;
        if (nsols_mid == nsols_low) Deltasq_low = Deltasq_mid;
    }
    mt2_b = std::sqrt(mnsq + Deltasq_high);
    return;
}

int Mt2::find_high(double &Deltasq_high)
{
    auto x0 = (c1 * d1 - b1 * e1) / (b1 * b1 - a1 * c1);
    auto y0 = (a1 * e1 - b1 * d1) / (b1 * b1 - a1 * c1);
    auto Deltasq_low = (mn + ma) * (mn + ma) - mnsq;
    do {
        auto Deltasq_mid = (Deltasq_high + Deltasq_low) / 2.;
        auto nsols_mid = nsols(Deltasq_mid);
        if (nsols_mid == 2) {
            Deltasq_high = Deltasq_mid;
            return 1;
        } else if (nsols_mid == 4) {
            Deltasq_high = Deltasq_mid;
            continue;
        } else if (nsols_mid == 0) {
            d1 = -pax * (Deltasq_mid - masq) / (2 * Easq);
            e1 = -pay * (Deltasq_mid - masq) / (2 * Easq);
            d2 = -pmissx + pbx * (Deltasq_mid - mbsq) / (2 * Ebsq)
                 + pbx * (pbx * pmissx + pby * pmissy) / (Ebsq);
            e2 = -pmissy + pby * (Deltasq_mid - mbsq) / (2 * Ebsq)
                 + pby * (pbx * pmissx + pby * pmissy) / (Ebsq);
            f2 = pmissx * pmissx + pmissy * pmissy - ((Deltasq_mid - mbsq) / (2 * Eb) +
                    (pbx * pmissx + pby * pmissy) / Eb) * ((Deltasq_mid - mbsq) / (2 * Eb) +
                            (pbx * pmissx + pby * pmissy) / Eb) + mnsq;
            // Does the larger ellipse contain the smaller one?
            auto dis = a2 * x0 * x0 + 2 * b2 * x0 * y0 + c2 * y0 * y0 + 2 * d2 * x0 + 2 * e2 * y0 + f2;
            if (dis < 0) Deltasq_high = Deltasq_mid;
            else Deltasq_low = Deltasq_mid;
        }
    } while (Deltasq_high - Deltasq_low > 0.001);
    return 0;
}

int Mt2::scan_high(double &Deltasq_high)
{
    auto foundhigh = 0 ;
    auto tempmass = mn + ma;
    auto maxmass = std::sqrt(mnsq + Deltasq_high);
    if (nevt == 32334) std::cout << "Deltasq_high = " << Deltasq_high << '\n';
    for (auto mass = tempmass + SCANSTEP; mass < maxmass; mass += SCANSTEP) {
        Deltasq_high = mass * mass - mnsq;
        if (nsols(Deltasq_high) > 0) {
//             Deltasq_low = (mass - SCANSTEP) * (mass - SCANSTEP) - mnsq;
            foundhigh = 1;
            break;
        }
    }
    return foundhigh;
}

int Mt2::nsols(double Dsq)
{
    auto delta = (Dsq - masq) / (2 * Easq);
    //calculate coefficients for the two quadratic equations
    d1 = d11 * delta;
    e1 = e11 * delta;
    f1 = f12 * delta * delta + f10;
    d2 = d21 * delta + d20;
    e2 = e21 * delta + e20;
    f2 = f22 * delta * delta + f21 * delta + f20;

    //obtain the coefficients for the 4th order equation
    //devided by Ea^n to make the variable dimensionless
    auto A4 = -4 * a2 * b1 * b2 * c1 + 4 * a1 * b2 * b2 * c1 + a2 * a2 * c1 * c1 +
              4 * a2 * b1 * b1 * c2 - 4 * a1 * b1 * b2 * c2 - 2 * a1 * a2 * c1 * c2 +
              a1 * a1 * c2 * c2;

    auto A3 = (-4 * a2 * b2 * c1 * d1 + 8 * a2 * b1 * c2 * d1 - 4 * a1 * b2 * c2 * d1 - 4 * a2 * b1 * c1 * d2 +
               8 * a1 * b2 * c1 * d2 - 4 * a1 * b1 * c2 * d2 - 8 * a2 * b1 * b2 * e1 + 8 * a1 * b2 * b2 * e1 +
               4 * a2 * a2 * c1 * e1 - 4 * a1 * a2 * c2 * e1 + 8 * a2 * b1 * b1 * e2 - 8 * a1 * b1 * b2 * e2 -
               4 * a1 * a2 * c1 * e2 + 4 * a1 * a1 * c2 * e2) / Ea;


    auto A2 = (4 * a2 * c2 * d1 * d1 - 4 * a2 * c1 * d1 * d2 - 4 * a1 * c2 * d1 * d2 + 4 * a1 * c1 * d2 * d2 -
               8 * a2 * b2 * d1 * e1 - 8 * a2 * b1 * d2 * e1 + 16 * a1 * b2 * d2 * e1 +
               4 * a2 * a2 * e1 * e1 + 16 * a2 * b1 * d1 * e2 - 8 * a1 * b2 * d1 * e2 -
               8 * a1 * b1 * d2 * e2 - 8 * a1 * a2 * e1 * e2 + 4 * a1 * a1 * e2 * e2 - 4 * a2 * b1 * b2 * f1 +
               4 * a1 * b2 * b2 * f1 + 2 * a2 * a2 * c1 * f1 - 2 * a1 * a2 * c2 * f1 +
               4 * a2 * b1 * b1 * f2 - 4 * a1 * b1 * b2 * f2 - 2 * a1 * a2 * c1 * f2 + 2 * a1 * a1 * c2 * f2) / Easq;

    auto A1 = (-8 * a2 * d1 * d2 * e1 + 8 * a1 * d2 * d2 * e1 + 8 * a2 * d1 * d1 * e2 - 8 * a1 * d1 * d2 * e2 -
               4 * a2 * b2 * d1 * f1 - 4 * a2 * b1 * d2 * f1 + 8 * a1 * b2 * d2 * f1 + 4 * a2 * a2 * e1 * f1 -
               4 * a1 * a2 * e2 * f1 + 8 * a2 * b1 * d1 * f2 - 4 * a1 * b2 * d1 * f2 - 4 * a1 * b1 * d2 * f2 -
               4 * a1 * a2 * e1 * f2 + 4 * a1 * a1 * e2 * f2) / (Easq * Ea);

    auto A0 = (-4 * a2 * d1 * d2 * f1 + 4 * a1 * d2 * d2 * f1 + a2 * a2 * f1 * f1 +
               4 * a2 * d1 * d1 * f2 - 4 * a1 * d1 * d2 * f2 - 2 * a1 * a2 * f1 * f2 +
               a1 * a1 * f2 * f2) / (Easq * Easq);

    auto A3sq = A3 * A3;

    auto B3 = 4 * A4;
    auto B2 = 3 * A3;
    auto B1 = 2 * A2;
    auto B0 = A1;

    auto C2 = -(A2 / 2 - 3 * A3sq / (16 * A4));
    auto C1 = -(3 * A1 / 4. - A2 * A3 / (8 * A4));
    auto C0 = -A0 + A1 * A3 / (16 * A4);

    auto D1 = -B1 - (B3 * C1 * C1 / C2 - B3 * C0 - B2 * C1) / C2;
    auto D0 = -B0 - B3 * C0 * C1 / (C2 * C2) + B2 * C0 / C2;

    auto E0 = -C0 - C2 * D0 * D0 / (D1 * D1) + C1 * D0 / D1;

    //find the coefficients for the leading term in the Sturm sequence
    auto t1 = A4;
    auto t2 = A4;
    auto t3 = C2;
    auto t4 = D1;
    auto t5 = E0;

    //The number of solutions depends on diffence of number of sign changes for x->Inf and x->-Inf
    auto nsol = signchange_n(t1, t2, t3, t4, t5) - signchange_p(t1, t2, t3, t4, t5);

    //Cannot have negative number of solutions, must be roundoff effect
    if (nsol < 0) nsol = 0;
    return nsol;
}

int Mt2::signchange_n(double t1, double t2, double t3, double t4, double t5)
{
    auto nsc = 0;
    if (t1 * t2 > 0) nsc++;
    if (t2 * t3 > 0) nsc++;
    if (t3 * t4 > 0) nsc++;
    if (t4 * t5 > 0) nsc++;
    return nsc;
}
int Mt2::signchange_p(double t1, double t2, double t3, double t4, double t5)
{
    auto nsc = 0;
    if (t1 * t2 < 0) nsc++;
    if (t2 * t3 < 0) nsc++;
    if (t3 * t4 < 0) nsc++;
    if (t4 * t5 < 0) nsc++;
    return nsc;
}

}//end namespace mt2_bisect
