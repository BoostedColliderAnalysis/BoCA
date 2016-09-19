/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/fastjet/PseudoJet.hh"
#include "boca/multiplets/ParticleInfo.hh"

namespace boca
{

class Particle : public PseudoJet
            , public boost::addable<Particle>
            , public boost::subtractable<Particle>
            , public boost::multipliable<Particle, double>
            , public boost::dividable<Particle, double>
{

public:

    Particle();

//     Particle(double x, double y, double z, double e);

    Particle(fastjet::PseudoJet const& jet);

    Particle(TLorentzVector const& vector, Family const& family);

    Particle(exroot::GenParticle const& particle, int id);

    Particle(exroot::LHEFParticle const& particle, int id);

    ParticleInfo const& Info() const;

    ParticleInfo& Info();

    bool HasParticleInfo() const;

    /**
    * @name Operators
    * @{
    */

    /**
    * @brief add the other jet's momentum to this jet
    */
    Particle& operator+=(Particle const& pseudo_jet);

    /**
    * @brief subtract the other jet's momentum from this jet
    */
    Particle& operator-=(const Particle &pseudo_jet);

    /**
    * @brief multiply the jet's momentum by the coefficient
    */
    Particle& operator*=(double scalar);

    /**
    * @brief divide the jet's momentum by the coefficient
    */
    Particle& operator/=(double scalar);

    //@}

private:

    void SetInfo(ParticleInfo const& info = ParticleInfo());

};

std::vector<Particle> ParticleVector(std::vector<fastjet::PseudoJet> const& pseudo_jets);

}
