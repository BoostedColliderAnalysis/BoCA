#include "Particle.hh"
#include "Predicate.hh"

namespace analysis {

Particle::Particle(int id)
{
    id_ = id;
}
Particle::Particle(const Id id)
{
    id_ = to_int(id);
}
Particle::Particle(const LorentzVector& momentum, int id, int position)
{
    id_ = id;
    position_ = position;
    momentum_ = momentum;
}

Particle::Particle(const Id id, int position)
{
    id_ = to_int(id);
    position_ = position;
}
Particle::Particle(const TLorentzVector& momentum, int id, int position)
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
