/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Flag.hh"
#include "boca/multiplets/Jet.hh"
#include "boca/multiplets/Particle.hh"

namespace boca
{

enum class JetDetail
{
    none = 0,
    plain = 1 << 0,
    structure = 1 << 1,
    isolation = 1 << 2,
};

template<>
struct Flag<JetDetail> {
    static const bool enable = true;
};

std::string Name(JetDetail jet_detail);

enum class Decay
{
    leptonic,
    hadronic
};

std::string Name(Decay decay);

enum class Status
{
  none = 0,
  stable = 1,
  unstable = 2,
  generator = 3
};

class TreeReader;

/**
 * @brief Base class for the event Topology
 *
 */
class Event
{

public:

    /**
    * @brief Constructor
    */
    Event(boca::TreeReader const& tree_reader);

    /**
    * @brief Generator level Particles
    */
    std::vector<Particle> GenParticles() const;

    /**
    * @brief All decayed particles
    */
    std::vector<Particle> Particles() const;

    /**
    * @brief Electrons and muons
    */
    virtual std::vector<Lepton> Leptons() const;

    /**
    * @brief Electrons
    */
    virtual std::vector<Lepton> Electrons() const = 0;

    /**
    * @brief Muons
    */
    virtual std::vector<Lepton> Muons() const = 0;

    /**
    * @brief Photons
    */
    virtual std::vector<Photon> Photons() const = 0;

    /**
    * @brief Jets
    */
    virtual std::vector<Jet> Jets() const = 0;

    /**
    * @brief Scalar sum of transverse momenta \f$H_T=\sum_ip_{Ti}\f$
    *
    * @return boca::units::Momentum
    */
    virtual Momentum ScalarHt() const;

    /**
    * @brief Missing transverse enenergy
    */
    virtual boca::MissingEt MissingEt() const;

    /**
    * @brief EFlow jets
    */
    virtual std::vector<Jet> EFlow(JetDetail jet_detail) const;

protected:

    boca::TreeReader const& TreeReader() const;

private:

    virtual std::vector<Particle> Particles(Status max_status) const = 0;

    boca::TreeReader const* tree_reader_;

};

}
