/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Partons.hh"
#include "boca/Hadrons.hh"
#include "boca/Isolation.hh"

namespace boca
{

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
class Event
{

public:

    Event(TreeReader const& tree_reader, Source source);

    virtual ~Event();

    std::vector<Lepton> Leptons() const {
        return Leptons_().leptons();
    }

    std::vector<Lepton> Electrons() const {
      return Leptons_().Electrons();
    }

    std::vector<Lepton> Muons() const {
      return Leptons_().Muons();
    }

    std::vector<Lepton> Photons() const {
      return Leptons_().Photons();
    }

    std::vector<Particle> GenParticles() const {
        return Partons().GenParticles();
    }

    std::vector<Particle> Particles() const {
        return Partons().Particles();
    }

    Momentum ScalarHt() const {
        return Hadrons().ScalarHt();
    }

    boca::MissingEt MissingEt() const {
        return Hadrons().MissingEt();
    }

    std::vector<Jet> Jets() const {
        return Hadrons().Jets();
    }

    std::vector<Jet> EFlow(JetDetail jet_detail) const {
        return Hadrons().EFlow(jet_detail);
    }

private:

    boca::Hadrons const& Hadrons() const;

    boca::Leptons const& Leptons_() const;

    boca::Partons const& Partons() const;

    std::vector<Lepton> IsolatedLeptons();

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
