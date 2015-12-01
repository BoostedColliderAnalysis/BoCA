/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "Jet.hh"
#include "InfoRecombiner.hh"
#include "Exception.hh"
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

Jet::Jet(const exroot::Electron& electron) : PseudoJet(LorentzVector<Momentum>(electron))
{
    SetInfo();
}

Jet::Jet(const exroot::GenJet& gen_jet) : PseudoJet(LorentzVector<Momentum>(gen_jet))
{
    SetInfo();
}

Jet::Jet(const exroot::Jet& jet) : PseudoJet(LorentzVector<Momentum>(jet))
{
    SetInfo();
}

Jet::Jet(const exroot::Muon& muon) : PseudoJet(LorentzVector<Momentum>(muon))
{
    SetInfo();
}

Jet::Jet(const exroot::Photon& photon) : PseudoJet(LorentzVector<Momentum>(photon))
{
    SetInfo();
}

Jet::Jet(const exroot::Tau& tau) : PseudoJet(LorentzVector<Momentum>(tau))
{
    SetInfo();
}

Jet::Jet(double const Momentum[4]) : PseudoJet(Momentum[1], Momentum[2], Momentum[3], Momentum[0])
{
    SetInfo();
}

JetInfo const& Jet::Info() const
{
    if (!has_user_info<JetInfo>()) {
        Error("No jet info");
        throw Empty();
//         SetInfo();
    }
    return user_info<JetInfo>();
}

JetInfo& Jet::Info()
{
    if (!has_user_info<JetInfo>()) {
        Error("No jet info");
        SetInfo();
    }
    return static_cast<JetInfo&>(*user_info_shared_ptr().get());
}

void Jet::SetInfo(JetInfo const& user_info)
{
    if (has_user_info<JetInfo>()) Error("Jet has already a user info, which gets overwritten: data loss and memory leak");
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
std::vector< Jet > Jet::Constituents() const
{
    if (has_constituents()) return JetVector(constituents());
    else return {};
}

}

