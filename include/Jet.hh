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

//     using boca::PseudoJet::PseudoJet;

    Jet();

    Jet(double x, double y, double z, double e);

    Jet(fastjet::PseudoJet const& jet);

    Jet(LorentzVector<Momentum> const& lorentz_vector);

    Jet(TLorentzVector const& lorentz_vector);

    Jet(TLorentzVector const& lorentz_vector, ::delphes::Jet const& jet);

    Jet(TLorentzVector const& lorentz_vector, Constituent const& constituent);

    Jet(TLorentzVector const& lorentz_vector, std::vector<Constituent> const& constituents);

    Jet(TLorentzVector const& lorentz_vector, int charge);

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

    std::vector<Jet> Constituents() const;

private:

    void SetInfo(JetInfo const & user_info = JetInfo());

};

using Lepton  = Jet;

using MissingEt  = Jet;

std::vector<Jet> JetVector(std::vector<fastjet::PseudoJet> const& pseudo_jets);

std::vector<fastjet::PseudoJet> PseudoJetVector(std::vector<Jet> const& jets);

Jet Join(std::vector<Jet> const& jets);

}
