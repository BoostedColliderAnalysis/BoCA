/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Particle.hh"
#include "Types.hh"

namespace boca {

Particle::Particle(int id)
{
    id_ = id;
}
// Particle::Particle(Id id)
// {
//     id_ = to_int(id);
// }
//
// Particle::Particle(Id id, int position)
// {
//     id_ = to_int(id);
//     position_ = position;
// }
Particle::Particle(LorentzVector const& momentum, int id, int position)
{
    id_ = id;
    position_ = position;
    momentum_ = momentum;
}
Particle::Particle(TLorentzVector const& momentum, int id, int position)
{
    id_ = id;
    position_ = position;
    momentum_ = momentum;
}
LorentzVector Particle::momentum() const
{
    return momentum_;
}
int Particle::position() const
{
    return position_;
}
int Particle::id() const
{
    return id_;
}
}
