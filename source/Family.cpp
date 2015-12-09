/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Family.hh"

namespace boca
{

Family::Family()
{}

Family::Family(int id)
    : particle_(Member(id))
    , mother_(Member(id))
{}

Family::Family(int id, int mother_1_id, int mother_2_id)
    : particle_(Member(id))
    , mother_(Member(mother_1_id))
    , step_mother_(Member(mother_2_id))
{}

Family::Family(Member const& particle, Member const& mother_1, Member const& mother_2, Member const& grand_mother, Member const& great_grand_mother)
    : particle_(particle)
    , mother_(mother_1)
    , step_mother_(mother_2)
    , grand_mother_(grand_mother)
    , great_grand_mother_(great_grand_mother)
{}

Family::Family(TLorentzVector const& particle, LorentzVector<Momentum> const& mother, int particle_position, int id, int mother_position, int mother_id)
    : particle_(Member(particle, id, particle_position)), mother_(Member(mother, mother_id, mother_position))
{}

bool Family::operator==(Family const& family) const
{
    return (particle_.Id() == family.Particle().Id() && mother_.Id() == family.Mother().Id());
}

Member const& Family::Particle() const
{
    return particle_;
}

Member const& Family::StepMother() const
{
    return step_mother_;
}

Member const& Family::Mother() const
{
    return mother_;
}

Member const& Family::GrandMother() const
{
    return grand_mother_;
}

Member const& Family::GreatGrandMother() const
{
    return great_grand_mother_;
}

}
namespace std
{
std::size_t hash< boca::Family >::operator()(const boca::Family& family) const
{
    return (std::hash<int>()(family.Particle().Id()) ^ (std::hash<int>()(family.Mother().Id()) << 1)) >> 1;
}
}

