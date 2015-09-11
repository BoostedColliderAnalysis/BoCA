/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include "EventShapes.hh"

namespace fastjet{
  class PseudoJet;
}

namespace boca{

  class EventShape{

  public:
    EventShape(){
      event_shapes_ = new boca::EventShapes;
    }

    virtual ~EventShape(){
      // FIXME memory leak!!
      // why can I not delete this
//       delete event_shapes_;
    }

    void SetJets(const std::vector<fastjet::PseudoJet>& jets);

    float Sphericity() const;

    float Aplanarity() const;

    const boca::EventShapes& EventShapes() const{
      return *event_shapes_;
    }

  private:

    boca::EventShapes& EventShapes(){
      return *event_shapes_;
    }

    boca::EventShapes *event_shapes_;

  };

}
