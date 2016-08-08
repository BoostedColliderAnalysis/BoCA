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
class EventCharged : public boca::branch::Event
{

public:

    EventCharged();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        Event::Fill(event);
        HiggsMass = event.Signature().Quartet1().Mass() / GeV;
        HiggsBdt = event.Signature().Quartet1().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Quartet2().DeltaRap() / rad;
    }

    Observables Variables();

private:

    ClassDef(EventCharged, 1)

};

}

}
