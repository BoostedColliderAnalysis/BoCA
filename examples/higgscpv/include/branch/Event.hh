#pragma once

#include "boca/branch/Event.hh"

namespace higgscpv
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class Event : public boca::branch::Event
{

public:

    Event();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
//       boca::branch::Event::Fill(multiplet);
    }
    Observables Variables();
    Observables Spectators();

private:

    ClassDef(Event, 1)

};

}

}
