#pragma once

#include "boca/branch/ThreeBody.hh"

namespace toppartner
{

namespace branch
{

class SignatureSingleBranch : public ::boca::branch::ThreeBody
{
public:
    SignatureSingleBranch();
    float veto_bdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
        veto_bdt = multiplet.VetoBdt();
    }
    boca::Observables Variables();
private:
    ClassDef(SignatureSingleBranch, 1)
};

}

}
