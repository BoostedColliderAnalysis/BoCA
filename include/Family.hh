# pragma once

# include "Object.hh"

namespace analysis {

struct Particle {

    TLorentzVector Momentum;

    int Position;

    int Id;

};

class Family : public Object
{

public:

    Family();

    Family(const int particle_id);

    Family(const int particle_id, const int mother_id);

    Family(const int particle_id, const int mother_1_id, const int mother_2_id);

    Family(const int particle_position, const int particle_id, const int mother_position, const int mother_id);

    Family(const TLorentzVector &particle, const TLorentzVector &mother, const int particle_position, const int particle_id, const int mother_position, const int mother_id);

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

protected:

    Particle particle_;

    Particle mother_1_;

    Particle mother_2_;

    std::vector<int> daughter_ids_;

    float pt_;

    bool marker_;

};

}

namespace std
{

template <>
struct hash<analysis::Family> {
    std::size_t operator()(const analysis::Family &Family) const {

        return ((std::hash<int>()(Family.particle().Id)
                 ^ (std::hash<int>()(Family.mother_1().Id) << 1)) >> 1)
               //                ^ (std::hash<int>()(Family.mother_2().Id) << 1)
               ;
    }
};

}
