#pragma once

#include "higgscpv/branch/SignatureT.hh"

namespace higgscpv
{

using namespace boca;

namespace branch
{

class SignatureLeptonT : public SignatureT
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        SignatureT::Fill(signature);
    }
    Observables Variables();

private:
    ClassDef(SignatureLeptonT, 1)
};

}

}
