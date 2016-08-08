#pragma once

#include "boca/branch/ThreeBody.hh"

namespace toppartner
{

namespace branch
{

class SignatureSingle : public ::boca::branch::ThreeBody
{
public:
    SignatureSingle();
    float veto_bdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
        veto_bdt = multiplet.VetoBdt();
    }
    boca::Observables Variables();
private:
    ClassDef(SignatureSingle, 1)
};

}

using SignatureSingleBranch = branch::SignatureSingle;

}
