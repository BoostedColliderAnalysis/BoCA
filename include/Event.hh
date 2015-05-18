# pragma once

# include "Partons.hh"
# include "Leptons.hh"
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

    void NewEvent(const ClonesArrays &clones_arrays);

    Hadrons &hadrons() const {
        return *hadrons_;
    }

    Leptons &leptons() const {
        return *leptons_;
    }


    Partons &partons() const {
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

private:

    /**
     * @brief Particles
     *
     */
    Partons *partons_ = NULL;

    /**
     * @brief Leptons
     *
     */
    Leptons *leptons_ = NULL;

    /**
     * @brief Jets
     *
     */
    Hadrons *hadrons_ = NULL;

    ClonesArrays::Source source_;

    float mass_;

};

}
