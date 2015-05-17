# pragma once

# include "HParticle.hh"
# include "HLepton.hh"
# include "Hadrons.hh"

namespace analysis
{

/**
 * @brief Base class for the event Topology
 *
 */
class Event : public Object
{

public:

    Event(const ClonesArrays::Source source);

    ~Event();

    void NewEvent(const ClonesArrays &);

    Hadrons &hadrons() const {
        return *hadrons_;
    }

    HLepton &Leptons() const {
        return *leptons_;
    }

    HParticle &Partons() const {
        return *partons_;
    }

    float mass() const {
        return mass_;
    }

    void SetMass(const float mass) {
        mass_ = mass;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Event";
    }

    /**
     * @brief Particles
     *
     */
    HParticle *partons_ = NULL;

    /**
     * @brief Leptons
     *
     */
    HLepton *leptons_ = NULL;

    /**
     * @brief Jets
     *
     */
    Hadrons *hadrons_ = NULL;

private:

    ClonesArrays::Source source_;

    float mass_;

};

}
