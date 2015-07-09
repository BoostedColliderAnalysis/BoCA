#pragma once

#include "Particle.hh"

namespace analysis
{

class Family
{

public:

    Family();

    Family(const int id);

    Family(const Id id);

//     Family(const int id, const int mother_id);

    Family(const Id id, const Id mother_id);

    Family(const int id, const int mother_1_id, const int mother_2_id);

    Family(const Id id, const Id mother_1_id, const Id mother_2_id);

//     Family(const int particle_position, const int id, const int mother_position, const int mother_id);

    Family(const int particle_position, const Id id, const int mother_position, const Id mother_id);

    Family(const TLorentzVector &particle, const LorentzVector &mother, const int particle_position, const int id, const int mother_position, const int mother_id);

//     Family(const LorentzVector &particle, const LorentzVector &mother, const int particle_position, const Id id, const int mother_position, const Id mother_id);

    bool operator==(const Family &family) const;

    void AddDaughter(const int daughter_id);

    void SetMarker();

    void UnSetMarker();

    bool Marker() const;

    Particle particle() const {
        return particle_;
    }

    Particle mother_1() const {
        return mother_1_;
    }

    Particle mother_2() const {
        return mother_2_;
    }

    float Pt() const {
        return pt_;
    }

private:

    Particle particle_;

    Particle mother_1_;

    Particle mother_2_;

    std::vector<int> daughter_ids_;//(2);

    float pt_ = 0;

    bool marker_ = false;

};

}

namespace std
{

template <>
struct hash<analysis::Family> {
    std::size_t operator()(const analysis::Family &Family) const {

        return ((std::hash<int>()(Family.particle().id())
                 ^ (std::hash<int>()(Family.mother_1().id()) << 1)) >> 1)
               //                ^ (std::hash<int>()(Family.mother_2().Id) << 1)
               ;
    }
};

}
