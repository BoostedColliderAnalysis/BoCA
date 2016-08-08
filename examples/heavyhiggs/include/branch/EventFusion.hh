#pragma once

#include "boca/branch/Event.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventFusion : public boca::branch::Event
{

public:

    EventFusion();


    float HiggsMass;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Event::Fill(multiplet);
        HiggsMass = multiplet.Mass() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventFusion, 1)

};

}

}
