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
class TripletJetPair : public boca::branch::TwoBody
{

public:

    TripletJetPair();
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
        TwoBody::Fill(multiplet);
        BottomPt = multiplet.Singlet().Pt() / GeV;
        //         BottomRap = std::abs(multiplet.Singlet().rap());
        BottomRap = multiplet.Singlet().Rap() / rad;
        BottomPhi = multiplet.Singlet().Phi() / rad;
        BottomMass = multiplet.Singlet().Mass() / GeV;
        //         BottomBdt = multiplet.Singlet().Info().Bdt();
        TopPt = multiplet.Triplet().Pt() / GeV;
        //         TopRap = std::abs(multiplet.Triplet().rap());
        TopRap = multiplet.Triplet().Rap() / rad;
        TopPhi = multiplet.Triplet().Phi() / rad;
        TopMass = multiplet.Triplet().Mass() / GeV;
        TopBdt = multiplet.Triplet().Bdt();
    }
    Observables Variables();

private:

    ClassDef(TripletJetPair, 1)

};

}

}
