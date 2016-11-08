#pragma once

#include "boca/branch/Cut.hh"
#include "boca/units/Prefixes.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

class CutNeutral : public boca::branch::Cut
{

public:

    CutNeutral();
    float JetPt1;
    float JetPt2;
    float JetPt3;
    float JetPt4;
    float Ht;
    float BottomNumber;
    float LeptonPt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Cut::Fill(multiplet);
//         Bdt::Fill(multiplet);
        JetPt1 = multiplet.JetPt(0) / GeV;
        JetPt2 = multiplet.JetPt(1) / GeV;
        JetPt3 = multiplet.JetPt(2) / GeV;
        JetPt4 = multiplet.JetPt(3) / GeV;
        LeptonPt = multiplet.LeptonPt(0) / GeV;
        Ht = multiplet.Ht() / GeV;
        BottomNumber = multiplet.BottomNumber();
    }
    virtual Observables Variables();

private:

    ClassDef(CutNeutral, 1)

};

}

}
