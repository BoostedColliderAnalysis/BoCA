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
class OctetCharged : public boca::branch::Multi
{

public:

    OctetCharged();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float PairBdt;


    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        HiggsBdt = multiplet.Quartet1().Bdt();
        PairBdt = multiplet.Quartet2().Bdt();
        HiggsMass = multiplet.Quartet1().Mass() / GeV;
        PairRap = multiplet.Quartet2().DeltaRap() / rad;
    }

    Observables Variables();

private:

    ClassDef(OctetCharged, 1)

};

}

}
