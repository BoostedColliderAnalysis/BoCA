#include "Family.hh"

namespace analysis {

Family::Family()
{
    daughter_ids_.reserve(2);
}

Family::Family(int id) : particle_(Particle(id)), mother_1_(Particle(id))
{
    daughter_ids_.reserve(2);
}

Family::Family(const Id id) : particle_(Particle(id)), mother_1_(Particle(id))
{
    daughter_ids_.reserve(2);
}

Family::Family(const Id id, const Id mother_id) : particle_(Particle(id)), mother_1_(Particle(mother_id))
{
    daughter_ids_.reserve(2);
}

Family::Family(int id, int mother_1_id, int mother_2_id) : particle_(Particle(id)), mother_1_(Particle(mother_1_id)), mother_2_(Particle(mother_2_id))
{
    daughter_ids_.reserve(2);
}

Family::Family(int id, int mother_1_id, int mother_2_id, int grand_mother_id) : particle_(Particle(id)), mother_1_(Particle(mother_1_id)), mother_2_(Particle(mother_2_id)), grand_mother_(Particle(grand_mother_id))
{
    daughter_ids_.reserve(2);
}

Family::Family(const Id id, const Id mother_1_id, const Id mother_2_id) : particle_(Particle(id)), mother_1_(Particle(mother_1_id)), mother_2_(Particle(mother_2_id))
{
    daughter_ids_.reserve(2);
}

Family::Family(const Id id, const Id mother_1_id, const Id mother_2_id, const Id grand_mother_id) : particle_(Particle(id)), mother_1_(Particle(mother_1_id)), mother_2_(Particle(mother_2_id)), grand_mother_(Particle(grand_mother_id))
{
    daughter_ids_.reserve(2);
}

Family::Family(int particle_position, const Id id, int mother_position, const Id mother_id) : particle_(Particle(id, particle_position)), mother_1_(Particle(mother_id, mother_position))
{
    daughter_ids_.reserve(2);
}

Family::Family(const TLorentzVector& particle, const LorentzVector& mother, int particle_position, int id, int mother_position, int mother_id) : particle_(Particle(particle, id, particle_position)), mother_1_(Particle(mother, mother_id, mother_position))
{
    daughter_ids_.reserve(2);
}

bool Family::operator==(const Family& family) const
{
    return (particle_.id() == family.particle().id() && mother_1_.id() == family.mother_1().id() && daughter_ids_ == family.daughter_ids_);
}

void Family::AddDaughter(int daughter_id)
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
