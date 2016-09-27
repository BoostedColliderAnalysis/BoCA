/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "boca/exroot/Classes.hh"
#include "boca/multiplets/Jet.hh"
#include "boca/multiplets/Particle.hh"
#include "boca/generic/Vector.hh"

// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Jet::Jet() :
    PseudoJet()
{
    DEBUG0;
    SetInfo();
}

Jet::Jet(PseudoJet const& jet) :
    PseudoJet(jet)
{
    DEBUG0;
//     SetInfo();
}

Jet::Jet(fastjet::PseudoJet const& jet) :
    PseudoJet(jet)
{
    DEBUG0;
//     SetInfo();
}

Jet::Jet(fastjet::PseudoJet const& jet, JetInfo const& info) :
    PseudoJet(jet)
{
    DEBUG0;
    SetInfo(info);
}

Jet::Jet(Momentum const& x, Momentum const& y, Momentum const& z, boca::Energy const& e) :
    PseudoJet(x, y, z, e)
{
    DEBUG(x, y, z, e);
    SetInfo();
}

Jet::Jet(boca::Vector3<Momentum> const& spatial, boca::Energy const& e) :
    PseudoJet(spatial, e)
{
    DEBUG(spatial.X(), spatial.Y(), spatial.Z(), e);
    SetInfo();
}

Jet::Jet(Vector2<Momentum> const& transversal, Momentum const& z, boca::Energy const& e) :
    PseudoJet(transversal, z, e)
{
    DEBUG(transversal.X(), transversal.Y(), z, e);
    SetInfo();
}

Jet::Jet(boca::LorentzVector<Momentum> const& lorentz_vector) :
    PseudoJet(lorentz_vector)
{
    DEBUG0;
    SetInfo();
}

Jet::Jet(TLorentzVector const& lorentz_vector) :
    PseudoJet(lorentz_vector)
{
    DEBUG0;
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
    DEBUG0;
    SetInfo(constituents);
}

Jet::Jet(TLorentzVector const& lorentz_vector, int charge) :
    PseudoJet(lorentz_vector)
{
    DEBUG0;
    SetInfo(charge);
}

Jet::Jet(const exroot::Electron& electron) :
    PseudoJet(boca::LorentzVector<Momentum>(electron))
{
    DEBUG0;
    SetInfo(static_cast<int>(electron.Charge));
}

Jet::Jet(const exroot::GenJet& gen_jet) :
    PseudoJet(boca::LorentzVector<Momentum>(gen_jet))
{
    DEBUG0;
    SetInfo();
}

Jet::Jet(const exroot::Jet& jet) :
    PseudoJet(boca::LorentzVector<Momentum>(jet))
{
    DEBUG0;
    SetInfo();
}

Jet::Jet(const exroot::Muon& muon) :
    PseudoJet(boca::LorentzVector<Momentum>(muon))
{
    DEBUG0;
    SetInfo(static_cast<int>(muon.Charge));
}

Jet::Jet(const exroot::Photon& photon) :
    PseudoJet(boca::LorentzVector<Momentum>(photon))
{
    DEBUG0;
    SetInfo();
}

Jet::Jet(const exroot::Tau& tau) :
    PseudoJet(boca::LorentzVector<Momentum>(tau))
{
    DEBUG0;
    SetInfo();
}

JetInfo const& Jet::Info() const
{
    DEBUG0;
    if (!HasJetInfo()) {
        ERROR("No jet info");
        const_cast<Jet&>(*this).SetInfo();
    }
    return FastJet().user_info<JetInfo>();
}

JetInfo& Jet::Info()
{
    DEBUG0;
    if (!HasJetInfo()) {
        ERROR("No jet info");
        SetInfo();
    }
    return static_cast<JetInfo&>(*FastJet().user_info_shared_ptr().get());
}

void Jet::SetInfo(JetInfo const& info)
{
    DEBUG0;
    if (HasInfo()) ERROR("Jet has already a user info, which is beeing overwritten, this leads to data loss and leaking memory");
    FastJet().set_user_info(new JetInfo(info));
}

void Jet::ResetInfo(const JetInfo& info)
{
    DEBUG0;
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
    DEBUG0;
    return fastjet::join(jet_1.FastJet(), jet_2.FastJet(), InfoRecombiner());
}

Jet Join(Jet const& jet_1, Jet const& jet_2, Jet const& jet_3)
{
    DEBUG0;
    return fastjet::join(jet_1.FastJet(), jet_2.FastJet(), jet_3.FastJet(), InfoRecombiner());
}

bool Jet::HasConsitutents() const
{
    DEBUG0;
    return FastJet().has_constituents();
}


bool Jet::HasJetInfo() const
{
    DEBUG0;
    return FastJet().has_user_info<JetInfo>();
}


void Jet::SetDelphesTags(const delphes::Jet& delphes_jet)
{
    DEBUG0;
    Info().SetDelphesTags(delphes_jet);
}

std::vector< Jet > Jet::Constituents() const
{
    DEBUG(HasConsitutents(),  FastJet().has_pieces());
    if (HasConsitutents()) return JetVector(FastJet().constituents());
    if (FastJet().has_pieces()) return JetVector(FastJet().pieces());
    return {*this};
}

double Jet::Bdt() const
{
    DEBUG0;
    return Info().Bdt();
}

boca::Jet& Jet::operator+=(boca::Jet const& jet)
{
    DEBUG0;
    FastJet() += jet.FastJet();
    return *this;
}

boca::Jet& Jet::operator-=(boca::Jet const& jet)
{
    DEBUG0;
    FastJet() -= jet.FastJet();
    return *this;
}

boca::Jet& Jet::operator*=(double scalar)
{
    DEBUG0;
    FastJet() *= scalar;
    return *this;
}

boca::Jet& Jet::operator/=(double scalar)
{
    DEBUG0;
    FastJet() /= scalar;
    return *this;
}

boca::Jet& Jet::operator+=(boca::Particle const& pseudo_jet)
{
    DEBUG0;
    FastJet() += pseudo_jet.FastJet();
    return *this;
}

boca::Jet& Jet::operator-=(boca::Particle const& pseudo_jet)
{
    DEBUG0;
    FastJet() -= pseudo_jet.FastJet();
    return *this;
}

}

