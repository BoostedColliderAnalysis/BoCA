/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Triplet.hh"

namespace boca
{

/**
 * @brief A sextet of 2 triplets
 *
 */
class Sextet : public TwoBody<Triplet, Triplet>
{

public:

    using TwoBody<Triplet, Triplet>::TwoBody;

    Triplet const& Triplet1() const;

    Triplet const& Triplet2() const;

    Triplet & Triplet1();

    Triplet & Triplet2();

    Momentum HardTopPt() const;

    Momentum SoftTopPt() const;

    Angle GetLargertripletDeltaR() const;

    Angle GetSmallertripletDeltaR() const;

    Angle GetLargertripletDeltaRap() const;

    Angle GetSmallertripletDeltaRap() const;

    Angle GetLargerTripleDeltaPhi() const;

    Angle GetSmallertripletDeltaPhi() const;

    boca::Mass GetBetterTripleMass(Id id) const;

    boca::Mass GetWorseTripleMass(Id id) const;

    boca::Mass GetBetterPairMass(Id id) const;

    boca::Mass GetWorsePairMass(Id id) const;

    boca::Mass GetBetterJetMass(Id id) const;

    boca::Mass GetWorseJetMass(Id id) const;

};

}
