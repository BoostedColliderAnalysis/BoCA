/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/units/cmath.hpp>
#include "multiplets/Triplet.hh"

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

    Momentum HardTopPt() const {
        return std::max(Triplet1().Pt(), Triplet2().Pt());
    }

    Momentum SoftTopPt() const {
        return std::min(Triplet1().Pt(), Triplet2().Pt());
    }

    Angle GetLargertripletDeltaR() const {
        return std::max(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    Angle GetSmallertripletDeltaR() const {
        return std::min(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    Angle GetLargertripletDeltaRap() const {
        return std::max(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    Angle GetSmallertripletDeltaRap() const {
        return std::min(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    Angle GetLargerTripleDeltaPhi() const {
        return std::max(boost::units::abs(Triplet1().DeltaPhi()), boost::units::abs(Triplet2().DeltaPhi()));
    }

    Angle GetSmallertripletDeltaPhi() const {
        return std::min(boost::units::abs(Triplet1().DeltaPhi()), boost::units::abs(Triplet2().DeltaPhi()));
    }

    boca::Mass GetBetterTripleMass(Id id) const {
        return boost::units::fmin(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
    }

    boca::Mass GetWorseTripleMass(Id id) const {
        return boost::units::fmax(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
    }

    boca::Mass GetBetterPairMass(Id id) const {
        return boost::units::fmin(Triplet1().Doublet().MassDifferenceTo(id), Triplet2().Doublet().MassDifferenceTo(id));
    }

    boca::Mass GetWorsePairMass(Id id) const {
        return boost::units::fmax(Triplet1().Doublet().MassDifferenceTo(id), Triplet2().Doublet().MassDifferenceTo(id));
    }

    boca::Mass GetBetterJetMass(Id id) const {
        return boost::units::fmin(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
    }

    boca::Mass GetWorseJetMass(Id id) const {
        return boost::units::fmax(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
    }

};

}
