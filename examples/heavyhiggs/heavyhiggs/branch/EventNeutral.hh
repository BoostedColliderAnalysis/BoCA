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
class EventNeutral : public boca::branch::Event
{

public:

    EventNeutral();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;
    float HardTopPt;
    float SoftTopPt;

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        Event::Fill(event);
        HiggsMass = event.Signature().Sextet().Mass() / GeV;
        HiggsBdt = event.Signature().Sextet().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Doublet().DeltaRap() / rad;
        HardTopPt = event.Signature().Sextet().HarderComponent().Pt() / GeV;
        SoftTopPt = event.Signature().Sextet().SofterComponent().Pt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventNeutral, 1)

};

}

}
