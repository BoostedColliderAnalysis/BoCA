/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "boca/exroot/Classes.hh"
#include "boca/multiplets/Jet.hh"
#include "boca/multiplets/Particle.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Jet::Jet() :
    PseudoJet()
{
    SetInfo();
}

Jet::Jet(PseudoJet const& jet) :
    PseudoJet(jet)
{
    SetInfo();
}

Jet::Jet(fastjet::PseudoJet const& jet) :
    PseudoJet(jet)
{
    SetInfo();
}

Jet::Jet(fastjet::PseudoJet const& jet, JetInfo const& info) :
    PseudoJet(jet)
{
    SetInfo(info);
}

// Jet::Jet(double x, double y, double z, double e) :
//     PseudoJet(x, y, z, e)
// {
//     SetInfo();
// }

Jet::Jet(Momentum const& x, Momentum const& y, Momentum const& z, boca::Energy const& e) :
    PseudoJet(x, y, z, e)
{
    SetInfo();
}

Jet::Jet(LorentzVector<Momentum> const& lorentz_vector) :
    PseudoJet(lorentz_vector)
{
    SetInfo();
}

Jet::Jet(TLorentzVector const& lorentz_vector) :
    PseudoJet(lorentz_vector)
{
    SetInfo();
}

Jet::Jet(TLorentzVector const& lorentz_vector, ::delphes::Jet const& jet) :
    PseudoJet(lorentz_vector)
{
    DEBUG(Px(), Py(), Pz(), Mass());
    SetInfo(jet);
}

Jet::Jet(TLorentzVector const& lorentz_vector, Constituent const& constituent) :
    PseudoJet(lorentz_vector)
{
    DEBUG(Px(), Py(), Pz(), Mass());
    SetInfo(constituent);
}

Jet::Jet(TLorentzVector const& lorentz_vector, std::vector<Constituent> const& constituents) :
    PseudoJet(lorentz_vector)
{
    SetInfo(constituents);
}

Jet::Jet(TLorentzVector const& lorentz_vector, int charge) :
    PseudoJet(lorentz_vector)
{
    SetInfo(charge);
}

Jet::Jet(const exroot::Electron& electron) :
    PseudoJet(LorentzVector<Momentum>(electron))
{
    SetInfo(static_cast<int>(electron.Charge));
}

Jet::Jet(const exroot::GenJet& gen_jet) :
    PseudoJet(LorentzVector<Momentum>(gen_jet))
{
    SetInfo();
}

Jet::Jet(const exroot::Jet& jet) :
    PseudoJet(LorentzVector<Momentum>(jet))
{
    SetInfo();
}

Jet::Jet(const exroot::Muon& muon) :
    PseudoJet(LorentzVector<Momentum>(muon))
{
    SetInfo(static_cast<int>(muon.Charge));
}

Jet::Jet(const exroot::Photon& photon) :
    PseudoJet(LorentzVector<Momentum>(photon))
{
    SetInfo();
}

Jet::Jet(const exroot::Tau& tau) :
    PseudoJet(LorentzVector<Momentum>(tau))
{
    SetInfo();
}

// Jet::Jet(double const momentum[4]) :
//     PseudoJet(momentum[1], momentum[2], momentum[3], momentum[0])
// {
//     SetInfo();
// }

JetInfo const& Jet::Info() const
{
    if (!HasJetInfo()) {
        ERROR("No jet info");
        const_cast<Jet&>(*this).SetInfo();
    }
    return FastJet().user_info<JetInfo>();
}

JetInfo& Jet::Info()
{
    if (!HasJetInfo()) {
        ERROR("No jet info");
        SetInfo();
    }
    return static_cast<JetInfo&>(*FastJet().user_info_shared_ptr().get());
}

void Jet::SetInfo(JetInfo const& info)
{
    if (HasInfo()) ERROR("Jet has already a user info, which is beeing overwritten, this leads to data loss and leaking memory");
    FastJet().set_user_info(new JetInfo(info));
}

void Jet::ResetInfo(const JetInfo& info)
{
    if (!HasInfo()) ERROR("You can not reset a non existing user info");
    static_cast<JetInfo&>(*FastJet().user_info_shared_ptr().get()) = info;
}


std::vector< Jet > JetVector(std::vector< fastjet::PseudoJet > const& pseudo_jets)
{
    INFO0;
    return Transform(pseudo_jets, [](fastjet::PseudoJet const & pseudo_jet) -> Jet {
        return pseudo_jet;
    });
}

std::vector< fastjet::PseudoJet > PseudoJetVector(std::vector< Jet > const& jets)
{
    INFO0;
    return Transform(jets, [](Jet const & jet) -> fastjet::PseudoJet {
        return jet.FastJet();
    });
}

Jet Join(std::vector< Jet > const& jets)
{
    INFO0;
    return fastjet::join(PseudoJetVector(jets), InfoRecombiner());
}

Jet Join(Jet const& jet_1, Jet const& jet_2)
{
    return fastjet::join(jet_1.FastJet(), jet_2.FastJet(), InfoRecombiner());
}

Jet Join(Jet const& jet_1, Jet const& jet_2, Jet const& jet_3)
{
    return fastjet::join(jet_1.FastJet(), jet_2.FastJet(), jet_3.FastJet(), InfoRecombiner());
}

bool Jet::HasConsitutents() const
{
    return FastJet().has_constituents();
}


bool Jet::HasJetInfo() const
{
    return FastJet().has_user_info<JetInfo>();
}


void Jet::SetDelphesTags(const delphes::Jet& delphes_jet)
{
    Info().SetDelphesTags(delphes_jet);
}

std::vector< Jet > Jet::Constituents() const
{
    if (HasConsitutents()) return JetVector(FastJet().constituents());
    if (FastJet().has_pieces()) return JetVector(FastJet().pieces());
    return {*this};
}

double Jet::Bdt() const
{
    return Info().Bdt();
}

boca::Jet& Jet::operator+=(boca::Jet const& pseudo_jet)
{
    FastJet() += pseudo_jet.FastJet();
    return *this;
}

boca::Jet& Jet::operator-=(boca::Jet const& pseudo_jet)
{
    FastJet() -= pseudo_jet.FastJet();
    return *this;
}

boca::Jet& Jet::operator*=(double scalar)
{
    FastJet() *= scalar;
    return *this;
}

boca::Jet& Jet::operator/=(double scalar)
{
    FastJet() /= scalar;
    return *this;
}

boca::Jet& Jet::operator+=(boca::Particle const& pseudo_jet)
{
    FastJet() += pseudo_jet.FastJet();
    return *this;
}

boca::Jet& Jet::operator-=(boca::Particle const& pseudo_jet)
{
    FastJet() -= pseudo_jet.FastJet();
    return *this;
}

}

