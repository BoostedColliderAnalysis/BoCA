#pragma once
#include "EventShapes.hh"
#include "fastjet/PseudoJet.hh"

namespace analysis{

  class EventShape{

  public:
    EventShape(){
      event_shapes_ = new analysis::EventShapes;
    }

    ~EventShape(){
      // FIXME memory leak!!
      // why can I not delete this
//       delete event_shapes_;
    }

    void SetJets(const std::vector<fastjet::PseudoJet>& jets);

    float Sphericity() const;

    float Aplanarity() const;

    const analysis::EventShapes& EventShapes() const{
      return *event_shapes_;
    }

  private:

    analysis::EventShapes& EventShapes(){
      return *event_shapes_;
    }

    analysis::EventShapes *event_shapes_;

  };

}
