/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "EventShapes.hh"
#include "Identification.hh"

namespace boca {

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_1>
class MultipletSignature : public Identification {

public:

  MultipletSignature(Multiplet_1 const& multiplet) {
        multiplet_ = multiplet;
        event_shape_.reset(multiplet.Jets());

    }

    const Multiplet_1 &Multiplet() const
    {
      return multiplet_;
    }

    const boca::EventShape& EventShape() const
    {
        return event_shape_;
    }

private:

  boca::EventShapes event_shape_;

  Multiplet_1 multiplet_;

};

}


