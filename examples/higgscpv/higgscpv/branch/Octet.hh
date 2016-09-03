#pragma once

#include "boca/branch/Multi.hh"

namespace higgscpv
{

using namespace boca;

/**
* @brief Branches
*
*/
namespace branch
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class Octet : public boca::branch::Multi
{
public:
    Octet();
    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HiggsBdt;
    float PairBdt;
    float HardTopPt;
    float SoftTopPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::branch::Multi::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.PairBottomBdt();
        PairBdt = multiplet.Doublet().Bdt();
        HiggsBdt = multiplet.Sextet().Bdt();
        HardTopPt = multiplet.Sextet().HarderComponent().Pt() / GeV;
        SoftTopPt = multiplet.Sextet().SofterComponent().Pt() / GeV;
        HiggsMass = multiplet.Sextet().Mass() / GeV;
        PairRap = multiplet.Doublet().DeltaRap() / rad;
    }
private:
    ClassDef(Octet, 1)
};

}

}
