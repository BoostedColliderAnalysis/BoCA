#pragma once

#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"
#include "boca/branch/Cut.hh"

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
        HiggsMass = event.Signature().Sextet().Mass() / GeV;
        HiggsBdt = event.Signature().Sextet().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Doublet().DeltaRap() / rad;
        HardTopPt = event.Signature().Sextet().HardTopPt() / GeV;
        SoftTopPt = event.Signature().Sextet().SoftTopPt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventNeutralFourTop, 1)

};

}

}
