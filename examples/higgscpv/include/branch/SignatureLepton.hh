#pragma once

#include "boca/branch/ThreeBody.hh"
#include "boca/branch/TwoBody.hh"
#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"

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
class SignatureLepton : public boca::branch::Multi
{
public:
    SignatureLepton();
    float Mass12;
    float Mass23;
    float Mass13;
    float Pt12;
    float Pt23;
    float Pt13;
    float DeltaPt23;
    float DeltaPt13;
    float Ht12;
    float Ht23;
    float Ht13;
    float Rho23;
    float Rho13;
    float DeltaRap23;
    float DeltaRap13;
    float DeltaPhi23;
    float DeltaPhi13;
    float DeltaR23;
    float DeltaR13;
    float DeltaM23;
    float DeltaM13;
    float DeltaHt23;
    float DeltaHt13;
    float Pull23;
    float Pull13;
    float DeltaPull23;
    float DeltaPull13;
//     float Dipolarity23;
//     float Dipolarity13;
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        auto signature = multiplet.Multiplet();
//         boca::branch::Multi::Fill(signature);
        Mass12 = signature.Multiplet12().Mass() / GeV;
        Mass23 = signature.Multiplet23().Mass() / GeV;
        Mass13 = signature.Multiplet13().Mass() / GeV;
        Pt12 = signature.Multiplet12().Pt() / GeV;
        Pt23 = signature.Multiplet23().Pt() / GeV;
        Pt13 = signature.Multiplet13().Pt() / GeV;
        DeltaPt23 = signature.Multiplet23().DeltaPt() / GeV;
        DeltaPt13 = signature.Multiplet13().DeltaPt() / GeV;
        Ht12 = signature.Multiplet12().Ht() / GeV;
        Ht23 = signature.Multiplet23().Ht() / GeV;
        Ht13 = signature.Multiplet13().Ht() / GeV;
        Rho23 = signature.Multiplet23().Rho();
        Rho13 = signature.Multiplet13().Rho();
        DeltaRap23 = signature.Multiplet23().DeltaRap() / rad;
        DeltaRap13 = signature.Multiplet13().DeltaRap() / rad;
        DeltaPhi23 = signature.Multiplet23().DeltaPhi() / rad;
        DeltaPhi13 = signature.Multiplet13().DeltaPhi() / rad;
        DeltaR23 = signature.Multiplet23().DeltaR() / rad;
        DeltaR13 = signature.Multiplet13().DeltaR() / rad;
        DeltaM23 = signature.Multiplet23().DeltaM() / GeV;
        DeltaM13 = signature.Multiplet13().DeltaM() / GeV;
        DeltaHt23 = signature.Multiplet23().DeltaHt() / GeV;
        DeltaHt13 = signature.Multiplet13().DeltaHt() / GeV;
//         Pull23 = signature.Multiplet23().Pull() / rad;
//         Pull13 = signature.Multiplet13().Pull() / rad;
//         DeltaPull23 = signature.Multiplet32().Pull() / rad;
//         DeltaPull13 = signature.Multiplet31().Pull() / rad;
//         Dipolarity23 = signature.Multiplet().Dipolarity23();
//         Dipolarity13 = signature.Multiplet().Dipolarity13();
        Aplanarity = signature.EventShapes().Aplanarity();
        Sphericity = signature.EventShapes().Sphericity();
    }
    Observables Variables();

private:
    ClassDef(SignatureLepton, 1)
};

}

}
