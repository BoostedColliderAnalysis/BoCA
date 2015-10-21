/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "DetectorGeometry.hh"
#include "Particles.hh"
#include "Math.hh"

namespace boca
{

class SubJet
{
public:
    SubJet(boca::Id id) {
        id_ = id;
    }
    boca::Id Id() {
        return id_;
    }
    boca::Id id_;
};

class MomentumRange
{
public:
    MomentumRange() {};
    MomentumRange(Momentum min, Momentum max) {
        Set(min, max);
    };
    MomentumRange(Id max) {
        Set(at_rest, PtMax(max));
    };
    MomentumRange(Id min, Id max) {
        Set(PtMin(min), PtMax(max));
    };
    MomentumRange(Id min, SubJet max) {
        Set(PtMin(min), PtMax(max));
    };
    MomentumRange(SubJet min, SubJet max) {
        Set(PtMin(min), PtMax(max));
    };
    MomentumRange(SubJet min) {
        Set(PtMin(min), double(LargeNumber()) * GeV);
    };
    void Set(Momentum min, Momentum max) {
        min_ = min;
        max_ = max;
    }
    Momentum Min() const {
        return min_;
    }
    Momentum Max() const {
        return max_;
    }
    static Momentum PtMin(Id id) {
        return 0.8 * MassOf(id) * (2. / DetectorGeometry::JetConeSize());
    }
    static Momentum PtMax(Id id) {
        return 1.2 * MassOf(id) * (2. / DetectorGeometry::JetConeSize());
    }
    static Momentum PtMin(SubJet id) {
        return 0.8 * MassOf(id.Id()) * (2. / DetectorGeometry::MinCellResolution());
    }
    static Momentum PtMax(SubJet id) {
        return 1.2 * MassOf(id.Id()) * (2. / DetectorGeometry::MinCellResolution());
    }
    bool UpperBound(fastjet::PseudoJet const& jet) const {
        return jet.pt() * GeV < max_;
    }
    bool LowerBound(fastjet::PseudoJet const& jet) const {
        return jet.pt() * GeV > min_;
    }
    bool Bounds(fastjet::PseudoJet const& jet) const {
        return LowerBound(jet) && UpperBound(jet);
    }
private:
    Momentum min_ = at_rest;
    Momentum max_ = at_rest;
};

}
