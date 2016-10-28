/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "TLorentzVector.h"
#include "boca/fastjet/Particle.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Particle::Particle() :
    PseudoJet()
{
    SetInfo();
}

Particle::Particle(fastjet::PseudoJet const& particle) :
    PseudoJet(particle)
{}

// Particle::Particle(double x, double y, double z, double e) :
//     PseudoJet(x, y, z, e)
// {
//     SetInfo();
// }

Particle::Particle(TLorentzVector const& vector, Family const& family) :
    PseudoJet(vector)
{
    SetInfo(family);
}

Particle::Particle(exroot::GenParticle const& particle, int id) :
    PseudoJet(boca::LorentzVector<Momentum>(particle))
{
    SetInfo(Family(id, Relative::particle));
}

Particle::Particle(exroot::LHEFParticle const& particle, int id) :
    PseudoJet(boca::LorentzVector<Momentum>(particle))
{
    SetInfo(Family(id, Relative::particle));
}

ParticleInfo const& Particle::Info() const
{
    if (!HasParticleInfo()) {
        ERROR("No particle info");
        const_cast<Particle&>(*this).SetInfo();
    }
    return FastJet().user_info<ParticleInfo>();
}

ParticleInfo& Particle::Info()
{
    if (!HasParticleInfo()) {
        ERROR("No particle info");
        SetInfo();
    }
    return static_cast<ParticleInfo&>(*FastJet().user_info_shared_ptr().get());
}

void Particle::SetInfo(ParticleInfo const& info)
{
    if (HasInfo()) ERROR("Particle has already a user info, which gets overwritten: data loss and memory leak");
    FastJet().set_user_info(new ParticleInfo(info));
}

std::vector< Particle > ParticleVector(std::vector< fastjet::PseudoJet > const& pseudo_jets)
{
    INFO0;
    return Transform(pseudo_jets, [](fastjet::PseudoJet const & pseudo_jet) -> Particle {
        return pseudo_jet;
    });
}

bool Particle::HasParticleInfo() const
{
    return FastJet().has_user_info<ParticleInfo>();
}


boca::Particle& Particle::operator+=(boca::Particle const& pseudo_jet)
{
    FastJet() += pseudo_jet.FastJet();
    return *this;
}

boca::Particle& Particle::operator-=(boca::Particle const& pseudo_jet)
{
    FastJet() -= pseudo_jet.FastJet();
    return *this;
}

boca::Particle& Particle::operator*=(double scalar)
{
    FastJet() *= scalar;
    return *this;
}

boca::Particle& Particle::operator/=(double scalar)
{
    FastJet() /= scalar;
    return *this;
}

}

