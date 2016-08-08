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
 * @brief Higgs tagger root tree structure
 *
 */
class TripletTwoBody : public boca::branch::TwoBody
{
public:
    TripletTwoBody();
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
        BottomPt = multiplet.Triplet1().Pt() / GeV;
        //         BottomRap = std::abs(multiplet.Rap() / rad);
        BottomRap = multiplet.Triplet1().Rap() / rad;
        BottomPhi = multiplet.Triplet1().Phi() / rad;
        BottomMass = multiplet.Triplet1().Mass() / GeV;
        //         BottomBdt = multiplet.Info().Bdt();
        TopPt = multiplet.Triplet2().Pt() / GeV;
        //         TopRap = std::abs(multiplet.triplet().Rap() / rad);
        TopRap = multiplet.Triplet2().Rap() / rad;
        TopPhi = multiplet.Triplet2().Phi() / rad;
        TopMass = multiplet.Triplet2().Mass() / GeV;
        TopBdt = multiplet.Triplet2().Bdt();
    }
    Observables Variables();

private:
    ClassDef(TripletTwoBody, 1)
};

}

}
