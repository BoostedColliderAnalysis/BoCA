# ifndef HJetTag_hh
# define HJetTag_hh

# include <set>
# include <unordered_set>

# include "HObject.hh"

class HFamily
{

public:

    HFamily(const int NewParticle, const int NewMother1, const int NewMother2) {
        ParticleId = NewParticle;
        Mother1Id = NewMother1;
        Mother2Id = NewMother2;
    }

    bool operator==(const HFamily &Family) const {
//         return (std::abs(ParticleId) == std::abs(Family.ParticleId)
//         && std::abs(Mother1Id) == std::abs(Family.Mother1Id)
//         && std::abs(Mother2Id) == std::abs(Family.Mother2Id));
        return (ParticleId == Family.ParticleId
        && Mother1Id == Family.Mother1Id
        && Mother2Id == Family.Mother2Id);
    }

    HFamily Abs() const {
      return HFamily(std::abs(ParticleId),std::abs(Mother1Id),std::abs(Mother2Id));
    }

    int ParticleId;
    int Mother1Id;
    int Mother2Id;
};

class HFamilyId : public hanalysis::HObject
{
public:
    HFamilyId(const HParticleId NewParticle, const HParticleId NewMother1, const HParticleId NewMother2) {
        ParticleId = NewParticle;
        Mother1Id = NewMother1;
        Mother2Id = NewMother2;
    }
    HParticleId ParticleId;
    HParticleId Mother1Id;
    HParticleId Mother2Id;
};

namespace std
{

template <>
struct hash<HFamily> {
    std::size_t operator()(const HFamily &Family) const {

        return ((std::hash<int>()(Family.ParticleId)
                 ^ (std::hash<int>()(Family.Mother1Id) << 1)) >> 1)
               ^ (std::hash<int>()(Family.Mother2Id) << 1);
    }
};

}

/**
 * @brief defines how to tag a jet
 *
 */
class hanalysis::HJetTag : public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HJetTag();

    /**
     * @brief Destructor
     *
     */
    ~HJetTag();

    /**
     * @brief decide on the branch id based on the former branch id and the particle id
     *
     */
    virtual int GetBranchId(const int ParticleId, int BranchId);

    HFamily GetBranchId(const HFamily &Family, HFamily &BranchId);

    std::set<HParticleId> HeavyParticles;

    std::unordered_set<HFamily> HeavyFamily;

//     std::set<HFamilyId> HeavyParticleFamilies;

protected:

    /**
     * @brief set of Particle Ids defiend as initial state radiation
     *
     */
    std::set<HParticleId> RadiationParticles {GluonId, UpId, DownId, StrangeId, CharmId, UpDown0Id, UpDown1Id, UpUp1Id, DownDown1Id};

private:

    virtual inline std::string ClassName() const {
        return "HJetTag";

    };

};

# endif
