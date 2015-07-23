#include "Doublet.hh"
#include "Debug.hh"

namespace analysis {

fastjet::PseudoJet Doublet::SingletJet1() const
{
    return Multiplet1().Jet();
}

fastjet::PseudoJet Doublet::SingletJet2() const
{
    return Multiplet2().Jet();
}

Singlet& Doublet::Singlet1() const
{
    return Multiplet1();
}

Singlet& Doublet::Singlet2() const
{
    return Multiplet2();
}

std::vector<Kinematics> Doublet::Constituents(const fastjet::PseudoJet& jet, float jet_ratio, float theta, float shift) const
{
    Info("constituents", jet_ratio, theta);
    float Cut = 2. / jet_ratio;
    float Cut1 = 1. / jet_ratio;
    std::vector<Kinematics> Newconstituents;
    for (const auto& constituentJet : jet.constituents()) {
        if (jet.delta_R(constituentJet) > Cut)
            continue;
        if (jet.delta_R(constituentJet) < Cut1)
            continue;
        // Get constituent coordinates in Jet coordinates
        float ConstRap = constituentJet.rap() - jet.rap();
        float ConstPhi = analysis::DeltaPhi(constituentJet.phi_std(), jet.phi_std());
        if (ConstPhi > Cut)
            Error("phi", "too big");
        if (ConstRap > Cut)
            Error("eta", "too big");
        // rotate constituent according to other jet
        float ObservableRap = ConstRap * cos(theta) + ConstPhi * sin(theta);
        float ObservablePhi = ConstRap * sin(theta) - ConstPhi * cos(theta);
        // Scale according to Jet distance
        ObservableRap *= jet_ratio;
        ObservablePhi *= jet_ratio;
        // move jet to (+-1,0)
        ObservableRap -= shift;
        Debug("eta", ObservableRap);
        Kinematics constituent(constituentJet.pt(), ObservableRap, ObservablePhi);
        Newconstituents.emplace_back(constituent);
    }
    return Newconstituents;
}

float Doublet::ReferenceAngle(const fastjet::PseudoJet& NewJet, const fastjet::PseudoJet& ReferenceJet) const
{
    Info("ReferenceAngle");
    float Rap = NewJet.rap() - ReferenceJet.rap();
    float Phi = NewJet.delta_phi_to(ReferenceJet);
    return std::atan2(-Phi, -Rap);
}


float Doublet::PullAngle1() const
{
    Info("PullAngle1");
    float pull = Pull(SingletJet1());
    float reference_angle = ReferenceAngle(SingletJet1(), SingletJet2());
    return analysis::DeltaPhi(pull, reference_angle);
}

float Doublet::PullAngle2() const
{
    Info("PullAngle2");
    float pull = Pull(SingletJet2());
    float reference_angle = ReferenceAngle(SingletJet2(), SingletJet1());
    Debug("Pull", pull, reference_angle, analysis::DeltaPhi(pull, reference_angle));
    return analysis::DeltaPhi(pull, reference_angle);
}


float Doublet::Pull(const fastjet::PseudoJet& NewJet) const
{
    Info("Pull");
    float Rap = 0;
    float Phi = 0;
    for (const auto& constituent : NewJet.constituents()) {
        float NewDeltaRap = constituent.rap() - NewJet.rap();
        float NewDeltaPhi = analysis::DeltaPhi(constituent.phi_std(), NewJet.phi_std());
        float NewDeltaR = std::sqrt(std::pow(NewDeltaRap, 2) + std::pow(NewDeltaPhi, 2));
        float PullFactor = constituent.pt() / NewJet.pt() * NewDeltaR;
        //         float PullFactor = constituent.pt() / CandidateJet.pt() * constituent.delta_R(CandidateJet);
        Rap += (PullFactor * NewDeltaRap);
        Phi += (PullFactor * NewDeltaPhi);
    }
    return std::atan2(Phi, Rap);
}


std::vector<Kinematics> Doublet::Constituents() const
{
    Info("constituents");
    if (SingletJet1().constituents().empty() || SingletJet2().constituents().empty()) {
        Note("Not enough constituents", SingletJet1().constituents().size(), SingletJet2().constituents().size());
        //         return 0;
    }
    float Shift = 1;
    float CenterRap = (SingletJet1().rap() + SingletJet2().rap()) / 2;
    //     float CenterPhi = (Jet1.phi_std() + Jet2.phi_std()) / 2;
    float CenterPhi = analysis::DeltaPhi(SingletJet1().phi_std(), -SingletJet2().phi_std()) / 2;
    float Theta = atan2(analysis::DeltaPhi(SingletJet1().phi_std(), CenterPhi), SingletJet1().rap() - CenterRap);
    float Distance = SingletJet1().delta_R(SingletJet2());
    float SubJetRatio = 2. * Shift / Distance;
//     std::vector<Kinematics> constituentVectors1 = static_cast<DoubletPrivate *>(TagPrivate.get())->constituents(jet_1, SubJetRatio, Theta, -Shift);
    std::vector<Kinematics> constituents_1 = Constituents(SingletJet1(), SubJetRatio, Theta, -Shift);
//     std::vector<Kinematics> constituentVectors2 = static_cast<DoubletPrivate *>(TagPrivate.get())->constituents(jet_2, SubJetRatio, -Theta, Shift);
    std::vector<Kinematics> constituent_2 = Constituents(SingletJet2(), SubJetRatio, -Theta, Shift);
    constituents_1.insert(constituents_1.end(), constituent_2.begin(), constituent_2.end());
    return constituents_1;
}

}
