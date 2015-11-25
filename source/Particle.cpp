/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "Particle.hh"
#include "TLorentzVector.h"

namespace boca
{

Particle::Particle(TLorentzVector const& vector, Family const& family) : PseudoJet(vector), particle_info_(family) {}

Particle::Particle(exroot::GenParticle const& particle, int id) : PseudoJet(LorentzVector(particle)), particle_info_(id) {}

Particle::Particle(exroot::LHEFParticle const& particle, int id) : PseudoJet(LorentzVector(particle)), particle_info_(id) {}

ParticleInfo const& Particle::Info() const
{
    return particle_info_;
}

ParticleInfo& Particle::Info()
{
    return particle_info_;
}

}

