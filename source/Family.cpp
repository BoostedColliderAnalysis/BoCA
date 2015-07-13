#include "Family.hh"

namespace analysis
{

Family::Family()
{
//   marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const int id) : particle_(Particle(id)), mother_1_(Particle(id))
{
//   marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const Id id) : particle_(Particle(id)), mother_1_(Particle(id))
{
//   particle_.id() = to_int(id);
//   mother_1_.id() = to_int(id);
//   particle_.position = EmptyPosition;
//   mother_1_.position = EmptyPosition;
//   marker_ = false;
  daughter_ids_.reserve(2);
}

// Family::Family(const int id, const int mother_id) {
//   particle_.Id = id;
//   mother_1_.Id = mother_id;
//   particle_.Position = EmptyPosition;
//   mother_1_.Position = EmptyPosition;
//   marker_ = false;
//   daughter_ids_.reserve(2);
// }

Family::Family(const Id id, const Id mother_id) : particle_(Particle(id)), mother_1_(Particle(mother_id))
{
//   particle_.id() = to_int(id);
//   mother_1_.id() = to_int(mother_id);
//   particle_.position = EmptyPosition;
//   mother_1_.position = EmptyPosition;
//   marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const int id, const int mother_1_id, const int mother_2_id) : particle_(Particle(id)), mother_1_(Particle(mother_1_id)), mother_2_(Particle(mother_2_id))
{
//   particle_.id() = id;
//   mother_1_.id() = mother_1_id;
//   mother_2_.id() = mother_2_id;
//   particle_.position = EmptyPosition;
//   mother_1_.position = EmptyPosition;
//   marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const Id id, const Id mother_1_id, const Id mother_2_id) : particle_(Particle(id)), mother_1_(Particle(mother_1_id)), mother_2_(Particle(mother_2_id))
{
//   particle_.id() = to_int(id);
//   mother_1_.id() = to_int(mother_1_id);
//   mother_2_.id() = to_int(mother_2_id);
//   particle_.position = EmptyPosition;
//   mother_1_.position = EmptyPosition;
//   marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const int particle_position, const Id id, const int mother_position, const Id mother_id) : particle_(Particle(id, particle_position)), mother_1_(Particle(mother_id, mother_position))
{
//     particle_.position = particle_position;
//     particle_.id() = to_int(id);
//     mother_1_.position = mother_position;
//     mother_1_.id() = to_int(mother_id);
//     marker_ = false;
    daughter_ids_.reserve(2);
}

Family::Family(const TLorentzVector &particle, const LorentzVector &mother, const int particle_position, const int id, const int mother_position, const int mother_id) : particle_(Particle(particle, id, particle_position)), mother_1_(Particle(mother, mother_id, mother_position))
{
//     particle_.momentum = particle;
//     mother_1_.momentum = mother;
//     particle_.position = particle_position;
//     particle_.id() = id;
//     mother_1_.position = mother_position;
//     mother_1_.id() = mother_id;
//     marker_ = false;
    daughter_ids_.reserve(2);
}

// Family::Family(const TLorentzVector &particle, const TLorentzVector &mother, const int particle_position, const Id id, const int mother_position, const Id mother_id) {
//   particle_.Momentum = particle;
//   mother_1_.Momentum = mother;
//   particle_.Position = particle_position;
//   particle_.Id = to_int(id);
//   mother_1_.Position = mother_position;
//   mother_1_.Id = to_int(mother_id);
//   marker_ = false;
//   daughter_ids_.reserve(2);
// }

bool Family::operator==(const Family &family) const
{
    return (particle_.id() == family.particle().id() && mother_1_.id() == family.mother_1().id() && daughter_ids_ == family.daughter_ids_);
}

void Family::AddDaughter(const int daughter_id)
{
    daughter_ids_.emplace_back(daughter_id);
}


void Family::SetMarker()
{
    marker_ = true;
}

void Family::UnSetMarker()
{
    marker_ = false;
}

bool Family::Marker() const
{
    return marker_;
}

}
