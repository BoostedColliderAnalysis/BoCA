/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Partons.hh"
#include "Leptons.hh"
#include "Hadrons.hh"
#include "Isolation.hh"

namespace boca
{

enum class Decay
{
    leptonic,
    hadronic,
    other
};

std::string Name(Decay decay);

/**
 * @brief Base class for the event Topology
 *
 */
class Event
{

public:

    Event(TreeReader const& tree_reader, Source source);

    virtual ~Event();

    boca::Hadrons const& Hadrons() const;

    boca::Leptons const& Leptons() const;

    boca::Partons const& Partons() const;

    std::vector<Lepton> IsolatedLeptons();

private:

    friend class Isolation;

    /**
     * @brief Leptons
     *
     */
    boca::Leptons* leptons_ = nullptr;

    /**
     * @brief Particles
     *
     */
    boca::Partons* partons_ = nullptr;

    /**
     * @brief Jets
     *
     */
    boca::Hadrons* hadrons_ = nullptr;

    Isolation isolation_;

    Source source_;

};

}
