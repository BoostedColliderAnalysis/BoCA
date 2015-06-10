# include "Doublet.hh"

std::vector<analysis::Kinematics> analysis::Doublet::constituents(const fastjet::PseudoJet &jet, const float jet_ratio, const float theta, const float shift) const
{
    Print(kInformation, "constituents", jet_ratio, theta);
    const float Cut = 2. / jet_ratio;
    const float Cut1 = 1. / jet_ratio;
    std::vector<Kinematics> Newconstituents;
    for (const auto & constituentJet : jet.constituents()) {
        if (jet.delta_R(constituentJet) > Cut) continue;
        if (jet.delta_R(constituentJet) < Cut1) continue;
        // Get constituent coordinates in Jet coordinates
        const float ConstRap = constituentJet.rap() - jet.rap();
        const float ConstPhi = analysis::DeltaPhi(constituentJet.phi_std(), jet.phi_std());
        if (ConstPhi > Cut) Print(kError, "phi", "too big");
        if (ConstRap > Cut) Print(kError, "eta", "too big");
        // rotate constituent according to other jet
        float ObservableRap = ConstRap * cos(theta) + ConstPhi * sin(theta);
        float ObservablePhi = ConstRap * sin(theta) - ConstPhi * cos(theta);
        // Scale according to Jet distance
        ObservableRap *= jet_ratio;
        ObservablePhi *= jet_ratio;
        // move jet to (+-1,0)
        ObservableRap -= shift;
        Print(kDebug, "eta", ObservableRap);
        Kinematics constituent(constituentJet.pt(), ObservableRap, ObservablePhi);
        Newconstituents.emplace_back(constituent);
    }
    return Newconstituents;
}

fastjet::PseudoJet analysis::Doublet::SingletJet1()const
{
    return multiplet_1_.Jet();
}

fastjet::PseudoJet analysis::Doublet::SingletJet2()const
{
    return multiplet_2_.Jet();
}

analysis::Singlet analysis::Doublet::Singlet1()const
{
    return multiplet_1_;
}

analysis::Singlet analysis::Doublet::Singlet2()const
{
    return multiplet_2_;
}

// bool analysis::Doublet::Overlap() const
// {
//     return Singlet1().Overlap(Singlet2());
// }
//
// bool analysis::Doublet::Overlap(const fastjet::PseudoJet &jet) const
// {
//     return (Singlet1().Overlap(jet) | Singlet2().Overlap(jet));
// }

void analysis::Doublet::SetSinglets(const fastjet::PseudoJet &singlet_1, const fastjet::PseudoJet &singlet_2)
{
    Print(kInformation, "Constructor");
    multiplet_1_ = singlet_1;
    multiplet_2_ = singlet_2;
    SetBdt(SubMultiplet1().Bdt(), SubMultiplet2().Bdt());
}

void analysis::Doublet::SetSinglets(const fastjet::PseudoJet &singlet)
{
    Print(kInformation, "Constructor");
    multiplet_1_ = singlet / 2;
    multiplet_2_ = singlet / 2;
    SetDegenerate();
    if (singlet.has_user_info<JetInfo>() && singlet.user_info<JetInfo>().Bdt() != initial_value()) SetBdt(singlet.user_info<JetInfo>().Bdt());
    else SetBdt(0);
    if (singlet.has_user_info<JetInfo>() && singlet.user_info<JetInfo>().Tag() != initial_value()) SetTag(singlet.user_info<JetInfo>().Tag());
}

float analysis::Doublet::ReferenceAngle(const fastjet::PseudoJet &NewJet, const fastjet::PseudoJet &ReferenceJet) const
{
    Print(kInformation, "ReferenceAngle");
    const float Rap = NewJet.rap() - ReferenceJet.rap();
    const float Phi = NewJet.delta_phi_to(ReferenceJet);
    return std::atan2(-Phi, -Rap);
}


float analysis::Doublet::PullAngle1() const
{
    Print(kInformation, "PullAngle1");
    const float pull = Pull(SingletJet1());
    const float reference_angle = ReferenceAngle(SingletJet1(), SingletJet2());
    return analysis::DeltaPhi(pull, reference_angle);
}

float analysis::Doublet::PullAngle2() const
{
    Print(kInformation, "PullAngle2");
    const float pull = Pull(SingletJet2());
    const float reference_angle = ReferenceAngle(SingletJet2(), SingletJet1());
    Print(kDebug, "Pull", pull, reference_angle, analysis::DeltaPhi(pull, reference_angle));
    return analysis::DeltaPhi(pull, reference_angle);
}


float analysis::Doublet::Pull(const fastjet::PseudoJet &NewJet) const
{
    Print(kInformation, "Pull");
    float Rap = 0;
    float Phi = 0;
    for (const auto & constituent : NewJet.constituents()) {
        const float NewDeltaRap = constituent.rap() - NewJet.rap();
        const float NewDeltaPhi = analysis::DeltaPhi(constituent.phi_std(), NewJet.phi_std());
        const float NewDeltaR = std::sqrt(std::pow(NewDeltaRap, 2) + std::pow(NewDeltaPhi, 2));
        const float PullFactor = constituent.pt() / NewJet.pt() * NewDeltaR;
        //         const float PullFactor = constituent.pt() / CandidateJet.pt() * constituent.delta_R(CandidateJet);
        Rap += (PullFactor * NewDeltaRap);
        Phi += (PullFactor * NewDeltaPhi);
    }
    return std::atan2(Phi, Rap);
}


std::vector<analysis::Kinematics> analysis::Doublet::constituents() const
{
    Print(kInformation, "constituents");
    if (SingletJet1().constituents().empty() || SingletJet2().constituents().empty()) {
        Print(kNotification, "Not enough constituents", SingletJet1().constituents().size(), SingletJet2().constituents().size());
        //         return 0;
    }
    const float Shift = 1;
    const float CenterRap = (SingletJet1().rap() + SingletJet2().rap()) / 2;
    //     const float CenterPhi = (Jet1.phi_std() + Jet2.phi_std()) / 2;
    const float CenterPhi = analysis::DeltaPhi(SingletJet1().phi_std(), -SingletJet2().phi_std()) / 2;
    const float Theta = atan2(analysis::DeltaPhi(SingletJet1().phi_std(), CenterPhi), SingletJet1().rap() - CenterRap);
    const float Distance = SingletJet1().delta_R(SingletJet2());
    const float SubJetRatio = 2. * Shift / Distance;
//     std::vector<Kinematics> constituentVectors1 = static_cast<DoubletPrivate *>(TagPrivate.get())->constituents(jet_1, SubJetRatio, Theta, -Shift);
    std::vector<Kinematics> constituents_1 = constituents(SingletJet1(), SubJetRatio, Theta, -Shift);
//     std::vector<Kinematics> constituentVectors2 = static_cast<DoubletPrivate *>(TagPrivate.get())->constituents(jet_2, SubJetRatio, -Theta, Shift);
    std::vector<Kinematics> constituent_2 = constituents(SingletJet2(), SubJetRatio, -Theta, Shift);
    constituents_1.insert(constituents_1.end(), constituent_2.begin(), constituent_2.end());
    return constituents_1;
}
