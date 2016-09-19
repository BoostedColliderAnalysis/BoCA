#pragma once

#include "boca/branch/Multi.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetNeutral : public boca::branch::Multi
{

public:

    OctetNeutral();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float PairBdt;
    float HardTopPt;
    float SoftTopPt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        PairBdt = multiplet.Doublet().Bdt();
        HiggsBdt = multiplet.Sextet33().Bdt();
        HardTopPt = multiplet.Sextet33().HarderComponent().Pt() / GeV;
        SoftTopPt = multiplet.Sextet33().SofterComponent().Pt() / GeV;
        HiggsMass = multiplet.Sextet33().Mass() / GeV;
        PairRap = multiplet.Doublet().DeltaRap() / rad;
    }

    Observables Variables();

private:

    ClassDef(OctetNeutral, 1)

};

}

}
