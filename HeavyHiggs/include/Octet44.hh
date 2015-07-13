#pragma once

#include "Quartet.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet44 : public analysis::Multiplet<analysis::Quartet31, analysis::Quartet31>
{

public:

    using analysis::Multiplet<analysis::Quartet31, analysis::Quartet31>::Multiplet;

     analysis::Quartet31 Quartet1() const {
        return Multiplet1();
    }

     analysis::Quartet31 Quartet2() const {
        return Multiplet2();
    }

     float BottomBdt() const {
        return Quartet1().Singlet().UserInfo().Bdt() + Quartet1().Triplet().Singlet().UserInfo().Bdt() + Quartet2().Singlet().UserInfo().Bdt() + Quartet2().Triplet().Singlet().UserInfo().Bdt();
    }

     float PairBottomBdt() const {
        return Quartet2().Singlet().UserInfo().Bdt() + Quartet2().Triplet().Singlet().UserInfo().Bdt();
    }

};

}

}
