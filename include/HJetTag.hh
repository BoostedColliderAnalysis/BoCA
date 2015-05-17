# pragma once

# include <set>

# include "Family.hh"

namespace analysis{

/**
 * @brief defines how to tag a jet
 *
 */
class HJetTag : public Object
{

public:

    /**
     * @brief Constructor
     *
     */
    HJetTag();

    /**
     * @brief decide on the branch id based on the former branch id and the particle id
     *
     */
    virtual int GetBranchId(const int particle_id, int branch_id);

    Family GetBranchFamily(const Family& node_family, Family& branch_family);


    std::set<HParticleId> HeavyParticles;

protected:

    /**
     * @brief set of Particle Ids defiend as initial state radiation
     *
     */
    std::set<HParticleId> RadiationParticles {ProtonId};

private:

    virtual inline std::string ClassName() const {
        return "HJetTag";
    };

};

}
