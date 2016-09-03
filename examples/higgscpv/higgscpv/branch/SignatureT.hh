#pragma once

#include "boca/branch/ThreeBody.hh"

namespace higgscpv
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureT : public boca::branch::ThreeBody
{
public:
  SignatureT();
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        boca::branch::ThreeBody::Fill(signature.Multiplet());
        Aplanarity = signature.EventShapes().Aplanarity();
        Sphericity = signature.EventShapes().Sphericity();
    }
    Observables Variables();
private:
    ClassDef(SignatureT, 1)
};

}

}
