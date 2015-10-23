/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include "Particles.hh"
#include "fastjet/PseudoJet.hh"

namespace boca
{

using Jets = std::vector<fastjet::PseudoJet>;

class SubJet
{
public:
    SubJet(boca::Id id);
    boca::Id Id() const;
private:
    boca::Id id_;
};

class MomentumRange
{
public:
    MomentumRange();
    MomentumRange(Momentum min, Momentum max);
    MomentumRange(Id max);
    MomentumRange(Id min, Id max);
    MomentumRange(Id min, SubJet const& max);
    MomentumRange(SubJet const& min, SubJet const& max);
    MomentumRange(SubJet const& min);
    void Set(Momentum min, Momentum max);
    Momentum Min() const;
    Momentum Max() const;
    Momentum PtMin(Id id);
    Momentum PtMax(Id id);
    Momentum PtMin(SubJet const& id);
    Momentum PtMax(SubJet const& id);
    template <typename Multiplet>
    bool UpperBound(Multiplet const& multiplet) const {
        return multiplet.Pt() < max_;
    }
    template <typename Multiplet>
    bool LowerBound(Multiplet const& multiplet) const {
        return multiplet.Pt() > min_;
    }
    bool UpperBound(fastjet::PseudoJet const& jet) const;
    bool LowerBound(fastjet::PseudoJet const& jet) const;
    bool Bounds(fastjet::PseudoJet const& jet) const;
    Jets Soft(Jets const& jets) const;
    Jets Hard(Jets const& jets) const;
private:
    Momentum min_ = at_rest;
    Momentum max_ = at_rest;
    Momentum Pt(Id id, float cone_size);
    Momentum PtMin(Id id, float cone_size);
    Momentum PtMax(Id id, float cone_size);
};

}
