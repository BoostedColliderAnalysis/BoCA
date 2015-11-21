/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "Jet.hh"
#include "InfoRecombiner.hh"
#include "Debug.hh"

namespace boca
{

Jet::Jet() : PseudoJet()
{
    SetInfo();
}

Jet::Jet(TLorentzVector const& vector, ::delphes::Jet const& jet) : PseudoJet(vector)
{
    SetInfo(jet);
}

Jet::Jet(TLorentzVector const& vector, Constituent const& constituent) : PseudoJet(vector)
{
    SetInfo(constituent);
}

Jet::Jet(TLorentzVector const& vector, int charge) : PseudoJet(vector)
{
    SetInfo(charge);
}

JetInfo const& Jet::Info() const
{
    if (has_user_info<JetInfo>()) return user_info<JetInfo>();
}

JetInfo& Jet::Info()
{
    if (has_user_info<JetInfo>()) return static_cast<JetInfo&>(*user_info_shared_ptr().get());
}

void Jet::SetInfo(JetInfo const& user_info)
{
    if (has_user_info<JetInfo>()) Error("Has already a user info");
    set_user_info(new JetInfo(user_info));
}

std::vector< Jet > JetVector(std::vector< fastjet::PseudoJet > const& pseudo_jets)
{
    Info0;
    std::vector<Jet> jets;
    for (auto const & pseudo_jet : pseudo_jets) jets.emplace_back(pseudo_jet);
    return jets;
}

std::vector< fastjet::PseudoJet > PseudoJetVector(std::vector< Jet > const& jets)
{
    Info0;
    std::vector<fastjet::PseudoJet> pseudo_jets;
    for (auto const & jet : jets) pseudo_jets.emplace_back(jet);
    return pseudo_jets;
}

Jet Join(const std::vector< Jet >& jets)
{
    Info0;
    return fastjet::join(PseudoJetVector(jets), InfoRecombiner());
}

}

