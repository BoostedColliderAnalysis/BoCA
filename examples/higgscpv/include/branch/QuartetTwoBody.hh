#pragma once

#include "boca/branch/TwoBody.hh"

namespace higgscpv
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class QuartetTwoBody : public boca::branch::TwoBody
{

    QuartetTwoBody();

    float BottomMass;
    float BottomPt;
    float BottomRap;
    float BottomPhi;
    float BottomBdt;
    float BottomBTag;

    float TopMass;
    float TopPt;
    float TopRap;
    float TopPhi;
    float TopBdt;
    float TopBTag;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::branch::TwoBody::Fill(multiplet);
        BottomPt = multiplet.Doublet1().Pt() / GeV;
        //         BottomRap = std::abs(multiplet.Rap() / rad);
        BottomRap = multiplet.Doublet1().Rap() / rad;
        BottomPhi = multiplet.Doublet1().Phi() / rad;
        BottomMass = multiplet.Doublet1().Mass() / GeV;
        //         BottomBdt = multiplet.Info().Bdt();
        TopPt = multiplet.Doublet2().Pt() / GeV;
        //         TopRap = std::abs(multiplet.triplet().Rap() / rad);
        TopRap = multiplet.Doublet2().Rap() / rad;
        TopPhi = multiplet.Doublet2().Phi() / rad;
        TopMass = multiplet.Doublet2().Mass() / GeV;
        TopBdt = multiplet.Doublet2().Bdt();
    }

private:

    ClassDef(QuartetTwoBody, 1)

};

}

}
