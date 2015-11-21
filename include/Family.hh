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

    Family(TLorentzVector const& particle, LorentzVector const& mother, int particle_position, int id, int mother_position, int mother_id);

    bool operator==(Family const& family) const;

    void AddDaughter(int daughter_id);

    void SetMarker();

    void UnSetMarker();

    bool Marker() const;

    Member particle() const;

    Member mother_1() const;

    Member mother_2() const;

    Member grand_mother() const;

    Member grand_grand_mother() const;

    float Pt() const;

private:

    Member particle_;

    Member mother_1_;

    Member mother_2_;

    Member grand_mother_;

    Member grand_grand_mother_;

    std::vector<int> daughter_ids_;//(2);

    float pt_ = 0;

    bool marker_ = false;

};

}

namespace std
{

template <>
struct hash<boca::Family> {
    size_t operator()(const boca::Family& Family) const {
        return ((std::hash<int>()(Family.particle().id())^ (std::hash<int>()(Family.mother_1().id()) << 1)) >> 1);
    }
};

}
