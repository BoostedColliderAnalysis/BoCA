#pragma once

#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"
#include "boca/branch/Cut.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HeavyHiggsTau : public boca::branch::TwoBody
{

public:

    HeavyHiggsTau();

    float LeptonPt;
    float NeutrinoPt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        LeptonPt = multiplet.Singlet1().Pt() / GeV;
        NeutrinoPt = multiplet.Singlet2().Pt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(HeavyHiggsTau, 1)

};

}

}
