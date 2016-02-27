/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "TLorentzVector.h"
#include "Particle.hh"
#include "Debug.hh"

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

Particle::Particle(double x, double y, double z, double e) :
    PseudoJet(x, y, z, e)
{
    SetInfo();
}

Particle::Particle(TLorentzVector const& vector, Family const& family) :
    PseudoJet(vector)
{
    SetInfo(family);
}

Particle::Particle(exroot::GenParticle const& particle, int id) :
    PseudoJet(LorentzVector<Momentum>(particle))
{
    SetInfo(Family(id, Relative::particle));
}

Particle::Particle(exroot::LHEFParticle const& particle, int id) :
    PseudoJet(LorentzVector<Momentum>(particle))
{
    SetInfo(Family(id, Relative::particle));
}

ParticleInfo const& Particle::Info() const
{
    if (!has_user_info<ParticleInfo>()) {
        ERROR("No particle info");
        const_cast<Particle&>(*this).SetInfo();
    }
    return user_info<ParticleInfo>();
}

ParticleInfo& Particle::Info()
{
    if (!has_user_info<ParticleInfo>()) {
        ERROR("No particle info");
        SetInfo();
    }
    return static_cast<ParticleInfo&>(*user_info_shared_ptr().get());
}

void Particle::SetInfo(ParticleInfo const& user_info)
{
    if (has_user_info()) ERROR("Particle has already a user info, which gets overwritten: data loss and memory leak");
    set_user_info(new ParticleInfo(user_info));
}

std::vector< Particle > ParticleVector(std::vector< fastjet::PseudoJet > const& pseudo_jets)
{
    INFO0;
    std::vector<Particle> jets;
    for (auto const & pseudo_jet : pseudo_jets) jets.emplace_back(pseudo_jet);
    return jets;
}

}

