#include "Multiplet.hh"

#include "InfoRecombiner.hh"
#include "JetInfo.hh"
#include "Vector.hh"
#include "Math.hh"
#include "Line2.hh"
#include "Debug.hh"

namespace analysis
{

Vector2 Multiplet::Pull() const
{
    Error("do not end up here");
    return Vector2();
};

fastjet::PseudoJet Multiplet::Jet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2) const
{
    analysis::Jets constituents;
    if (jet_1.has_user_info() && jet_1.user_info<JetInfo>().SubStructure() && jet_1.has_constituents()) constituents = jet_1.constituents();
    else constituents.emplace_back(jet_1);
    if (jet_2.has_user_info() && jet_2.user_info<JetInfo>().SubStructure() && jet_2.has_constituents()) constituents = Join(constituents, jet_2.constituents());
    else constituents.emplace_back(jet_2);

    fastjet::PseudoJet jet = fastjet::join(constituents, InfoRecombiner());
//     Check(int((jet_1 + jet_2).m()) == int(jet.m()), jet.m(), (jet_1 + jet_2).m(), jet_1.m(), jet_2.m());
    return jet;
}

float Multiplet::DeltaPt(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    float delta_pt  = multiplets_1.Jet().pt() - multiplets_2.Jet().pt();
    if(delta_pt != delta_pt) return 0;
    return delta_pt;
}

float Multiplet::Ht(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    return multiplets_1.Ht() + multiplets_2.Ht();
}

float Multiplet::DeltaRap(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    float delta_rap = multiplets_1.Jet().rap() - multiplets_2.Jet().rap();
    if (std::abs(delta_rap) > 100) return 0;
    return delta_rap;
}

float Multiplet::DeltaPhi(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    return multiplets_1.Jet().delta_phi_to(multiplets_2.Jet());
}

float Multiplet::DeltaR(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    float delta_r = multiplets_1.Jet().delta_R(multiplets_2.Jet());
    if (std::abs(delta_r) > 100) delta_r = 0;
//         if (delta_r < DetectorGeometry::MinCellResolution()) delta_r = Singlet(Jet()).DeltaR();
    return delta_r;
}

float Multiplet::DeltaM(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    return multiplets_1.Jet().m() - multiplets_2.Jet().m();
}

float Multiplet::DeltaHt(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    return multiplets_1.Ht() - multiplets_2.Ht();
}

float Multiplet::Rho(const MultipletBase& jet_1, const MultipletBase& jet_2) const
{
    if (Jet(jet_1.Jet(), jet_2.Jet()).pt() < DetectorGeometry::MinCellPt() || DeltaR(jet_1, jet_2) < DetectorGeometry::MinCellResolution()) return 0;
    return Jet().m() / Jet().pt() / DeltaR(jet_1, jet_2) * 2;
}

float Multiplet::Pull(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{  
/*  Vector2 pull = multiplets_1.singlet().Pull();
  Vector2 reference = multiplets_1.Reference(multiplets_2.singlet().Jet(),multiplets_1.singlet().Jet()); */  
  Vector2 pull = multiplets_1.singlet().Pull();
  fastjet::PseudoJet jet = multiplets_2.Jet();
  if (jet == fastjet::PseudoJet::PseudoJet()) return M_PI;
  Vector2 reference = multiplets_1.Reference(jet);    
  float pull_abs = pull.Mod();
  float reference_abs = reference.Mod();
  if (pull_abs == 0|| reference_abs == 0)  return M_PI;
  float cos = pull * reference / pull_abs / reference_abs;
  if (cos < -1 ) cos = -1;
  if (cos > 1 ) cos = 1;
//   return cos;
  return std::acos(cos); 
}

float Multiplet::PullDifference(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{  
  return Pull(multiplets_1, multiplets_2) + Pull(multiplets_2, multiplets_1);;
}

float Multiplet::PullSum(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
  return Pull(multiplets_2, multiplets_1) - Pull(multiplets_1, multiplets_2);
}

float Multiplet::Dipolarity(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    fastjet::PseudoJet jet = Jet(multiplets_1.Jet(), multiplets_2.Jet());
    if (jet.pt() == 0) return 0;
    if (!jet.has_constituents()) return 0;
    
    float delta_r = DeltaR(multiplets_1, multiplets_2);
    if (delta_r == 0) return 0;
    
    
    Vector2 point_1(multiplets_1.Jet().rap(), multiplets_1.Jet().phi_std());
    double phi = multiplets_2.Jet().phi_std();
    Vector2 point_2(multiplets_2.Jet().rap(), phi);    
    float distance_1 = (point_1 - point_2).Mod();
    if (phi < 0) phi += 2 * M_PI;
    else  phi -= 2 * M_PI;    
    Vector2 point_3(multiplets_2.Jet().rap(), phi);  
    float distance_2 = (point_1 - point_3).Mod();
    if (distance_2 < distance_1) point_2 = point_3;
    
    float dipolarity = 0;
    Line2 line(point_1, point_2);
    for (const auto & constituent : jet.constituents()) {
        float phi = constituent.phi_std();
        float distance_1 = line.DistanceToSegment(Vector2(constituent.rap(), phi)); 
        if (phi < 0) phi += 2 * M_PI;
        else  phi -= 2 * M_PI;
        float distance_2 =  line.DistanceToSegment(Vector2(constituent.rap(), phi)); 
        float distance = std::min(distance_1, distance_2);
        dipolarity += constituent.pt() * sqr(distance);
    }
    return dipolarity / jet.pt() / sqr(delta_r);
}

float Multiplet::Distance(const Vector2& point_1, const Vector2& point_2, const Vector2& point_0, float delta_r) const
{    
    return std::abs((point_2.Y() - point_1.Y()) * point_0.X() - (point_2.X() - point_1.X()) * point_0.Y() + point_2.X() * point_1.Y() - point_2.Y() * point_1.X()) / delta_r;
}
int Multiplet::Charge(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
    return sgn(multiplets_1.Charge() + multiplets_2.Charge());
}

float Multiplet::BottomBdt(const MultipletBase& multiplets_1, const MultipletBase& multiplets_2) const
{
   return (multiplets_1.BottomBdt() + multiplets_2.BottomBdt()) / 2 ;
}


}
