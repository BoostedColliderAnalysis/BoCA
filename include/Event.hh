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

    analysis::Hadrons &Hadrons() const {
        return *hadrons_;
    }

    analysis::Leptons &Leptons() const {
        return *leptons_;
    }


    analysis::Partons &Partons() const {
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
    analysis::Partons *partons_ = NULL;

    /**
     * @brief Leptons
     *
     */
    analysis::Leptons *leptons_ = NULL;

    /**
     * @brief Jets
     *
     */
    analysis::Hadrons *hadrons_ = NULL;

    ClonesArrays::Source source_;

    float mass_;

};

}
