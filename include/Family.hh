/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <vector>
#include <functional>

#include "Particle.hh"

namespace boca {

class Family {

public:

    Family();

    Family(int id);

//     Family(Id id);

//     Family(Id id, Id mother_id);

    Family(int id, int mother_1_id, int mother_2_id);

//     Family(Id id, Id mother_1_id, Id mother_2_id);

    Family(Particle const& id, Particle const& mother_1_id, Particle const& mother_2_id, Particle const& grand_mother_id, Particle const& grand_grand_mother_id);

//     Family(Id id, Id mother_1_id, Id mother_2_id, Id grand_mother_id);

//     Family(int particle_position, Id id, int mother_position, Id mother_id);

    Family(TLorentzVector const& particle, LorentzVector const& mother, int particle_position, int id, int mother_position, int mother_id);

    bool operator==(Family const& family) const;

    void AddDaughter(int daughter_id);

    void SetMarker();

    void UnSetMarker();

    bool Marker() const;

    Particle particle() const
    {
        return particle_;
    }

    Particle mother_1() const
    {
        return mother_1_;
    }

    Particle mother_2() const
    {
        return mother_2_;
    }

    Particle grand_mother() const
    {
        return grand_mother_;
    }

    Particle grand_grand_mother() const
    {
      return grand_grand_mother_;
    }

    float Pt() const
    {
        return pt_;
    }

private:

    Particle particle_;

    Particle mother_1_;

    Particle mother_2_;

    Particle grand_mother_;

    Particle grand_grand_mother_;

    std::vector<int> daughter_ids_;//(2);

    float pt_ = 0;

    bool marker_ = false;

};

}

namespace std {

template <>
struct hash<boca::Family> {
    size_t operator()(const boca::Family& Family) const
    {
        return ((std::hash<int>()(Family.particle().id())
                 ^ (std::hash<int>()(Family.mother_1().id()) << 1)) >> 1)
               //                ^ (std::hash<int>()(Family.mother_2().Id) << 1)
               ;
    }
};

}
