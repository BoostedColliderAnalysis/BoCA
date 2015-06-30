#pragma once

#include "FourVector.hh"
#include "Predicate.hh"

namespace analysis
{

/**
 * @brief Base class for jets
 *
 */
class Hadrons : public FourVector
{

public:

    virtual ~Hadrons() {};

    /**
     * @brief Initialize New event
     */
    void NewEvent(const ClonesArrays &clones_arrays);

    virtual analysis::Jets Jets() = 0;

    virtual float ScalarHt();

    virtual fastjet::PseudoJet MissingEt();

protected:

//     DetectorGeometry &detector_geometry() {
//         return detector_geometry_;
//     }

    template<typename Particle_1, typename Particle_2>
    bool CheckIsolation(const Particle_1 &particle_1, const Particle_2 &particle_2, const float delta_r_isolation_max) const {
        bool isolated = false;
        if (analysis::PseudoJet(const_cast<Particle_1 &>(particle_1).P4()).delta_R(analysis::PseudoJet(const_cast<Particle_2 &>(particle_2).P4())) < delta_r_isolation_max) isolated = true;
        return isolated;
    }

    template<typename Particle_1, typename Particle_2>
    bool CheckIsolation(const Particle_1 &particle_1, const Particle_2 &particle_2) const {
        const float delta_r_isolation_max = 0; // TODO decide on best value
        return CheckIsolation(particle_1, particle_2, delta_r_isolation_max);
    }

private:

//     DetectorGeometry detector_geometry_;

};

}
