/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Family.hh"

namespace boca {

Family::Family()
{
    daughter_ids_.reserve(2);
}

Family::Family(int id) : particle_(Member(id)), mother_(Member(id))
{
    daughter_ids_.reserve(2);
}

Family::Family(int id, int mother_1_id, int mother_2_id) : particle_(Member(id)), mother_(Member(mother_1_id)), step_mother_(Member(mother_2_id))
{
    daughter_ids_.reserve(2);
}

Family::Family(Member const& id, Member const& mother_1_id, Member const& mother_2_id, Member const& grand_mother_id, Member const& grand_grand_mother_id)
: particle_(id)
, mother_(mother_1_id)
, step_mother_(mother_2_id)
, grand_mother_(grand_mother_id)
, great_grand_mother_(grand_grand_mother_id)
{
    daughter_ids_.reserve(2);
}

Family::Family(TLorentzVector const& particle, LorentzVector<Momentum> const& mother, int particle_position, int id, int mother_position, int mother_id) : particle_(Member(particle, id, particle_position)), mother_(Member(mother, mother_id, mother_position))
{
    daughter_ids_.reserve(2);
}

bool Family::operator==(Family const& family) const
{
    return (particle_.Id() == family.Particle().Id() && mother_.Id() == family.Mother().Id() && daughter_ids_ == family.daughter_ids_);
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

Member Family::Particle() const
{
    return particle_;
}

Member Family::StepMother() const
{
    return step_mother_;
}

Member Family::Mother() const
{
    return mother_;
}

Member Family::GrandMother() const
{
    return grand_mother_;
}

Member Family::GreatGrandMother() const
{
    return great_grand_mother_;
}

float Family::Pt() const
{
    return pt_;
}

}
