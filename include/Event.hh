#pragma once

#include "Partons.hh"
#include "Leptons.hh"
#include "Hadrons.hh"
#include "Isolation.hh"

namespace analysis
{

/**
 * @brief Base class for the event Topology
 *
 */
class Event
{

public:

    Event();

    Event(const Source source);

    ~Event();

    void NewEvent(const ClonesArrays &clones_arrays);

    analysis::Hadrons const& Hadrons() const;

    analysis::Leptons const& Leptons() const;

    analysis::Partons const& Partons() const;

    float mass() const;

    void SetMass(float mass);

    Jets IsolatedLeptons();

    Isolation isolation_;

    /**
     * @brief Leptons
     *
     */
    analysis::Leptons *leptons_ = nullptr;

private:

    /**
     * @brief Particles
     *
     */
    analysis::Partons *partons_ = nullptr;

    /**
     * @brief Jets
     *
     */
    analysis::Hadrons *hadrons_ = nullptr;

    Source source_;

    float mass_;

};

}
