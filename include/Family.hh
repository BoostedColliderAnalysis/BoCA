/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Member.hh"

namespace boca
{

class Family
{

public:

    Family();

    Family(int id);

    Family(int id, int mother_1_id, int mother_2_id);

    Family(Member const& particle, Member const& mother_1, Member const& mother_2, Member const& grand_mother, Member const& great_grand_mother);

    Family(TLorentzVector const& particle, LorentzVector<Momentum> const& mother, int particle_position, int id, int mother_position, int mother_id);

    bool operator==(Family const& family) const;

    bool Marker() const;

    Member const& Particle() const;

    Member const& Mother() const;

    Member const& StepMother() const;

    Member const& GrandMother() const;

    Member const& GreatGrandMother() const;

private:

    Member particle_;

    Member mother_;

    Member step_mother_;

    Member grand_mother_;

    Member great_grand_mother_;

};

}

namespace std
{

template <>
struct hash<boca::Family> {
    size_t operator()(boca::Family const& family) const;
};

}
