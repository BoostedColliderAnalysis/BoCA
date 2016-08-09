#pragma once

#include "boca/branch/ThreeBody.hh"
#include "boca/branch/EventShapesBase.hh"

namespace toppartner
{

namespace branch
{

class SignatureSingleHadronicBranch : public boca::branch::ThreeBody, public boca::branch::EventShapesBase
{
public:
    SignatureSingleHadronicBranch();
    float veto_bdt;
    float top_pt;
    float higgs_pt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
        EventShapesBase::Fill(multiplet);
        veto_bdt = multiplet.VetoBdt();
        top_pt = multiplet.Triplet().Pt() / boca::GeV;
        higgs_pt = multiplet.Doublet().Pt() / boca::GeV;
    }
    boca::Observables Variables();
    boca::Observables Spectators();
private:
    ClassDef(SignatureSingleHadronicBranch, 1)
};

}

}
