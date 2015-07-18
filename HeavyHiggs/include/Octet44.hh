#pragma once

#include "Quartet.hh"

namespace analysis {

namespace heavyhiggs {

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet44 : public analysis::Multiplet<analysis::Quartet31, analysis::Quartet31> {

public:

    using analysis::Multiplet<analysis::Quartet31, analysis::Quartet31>::Multiplet;

    analysis::Quartet31 Quartet1() const;

    analysis::Quartet31 Quartet2() const;

    float BottomBdt() const;

    float PairBottomBdt() const;

};

}

}
