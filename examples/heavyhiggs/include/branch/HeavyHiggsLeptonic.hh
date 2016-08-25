#pragma once

#include "boca/branch/TwoBody.hh"

namespace heavyhiggs
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
 * @brief Higgs tagger root tree structure
 *
 */
class HeavyHiggsLeptonic : public boca::branch::TwoBody
{

public:

    HeavyHiggsLeptonic();

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


    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
//         LargerWDeltaR = multiplet.GetLargertripletDeltaR() / rad;
//         LargerWDeltaRap = multiplet.GetLargertripletDeltaRap() / rad;
//         LargerWDeltaPhi = multiplet.GetLargerTripleDeltaPhi() / rad;
//         SmallerWDeltaR = multiplet.GetSmallertripletDeltaR() / rad;
//         SmallerWDeltaRap = multiplet.GetSmallertripletDeltaRap() / rad;
//         SmallerWDeltaPhi = multiplet.GetSmallertripletDeltaPhi() / rad;
//         LargerNeutrinoDeltaR = multiplet.GetLargertripletDeltaR() / rad;
//         LargerNeutrinoDeltaRap = multiplet.GetLargertripletDeltaRap() / rad;
//         LargerNeutrinoDeltaPhi = multiplet.GetLargerTripleDeltaPhi() / rad;
//         SmallerNeutrinoDeltaR = multiplet.GetSmallertripletDeltaR() / rad;
//         SmallerNeutrinoDeltaRap = multiplet.GetSmallertripletDeltaRap() / rad;
//         SmallerNeutrinoDeltaPhi = multiplet.GetSmallertripletDeltaPhi() / rad;
    }

    Observables Variables();

private:

    ClassDef(HeavyHiggsLeptonic, 1)

};

}

}
