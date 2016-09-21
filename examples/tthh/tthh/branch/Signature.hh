#pragma once

#include "boca/branch/Signature.hh"

namespace tthh
{

namespace branch
{

class Signature : public boca::branch::Signature
{
public:
    Signature();
    float veto_bdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::branch::Signature::Fill(multiplet);
        veto_bdt = multiplet.VetoBdt();
    }
    boca::Observables Variables();
private:
    ClassDef(Signature, 1)
};

}

}
