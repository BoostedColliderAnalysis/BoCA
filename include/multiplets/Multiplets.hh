/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/math/constants/constants.hpp>
#include <boost/range/numeric.hpp>
#include "physics/Math.hh"
#include "Line2.hh"
#include "multiplets/Singlet.hh"
#include "DetectorGeometry.hh"

namespace boca
{

template<typename Multiplet_1_, typename Multiplet_2_>
Momentum DeltaPt(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    Momentum delta_pt  = multiplet_1.Pt() - multiplet_2.Pt();
    if (delta_pt != delta_pt) {
        std::cout << "Bad delta pt" << std::endl;
        return at_rest;
    }
    return delta_pt;
}

template<typename Multiplet_1_, typename Multiplet_2_>
Momentum Ht(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    return multiplet_1.Ht() + multiplet_2.Ht();
}

template<typename Multiplet_1_, typename Multiplet_2_>
Angle DeltaRap(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    Angle delta_rap = multiplet_1.Rap() - multiplet_2.Rap();
    if (boost::units::abs(delta_rap) > 100_rad) {
        std::cout << "Bad delta rap" << std::endl;
        return 0_rad;
    }
    return delta_rap;
}

template<typename Multiplet_1_, typename Multiplet_2_>
Angle DeltaPhi(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    return multiplet_1.DeltaPhiTo(multiplet_2);
}

template<typename Multiplet_1_, typename Multiplet_2_>
Angle DeltaR(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    Angle delta_r = multiplet_1.DeltaRTo(multiplet_2); //FIXME THIS HAS TO BE SWITCHED ON!!!!
    if (boost::units::abs(delta_r) > 100_rad) {
        std::cout << "Bad delta R" << std::endl;
        return 0_rad;
    }
    //         if (delta_r < DetectorGeometry::MinCellResolution()) delta_r = Singlet(Jet()).DeltaR();
    return delta_r;
}

template<typename Multiplet_1_, typename Multiplet_2_>
boca::Mass DeltaM(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    return multiplet_1.Mass() - multiplet_2.Mass();
}

template<typename Multiplet_1_, typename Multiplet_2_>
Momentum DeltaHt(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    return multiplet_1.Ht() - multiplet_2.Ht();
}

template<typename Multiplet_1_, typename Multiplet_2_>
double Rho(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2, boca::Jet const& jet)
{
    Angle delta_r = DeltaR(multiplet_1, multiplet_2);
    if (jet.Pt() < DetectorGeometry::MinCellPt() || delta_r < DetectorGeometry::MinCellResolution()) return 0;
    return jet.Mass() / jet.Pt() / delta_r * 2_rad;
}

template<typename Multiplet_1_, typename Multiplet_2_>
Angle Pull(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    Vector2<AngleSquare> pull = multiplet_1.ConstituentJet().PullVector();
    Vector2<Angle> ref = multiplet_1.DeltaTo(multiplet_2);
    AngleSquare pul_mag = pull.Mod();
    Angle ref_mag = ref.Mod();
    if (pul_mag == 0. * rad2 || ref_mag == 0_rad) return boost::math::constants::pi<double>() * rad;
    double cos = ref * pull / ref_mag / pul_mag;
    if (cos > 1) cos = 1;
    if (cos < -1) cos = -1;
    return std::acos(cos) * rad;
    //     return boost::units::acos(cos * boost::units::si::si_dimensionless);
}

template<typename Multiplet_>
Vector2<Angle> Point2(Vector2<Angle> const& point, Multiplet_ const& multiplet)
{
    Angle phi = multiplet.Phi();
    Vector2<Angle> point_2(multiplet.Rap(), phi);
    auto distance_1 = (point - point_2).Mod2();
    phi = Wrap(phi);
    Vector2<Angle> point_3(multiplet.Rap(), phi);
    auto distance_2 = (point - point_3).Mod2();
    if (distance_2 < distance_1) return point_3;
    return point_2;
}

using AngleSquareMomentum = ValueProduct<AngleSquare, Momentum>;

template<typename Multiplet_1_, typename Multiplet_2_>
double Dipolarity(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2, boca::Singlet const& singlet)
{
    if (singlet.Pt() == at_rest) return 0;
    if (!singlet.has_constituents()) return 0;
    Vector2<Angle> point_1(multiplet_1.Rap(), multiplet_1.Phi());
    auto point_2 = Point2(point_1, multiplet_2);
    Line2<Angle> line(point_1, point_2);
    auto dipolarity = boost::accumulate(singlet.Constituents(), at_rest * rad2, [&](AngleSquareMomentum & sum, Jet const & constituent) {
        return sum + constituent.Pt() * sqr(line.Distance(constituent));
    });
    auto delta_r = DeltaR(multiplet_1, multiplet_2);
    return delta_r == 0_rad ?  0 : dipolarity / singlet.Pt() / sqr(delta_r);
}

template<typename Multiplet_1_, typename Multiplet_2_>
int Charge(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    return multiplet_1.Charge() + multiplet_2.Charge();
}

}
