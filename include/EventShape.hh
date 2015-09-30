/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
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
    EventShape() : event_shapes_(new boca::EventShapes) {}

    virtual ~EventShape() {
      //FIXME memory leak
        delete event_shapes_;
        event_shapes_ = nullptr;
    }
//     friend void swap(EventShape& first, EventShape& second) {
//         std::swap(first.event_shapes_, second.event_shapes_);
//     }
//
//     EventShape& operator=(EventShape event_shape) {
//         swap(*this, event_shape);
//         return *this;
//     }
//
//     EventShape(EventShape const& event_shape) :  event_shapes_(new boca::EventShapes) {
//       event_shapes_ = event_shape.event_shapes_;
// //       std::copy(event_shape.event_shapes_, event_shape.event_shapes_ + 1, event_shapes_);
//     }
//
//     EventShape(EventShape && event_shape) : EventShape() {
//         swap(*this, event_shape);
//     }

    void SetJets(const std::vector<fastjet::PseudoJet>& jets);

    float Sphericity() const;

    float Aplanarity() const;

    const boca::EventShapes& EventShapes() const {
        return *event_shapes_;
    }

private:


    boca::EventShapes& EventShapes() {
        return *event_shapes_;
    }

    boca::EventShapes* event_shapes_;

};

}
