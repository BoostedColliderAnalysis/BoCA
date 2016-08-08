#pragma once

#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"
#include "boca/branch/Cut.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

class Cut : public boca::branch::Cut
{

public:

    Cut();
    float Ht;
    float EtMiss;
    float NumberJet;
    float NumberBottom;
    float InvariantMass;
    float DeltaR;
    float LeptonPt1;
    float LeptonPt2;
    float BottomMinPt;
    float BottomMaxRap;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Cut::Fill(multiplet);
        Ht = multiplet.Ht() / GeV;
        EtMiss = multiplet.EtMiss() / GeV;
        NumberJet = multiplet.JetNumber();
        NumberBottom = multiplet.BottomNumber();
        InvariantMass = multiplet.InvariantMass() / GeV;
        DeltaR = multiplet.DeltaR() / rad;
        LeptonPt1 = multiplet.LeptonPt(1) / GeV;
        LeptonPt2 = multiplet.LeptonPt(2) / GeV;
        BottomMinPt = multiplet.BottomMinPt() / GeV;
        BottomMaxRap = multiplet.BottomMaxRap() / rad;
    }
    virtual Observables Variables();

private:

    ClassDef(Cut, 1)

};

}

}
