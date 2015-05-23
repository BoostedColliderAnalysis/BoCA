# pragma once

# include <set>

# include "Family.hh"

namespace analysis{

/**
 * @brief defines how to tag a jet
 *
 */
class JetTag : public Object
{

public:

    /**
     * @brief Constructor
     *
     */
    JetTag();

    /**
     * @brief decide on the branch id based on the former branch id and the particle id
     *
     */
    virtual int GetBranchId(const int particle_id, int branch_id);

    Family GetBranchFamily(const Family& node_family, Family& branch_family);


    std::set<ParticleId> HeavyParticles;

protected:

    /**
     * @brief set of Particle Ids defiend as initial state radiation
     *
     */
    std::set<ParticleId> RadiationParticles {ProtonId};

private:

    virtual inline std::string ClassName() const {
        return "JetTag";
    };

};

}
