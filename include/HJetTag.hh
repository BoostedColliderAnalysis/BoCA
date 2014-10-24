# ifndef HJetTag_hh
# define HJetTag_hh

# include <set>

# include "HObject.hh"

using std::set;

/**
 * @brief defines how to tag a jet
 *
 * has to be subclassed for each case
 */
class HJetTag : public HObject
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
    virtual int GetBranchId(const int ParticleId, int BranchId) const;

    /**
     * @brief set of particle Ids which are considerd relevant
     *
     */
    const set<int> HeavyParticles = {BottomId, TopId};

protected:

    /**
     * @brief set of Particle Ids defiend as initial state radiation
     *
     */
    const set<int> RadiationParticles = {GluonId, UpId, DownId, StrangeId, CharmId, UpDown0Id, UpDown1Id, UpUp1Id, DownDown1Id};

private:

    virtual inline string ClassName() const {

        return "HJetTag";

    };

};

# endif
