/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "PseudoJet.hh"
#include "JetInfo.hh"

namespace boca
{

class Jet : public PseudoJet
{

public:

    using boca::PseudoJet::PseudoJet;

    Jet();

    Jet(TLorentzVector const& vector, ::delphes::Jet const& jet);

    Jet(TLorentzVector const& vector, Constituent const& constituent);

    Jet(TLorentzVector const& vector, std::vector<Constituent> const& constituents);

    Jet(TLorentzVector const& vector, int charge);

    Jet(exroot::Electron const& electron);

    Jet(exroot::GenJet const& gen_jet);

    Jet(exroot::Jet const& jet);

    Jet(exroot::Muon const& muon);

    Jet(exroot::Photon const& photon);

    Jet(exroot::Tau const& tau);

    Jet(double const Momentum[4]);

    JetInfo const& Info() const;

    JetInfo& Info();

    void SetDelphesTags(::delphes::Jet const& delphes_jet);

private:

    void SetInfo(JetInfo const & user_info = JetInfo());

};

using Lepton  = Jet;
using MissingEt  = Jet;

std::vector<Jet> JetVector(std::vector<fastjet::PseudoJet> const& pseudo_jets);

std::vector<fastjet::PseudoJet> PseudoJetVector(std::vector<Jet> const& jets);

Jet Join(std::vector<Jet> const& jets);

}
