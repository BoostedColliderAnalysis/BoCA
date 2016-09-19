#pragma once

#include "boca/branch/Event.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

  class EventNeutralFourTop : public boca::branch::Event
{

public:

    EventNeutralFourTop();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;

    float HardTopPt;
    float SoftTopPt;

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        Event::Fill(event);
        HiggsMass = event.Signature().Sextet33().Mass() / GeV;
        HiggsBdt = event.Signature().Sextet33().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Doublet().DeltaRap() / rad;
        HardTopPt = event.Signature().Sextet33().HarderComponent().Pt() / GeV;
        SoftTopPt = event.Signature().Sextet33().SofterComponent().Pt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventNeutralFourTop, 1)

};

}

}
