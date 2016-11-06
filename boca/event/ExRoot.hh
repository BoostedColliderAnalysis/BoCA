/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/event/Event.hh"

namespace boca
{

/**
 * @brief ExRoot
 *
 */
namespace exroot
{

/**
 * @brief pgs and parton events
 *
 */
class Event : public boca::Event
{

public:

    using boca::Event::Event;

protected:

    std::vector<Particle> GetParticles(Status max_status) const override;

    std::vector<Lepton> GetElectrons() const override;

    std::vector<Lepton> GetMuons() const override;

    std::vector<Photon> GetPhotons() const override;

    std::vector<Jet> GetJets() const override;

    virtual std::vector<Jet> GetEFlow(JetDetail jet_detail) const override;

    virtual boca::MissingEt GetMissingEt() const override;

    virtual Momentum GetScalarHt() const override;

};

}

}
