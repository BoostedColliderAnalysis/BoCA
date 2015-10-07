/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Partons.hh"
#include "Leptons.hh"
#include "Hadrons.hh"

namespace boca {

enum class Decay
{
  leptonic,
  hadronic
};

std::string Name(Decay decay);

/**
 * @brief Base class for the event Topology
 *
 */
class Event {

public:

    Event();

    Event(const Source source);

    virtual ~Event();

    void NewEvent(ClonesArrays const& clones_arrays);

    const boca::Hadrons& Hadrons() const
    {
        return *hadrons_;
    }

    const boca::Leptons& Leptons() const
    {
        return *leptons_;
    }


    const boca::Partons& Partons() const
    {
        return *partons_;
    }

    Mass mass() const
    {
        return mass_;
    }

    void SetMass(Mass const& mass)
    {
        mass_ = mass;
    }

private:

    /**
     * @brief Particles
     *
     */
  boca::Partons *partons_ = nullptr;

    /**
     * @brief Leptons
     *
     */
  boca::Leptons *leptons_ = nullptr;

    /**
     * @brief Jets
     *
     */
  boca::Hadrons *hadrons_ = nullptr;

    Source source_;

    Mass mass_;

};

}
