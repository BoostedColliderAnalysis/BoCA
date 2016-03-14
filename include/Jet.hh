/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "PseudoJet.hh"
#include "InfoRecombiner.hh"
#include "JetInfo.hh"

namespace boca
{

class Jet : public PseudoJet
{

public:

    Jet();

    Jet(double x, double y, double z, double e);

    Jet(Momentum x, Momentum y, Momentum z, boca::Energy e);

    Jet(fastjet::PseudoJet const& jet);

    Jet(fastjet::PseudoJet const& jet, JetInfo const& info);

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

    LorentzVector<Momentum> Vector() const;

    float Bdt() const;

protected:

    void SetInfo(JetInfo const& user_info = JetInfo());

    void ResetInfo(JetInfo const& user_info);

private:


};

using Lepton = Jet;

using MissingEt = Jet;

std::vector<Jet> JetVector(std::vector<fastjet::PseudoJet> const& pseudo_jets);

std::vector<fastjet::PseudoJet> PseudoJetVector(std::vector<Jet> const& jets);

Jet Join(std::vector<Jet> const& jets);

template<typename Multiplet_1_, typename Multiplet_2_>
Jet MakeJet(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2) {
    return fastjet::join(multiplet_1.Jet(), multiplet_2.Jet(), InfoRecombiner());
}

template<typename Multiplet_>
Jet MakeJet(Jet const& jet, Multiplet_ const& multiplet) {
  return fastjet::join(jet, multiplet.Jet(), InfoRecombiner());
}

template<typename Multiplet_>
Jet MakeJet(Multiplet_ const& multiplet_1, Multiplet_ const& multiplet_2) {
  return fastjet::join(multiplet_1.Jet(), multiplet_2.Jet(), InfoRecombiner());
}

Jet Join(Jet const& jet_1, Jet const& jet_2);

}
