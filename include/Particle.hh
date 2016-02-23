/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "PseudoJet.hh"
#include "ParticleInfo.hh"

namespace boca
{

class Particle : public PseudoJet
{

public:

    Particle();

    Particle(double x, double y, double z, double e);

    Particle(fastjet::PseudoJet const& jet);

    Particle(TLorentzVector const& vector, Family const& family);

    Particle(exroot::GenParticle const& particle, int id);

    Particle(exroot::LHEFParticle const& particle, int id);

    ParticleInfo const& Info() const;

    ParticleInfo& Info();

private:

    void SetInfo(ParticleInfo const& user_info = ParticleInfo());

};

}
