#pragma once

#include "Partons.hh"
#include "Leptons.hh"
#include "Hadrons.hh"

namespace analysis {

/**
 * @brief Base class for the event Topology
 *
 */
class Event {

public:

    Event();

    Event(const Source source);

    ~Event();

    void NewEvent(const ClonesArrays& clones_arrays);

    const analysis::Hadrons& Hadrons() const
    {
        return *hadrons_;
    }

    const analysis::Leptons& Leptons() const
    {
        return *leptons_;
    }


    const analysis::Partons& Partons() const
    {
        return *partons_;
    }

    float mass() const
    {
        return mass_;
    }

    void SetMass(const float mass)
    {
        mass_ = mass;
    }

private:

    /**
     * @brief Particles
     *
     */
    analysis::Partons* partons_ = NULL;

    /**
     * @brief Leptons
     *
     */
    analysis::Leptons* leptons_ = NULL;

    /**
     * @brief Jets
     *
     */
    analysis::Hadrons* hadrons_ = NULL;

    Source source_;

    float mass_;

};

}
