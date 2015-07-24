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
    Info(jet_ratio, theta);
    float cut = 2. / jet_ratio;
    float cut_1 = 1. / jet_ratio;
    std::vector<Kinematics> constituents;
    for (const auto& constituent : jet.constituents()) {
        if (jet.delta_R(constituent) > cut) continue;
        if (jet.delta_R(constituent) < cut_1) continue;
        // Get constituent coordinates in Jet coordinates
        float const_rap = constituent.rap() - jet.rap();
        float const_phi = analysis::DeltaPhi(constituent.phi_std(), jet.phi_std());
        if (const_phi > cut) Error("phi", "too big");
        if (const_rap > cut) Error("eta", "too big");
        // rotate constituent according to other jet
        float rap = const_rap * cos(theta) + const_phi * sin(theta);
        float phi = const_rap * sin(theta) - const_phi * cos(theta);
        // Scale according to Jet distance
        rap *= jet_ratio;
        phi *= jet_ratio;
        // move jet to (+-1,0)
        rap -= shift;
        Debug(rap);
        Kinematics final_constituent(constituent.pt(), rap, phi);
        constituents.emplace_back(final_constituent);
    }
    return constituents;
}

float Doublet::ReferenceAngle(const fastjet::PseudoJet& jet, const fastjet::PseudoJet& reference) const
{
    Info();
    float rap = jet.rap() - reference.rap();
    float phi = jet.delta_phi_to(reference);
    return std::atan2(-phi, -rap);
}


float Doublet::PullAngle1() const
{
    Info();
    float pull = Pull(SingletJet1());
    float reference_angle = ReferenceAngle(SingletJet1(), SingletJet2());
    return analysis::DeltaPhi(pull, reference_angle);
}

float Doublet::PullAngle2() const
{
    Info();
    float pull = Pull(SingletJet2());
    float reference_angle = ReferenceAngle(SingletJet2(), SingletJet1());
    Debug(pull, reference_angle, analysis::DeltaPhi(pull, reference_angle));
    return analysis::DeltaPhi(pull, reference_angle);
}


float Doublet::Pull(const fastjet::PseudoJet& jet) const
{
    Info();
    float rap = 0;
    float phi = 0;
    for (const auto& constituent : jet.constituents()) {
        float delta_rap = constituent.rap() - jet.rap();
        float delta_phi = constituent.delta_phi_to(jet);
//         float delta_r = std::sqrt(std::pow(delta_rap, 2) + std::pow(delta_phi, 2));
        float factor = constituent.pt() / jet.pt() * constituent.delta_R(jet);
        //         float PullFactor = constituent.pt() / CandidateJet.pt() * constituent.delta_R(CandidateJet);
        rap += factor * delta_rap;
        phi += factor * delta_phi;
    }
    return std::atan2(phi, rap);
}


std::vector<Kinematics> Doublet::Constituents() const
{
    Info();
    if (SingletJet1().constituents().empty() || SingletJet2().constituents().empty()) {
        Note("Not enough constituents", SingletJet1().constituents().size(), SingletJet2().constituents().size());
        //         return 0;
    }
    float shift = 1;
    float rap = (SingletJet1().rap() + SingletJet2().rap()) / 2;
    //     float CenterPhi = (Jet1.phi_std() + Jet2.phi_std()) / 2;
    float phi = analysis::DeltaPhi(SingletJet1().phi_std(), -SingletJet2().phi_std()) / 2;
    float theta = atan2(analysis::DeltaPhi(SingletJet1().phi_std(), phi), SingletJet1().rap() - rap);
    float distance = SingletJet1().delta_R(SingletJet2());
    float ratio = 2. * shift / distance;
//     std::vector<Kinematics> constituentVectors1 = static_cast<DoubletPrivate *>(TagPrivate.get())->constituents(jet_1, SubJetRatio, Theta, -Shift);
    std::vector<Kinematics> constituents = Constituents(SingletJet1(), ratio, theta, -shift);
//     std::vector<Kinematics> constituentVectors2 = static_cast<DoubletPrivate *>(TagPrivate.get())->constituents(jet_2, SubJetRatio, -Theta, Shift);
    std::vector<Kinematics> constituent_2 = Constituents(SingletJet2(), ratio, -theta, shift);
    constituents.insert(constituents.end(), constituent_2.begin(), constituent_2.end());
    return constituents;
}

}
