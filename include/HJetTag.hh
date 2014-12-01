# ifndef HJetTag_hh
# define HJetTag_hh

# include <set>

# include "HObject.hh"

/**
 * @brief defines how to tag a jet
 *
 * has to be subclassed for each case
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
     * @param ParticleId Id of the Particle
     * @param BranchId former id of the Branch
     * @return int new Id of the Branch
     */
    virtual int GetBranchId(const int ParticleId, int BranchId);

//     void SetHeavyParticles(const std::set<HParticleId> &NewHeavyParticles) {
//         HeavyParticles = NewHeavyParticles;
//     }
// 
//     std::set<HParticleId> GetHeavyParticles() const {
//         return HeavyParticles;
//     }
    std::set<HParticleId> HeavyParticles;

protected:

    /**
     * @brief set of particle Ids which are considerd relevant
     *
     */


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
