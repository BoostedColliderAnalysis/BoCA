/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <boost/units/cmath.hpp>
#include "Triplet.hh"

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

    float HardTopPt() const {
        return std::max(Triplet1().Pt(), Triplet2().Pt()) / GeV;
    }

    float SoftTopPt() const {
        return std::min(Triplet1().Pt(), Triplet2().Pt()) / GeV;
    }

    float GetLargertripletDeltaR() const {
        return std::max(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    float GetSmallertripletDeltaR() const {
        return std::min(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    float GetLargertripletDeltaRap() const {
        return std::max(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    float GetSmallertripletDeltaRap() const {
        return std::min(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    float GetLargerTripleDeltaPhi() const {
        return std::max(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

    float GetSmallertripletDeltaPhi() const {
        return std::min(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
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
