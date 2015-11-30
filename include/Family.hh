/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <vector>
#include <functional>

#include "Member.hh"

namespace boca
{

class Family
{

public:

    Family();

    Family(int id);

    Family(int id, int mother_1_id, int mother_2_id);

    Family(Member const& id, Member const& mother_1_id, Member const& mother_2_id, Member const& grand_mother_id, Member const& grand_grand_mother_id);

    Family(TLorentzVector const& particle, LorentzVector<Momentum> const& mother, int particle_position, int id, int mother_position, int mother_id);

    bool operator==(Family const& family) const;

    void AddDaughter(int daughter_id);

    void SetMarker();

    void UnSetMarker();

    bool Marker() const;

    Member Particle() const;

    Member Mother() const;

    Member StepMother() const;

    Member GrandMother() const;

    Member GreatGrandMother() const;

    float Pt() const;

private:

    Member particle_;

    Member mother_;

    Member step_mother_;

    Member grand_mother_;

    Member great_grand_mother_;

    std::vector<int> daughter_ids_;

    float pt_ = 0;

    bool marker_ = false;

};

}

namespace std
{

template <>
struct hash<boca::Family> {
    size_t operator()(boca::Family const& family) const {
        return ((std::hash<int>()(family.Particle().Id())^ (std::hash<int>()(family.Mother().Id()) << 1)) >> 1);
    }
};

}
