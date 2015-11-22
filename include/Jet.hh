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

    Jet(TLorentzVector const& vector, int charge);

    Jet(double const Momentum[4]) : PseudoJet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]){}

    JetInfo const& Info() const;

    JetInfo& Info();

    void SetDelphesTags(::delphes::Jet const& delphes_jet){
      Info().SetDelphesTags(delphes_jet);
    }

    void SetInfo(JetInfo const & user_info = JetInfo());

private:

};

using Lepton  = Jet;

std::vector<Jet> JetVector(std::vector<fastjet::PseudoJet> const& pseudo_jets);

std::vector<fastjet::PseudoJet> PseudoJetVector(std::vector<Jet> const& jets);

Jet Join(std::vector<Jet> const& jets);

}
