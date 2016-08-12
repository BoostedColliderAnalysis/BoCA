#pragma once

#include "boca/branch/TwoBody.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class JetPair : public boca::branch::TwoBody
{
public:
    JetPair();
    float Jet1Mass;
    float Jet1Pt;
    float Jet1Rap;
    float Jet1Phi;
    float Jet2Mass;
    float Jet2Pt;
    float Jet2Rap;
    float Jet2Phi;
    //     float BdtRatio11;
    //     float BdtRatio12;
    //     float BdtRatio13;
    //     float BdtRatio14;
    //     float BdtRatio21;
    //     float BdtRatio22;
    //     float BdtRatio23;
    //     float BdtRatio24;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        Jet1Pt = multiplet.Singlet1().Pt() / GeV;
        Jet1Rap = multiplet.Singlet1().Rap() / rad;
        Jet1Phi = multiplet.Singlet1().Phi() / rad;
        Jet1Mass = multiplet.Singlet1().Mass() / GeV;
        Jet2Pt = multiplet.Singlet2().Pt() / GeV;
        Jet2Rap = multiplet.Singlet2().Rap() / rad;
        Jet2Phi = multiplet.Singlet2().Phi() / rad;
        Jet2Mass = multiplet.Singlet2().Mass() / GeV;
    }
    Observables Variables();

private:
    ClassDef(JetPair, 1)
};

}

}
