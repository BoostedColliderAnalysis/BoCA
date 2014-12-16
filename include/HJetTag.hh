# ifndef HJetTag_hh
# define HJetTag_hh

# include <set>

# include "HObject.hh"

class HFamily
{
public:
    HFamily(const int NewParticle, const int NewMother1, const int NewMother2) {
        ParticleId = NewParticle;
        Mother1Id = NewMother1;
        Mother2Id = NewMother2;
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

    virtual int GetBranchId(const HFamily Family, int BranchId);

    std::set<HParticleId> HeavyParticles;

    std::set<HFamilyId> HeavyParticleFamilies;

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
