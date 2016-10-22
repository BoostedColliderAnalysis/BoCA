#pragma once

#include "boca/branch/Signature.hh"

namespace toppartner
{

namespace branch
{

class SignatureSingle : public boca::branch::Signature
{
public:
    SignatureSingle();
    float veto_bdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Signature::Fill(multiplet);
        veto_bdt = multiplet.ExtraInfo();
    }
    boca::Observables Variables();
private:
    ClassDef(SignatureSingle, 1)
};

}

using SignatureSingleBranch = branch::SignatureSingle;

}
