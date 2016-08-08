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
 * @brief Higgs tagger root tree structure
 *
 */
class ChargedHiggsLeptonic : public boca::branch::Multi
{

public:

    ChargedHiggsLeptonic();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float LargerWDeltaRap;
    float LargerWDeltaPhi;
    float LargerWDeltaR;

    float SmallerWDeltaRap;
    float SmallerWDeltaPhi;
    float SmallerWDeltaR;

    float LargerNeutrinoDeltaRap;
    float LargerNeutrinoDeltaPhi;
    float LargerNeutrinoDeltaR;

    float SmallerNeutrinoDeltaRap;
    float SmallerNeutrinoDeltaPhi;
    float SmallerNeutrinoDeltaR;

    float TopBdt;

    float HeavyHiggsTag;


    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        HeavyHiggsMass = multiplet.Mass() / GeV;
        HeavyHiggsPt = multiplet.Mass() / GeV;
        TopDeltaR = multiplet.DeltaR() / rad;
        TopDeltaRap = multiplet.DeltaRap() / rad;
        TopDeltaPhi = multiplet.DeltaPhi() / rad;
        TopBdt = multiplet.Bdt();
        HeavyHiggsTag = static_cast<int>(multiplet.Tag());
    }

    Observables Variables();
    Observables Spectators();

private:

    ClassDef(ChargedHiggsLeptonic, 1)

};

}

}
