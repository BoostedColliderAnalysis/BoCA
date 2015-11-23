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

Jet::Jet(TLorentzVector const& vector, std::vector<Constituent> const& constituents) : PseudoJet(vector)
{
  SetInfo(constituents);
}

Jet::Jet(TLorentzVector const& vector, int charge) : PseudoJet(vector)
{
    SetInfo(charge);
}

Jet::Jet(const exroot::Electron& electron) : PseudoJet(LorentzVector(electron))
{
    SetInfo();
}

Jet::Jet(const exroot::GenJet& gen_jet) : PseudoJet(LorentzVector(gen_jet))
{
    SetInfo();
}

Jet::Jet(const exroot::Jet& jet) : PseudoJet(LorentzVector(jet))
{
    SetInfo();
}

Jet::Jet(const exroot::Muon& muon) : PseudoJet(LorentzVector(muon))
{
    SetInfo();
}

Jet::Jet(const exroot::Photon& photon) : PseudoJet(LorentzVector(photon))
{
    SetInfo();
}

Jet::Jet(const exroot::Tau& tau) : PseudoJet(LorentzVector(tau))
{
    SetInfo();
}

Jet::Jet(double const Momentum[4]) : PseudoJet(Momentum[1], Momentum[2], Momentum[3], Momentum[0])
{
    SetInfo();
}

JetInfo const& Jet::Info() const
{
    if (has_user_info<JetInfo>()) return user_info<JetInfo>();
    Error("No jet info");
}

JetInfo& Jet::Info()
{
    if (has_user_info<JetInfo>()) return static_cast<JetInfo&>(*user_info_shared_ptr().get());
    Error("No jet info");
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

Jet Join(std::vector< Jet > const& jets)
{
    Info0;
    return fastjet::join(PseudoJetVector(jets), InfoRecombiner());
}

void Jet::SetDelphesTags(const delphes::Jet& delphes_jet)
{
    Info().SetDelphesTags(delphes_jet);
}

}

