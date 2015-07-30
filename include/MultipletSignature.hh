#pragma once

#include "EventShape.hh"
#include "Multiplet.hh"

namespace analysis {

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_1>
class MultipletSignature : public Identification {

public:

  MultipletSignature(const Multiplet_1& multiplet) {
        multiplet_ = multiplet;
        event_shape_.SetJets(multiplet.Jets());

    }

    const Multiplet_1 &Multiplet() const
    {
      return multiplet_;
    }

    const analysis::EventShape& EventShape() const
    {
        return event_shape_;
    }

private:

  analysis::EventShape event_shape_;

  Multiplet_1 multiplet_;

};

}


