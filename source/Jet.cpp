/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "Jet.hh"
#include "Debug.hh"

namespace boca
{

Jet::Jet() : PseudoJet() {}

Jet::Jet(TLorentzVector const& vector, ::delphes::Jet const& jet) : PseudoJet(vector), jet_info_(jet) {}

Jet::Jet(TLorentzVector const& vector, Constituent const& constituent) : PseudoJet(vector), jet_info_(constituent) {}

Jet::Jet(fastjet::PseudoJet const& pseudo_jet, JetInfo const& jet_info) : PseudoJet(pseudo_jet), jet_info_(jet_info) {}

JetInfo const& Jet::Info() const
{
    return jet_info_;
}

JetInfo& Jet::Info()
{
    return jet_info_;
}

void Jet::SetInfo(const JetInfo& user_info)
{
    jet_info_ = user_info;
//       _user_info.reset(user_info);
}

std::vector< Jet > JetVector(std::vector< fastjet::PseudoJet > const& pseudo_jets)
{
    Error0;
    std::vector<Jet> jets;
    for (auto const & pseudo_jet : pseudo_jets) jets.push_back(Jet(pseudo_jet, pseudo_jet.user_info<JetInfo>()));
    return jets;
}

std::vector< fastjet::PseudoJet > PseudoJetVector(std::vector< Jet > const& jets)
{
    Error0;
    std::vector<fastjet::PseudoJet> pseudo_jets;
    for (auto const & jet : jets) {
        fastjet::PseudoJet pseudo_jet = jet;
        pseudo_jet.set_user_info(new JetInfo(jet.Info()));
        pseudo_jets.push_back(pseudo_jet);
    }
    return pseudo_jets;
}
Jet Join(const std::vector< Jet >& jets)
{
    Error0;
    std::vector<fastjet::PseudoJet> pseudo_jets = PseudoJetVector(jets);
    fastjet::PseudoJet pseudo_jet = fastjet::join(pseudo_jets, InfoRecombiner());
    return Jet(pseudo_jet, pseudo_jet.user_info<JetInfo>());
}

Jet operator+(const Jet& jet1, const Jet& jet2)
{
    //return Jet(jet1.four_mom()+jet2.four_mom());
    return Jet(jet1.px() + jet2.px(),
               jet1.py() + jet2.py(),
               jet1.pz() + jet2.pz(),
               jet1.E() + jet2.E());
}

Jet operator-(const Jet& jet1, const Jet& jet2)
{
    //return Jet(jet1.four_mom()-jet2.four_mom());
    return Jet(jet1.px() - jet2.px(),
               jet1.py() - jet2.py(),
               jet1.pz() - jet2.pz(),
               jet1.E() - jet2.E());
}

Jet operator*(double coeff, const Jet& jet)
{
    //return Jet(coeff*jet.four_mom());
    // the following code is hopefully more efficient
    Jet coeff_times_jet(jet);
    coeff_times_jet *= coeff;
    return coeff_times_jet;
}

Jet operator*(const Jet& jet, double coeff)
{
    return coeff * jet;
}

Jet operator/(const Jet& jet, double coeff)
{
    return (1.0 / coeff) * jet;
}

}

