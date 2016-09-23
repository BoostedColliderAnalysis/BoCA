/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Mutable.hh"
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
    std::vector<Lepton> Leptons() const;

    /**
    * @brief Electrons
    */
    std::vector<Lepton> Electrons() const;

    /**
    * @brief Muons
    */
    std::vector<Lepton> Muons() const;

    /**
    * @brief Photons
    */
    std::vector<Photon> Photons() const;

    /**
    * @brief Jets
    */
    std::vector<Jet> Jets() const;

    /**
    * @brief EFlow jets
    */
    std::vector<Jet> EFlow(JetDetail jet_detail) const;

    /**
    * @brief Missing transverse enenergy
    */
    boca::MissingEt MissingEt() const;

    /**
    * @brief Scalar sum of transverse momenta \f$H_T=\sum_ip_{Ti}\f$
    *
    * @return boca::units::Momentum
    */
    Momentum ScalarHt() const;

protected:

    boca::TreeReader const& TreeReader() const;

    virtual std::vector<Particle> GetParticles(Status max_status) const = 0;

    virtual std::vector<Lepton> GetElectrons() const = 0;

    virtual std::vector<Lepton> GetMuons() const = 0;

    virtual std::vector<Photon> GetPhotons() const = 0;

    virtual std::vector<Jet> GetJets() const = 0;

    virtual std::vector<Jet> GetEFlow(JetDetail jet_detail) const = 0;

    virtual boca::MissingEt GetMissingEt() const = 0;

    virtual Momentum GetScalarHt() const = 0;

private:

    boca::TreeReader const* tree_reader_;

    std::map<Status, Mutable<std::vector<Particle>>> particles_;

    Mutable<std::vector<Lepton>> electrons_;

    Mutable<std::vector<Lepton>> muons_;

    Mutable<std::vector<Photon>> photons_;

    Mutable<std::vector<Jet>> jets_;

    Mutable<std::vector<Jet>> eflow_;

    Mutable<boca::MissingEt> missing_et_;

    Mutable<Momentum> scalar_ht_;

};

}
