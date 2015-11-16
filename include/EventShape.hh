/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include <memory>
#include "EventShapes.hh"

namespace fastjet
{
class PseudoJet;
}

namespace boca
{

class EventShape
{

public:
  
    EventShape() :  event_shapes_(std::make_shared<boca::EventShapes>()) {}

    void SetJets(std::vector<fastjet::PseudoJet> const& jets);

    float Sphericity() const;

    float Aplanarity() const;

    boca::EventShapes const& EventShapes() const {
        return *event_shapes_.get();
    }

private:

    boca::EventShapes& EventShapes() {
        return *event_shapes_.get();
    }

    std::shared_ptr<boca::EventShapes> event_shapes_;

};

}
