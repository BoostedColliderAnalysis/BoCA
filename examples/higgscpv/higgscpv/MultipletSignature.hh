/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/event/EventShapes.hh"

namespace boca
{

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_1>
class MultipletSignature : public Identification
{

public:

    MultipletSignature(Multiplet_1 const& multiplet) :
        event_shapes_(multiplet.Jets()) {
        multiplet_ = multiplet;
    }

    Multiplet_1 const& Multiplet() const {
        return multiplet_;
    }

    boca::EventShapes const& EventShapes() const {
        return event_shapes_;
    }

private:

    boca::EventShapes event_shapes_;

    Multiplet_1 multiplet_;

};

}
