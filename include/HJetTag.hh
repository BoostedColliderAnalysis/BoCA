# ifndef HJetTag_hh
# define HJetTag_hh

# include <set>
# include <unordered_set>

# include "Object.hh"
# include "Family.hh"

/**
 * @brief defines how to tag a jet
 *
 */
class analysis::HJetTag : public Object
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

    Family GetBranchFamily(const analysis::Family& node_family, analysis::Family& branch_family);


    std::set<HParticleId> HeavyParticles;

//     std::unordered_set<Family> HeavyFamily;

//     std::set<FamilyId> HeavyParticleFamilies;

protected:

    /**
     * @brief set of Particle Ids defiend as initial state radiation
     *
     */
    std::set<HParticleId> RadiationParticles {ProtonId/*, GluonId, UpId, DownId, StrangeId, CharmId, UpDown0Id, UpDown1Id, UpUp1Id, DownDown1Id*/};

private:

    virtual inline std::string ClassName() const {
        return "HJetTag";

    };

};

# endif
