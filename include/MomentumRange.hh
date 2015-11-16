/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include "Particles.hh"
#include "fastjet/PseudoJet.hh"
#include "Vector.hh"

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
    MomentumRange(Id max);
    MomentumRange(Id min, Id max);
    MomentumRange(Id min, SubJet const& max);
    MomentumRange(SubJet const& min, SubJet const& max);
    MomentumRange(SubJet const& min);
    void Set(Momentum min, Momentum max);
    Momentum Min() const;
    Momentum Max() const;
    template <typename Multiplet>
    bool BelowUpperBound(Multiplet const& multiplet) const {
        return multiplet.Pt() < max_;
    }
    bool BelowUpperBound(fastjet::PseudoJet const& jet) const;
    template <typename Multiplet>
    bool AboveLowerBound(Multiplet const& multiplet) const {
        return multiplet.Pt() > min_;
    }
    bool AboveLowerBound(fastjet::PseudoJet const& jet) const;
    template <typename Multiplet>
    bool InsideBounds(Multiplet const& multiplet) const {
        return AboveLowerBound(multiplet) && BelowUpperBound(multiplet);
    }
    template <typename Multiplet>
    Multiplet SofterThanMax(const Multiplet& multiplet) const {
        return RemoveIfHard(multiplet, max_);
    }
    template <typename Multiplet>
    Multiplet HarderThanMin(const Multiplet& multiplet) const {
        return RemoveIfSoft(multiplet, min_);
    }
private:
    Momentum PtMin(Id id);
    Momentum PtMax(Id id);
    Momentum PtMin(SubJet const& id);
    Momentum PtMax(SubJet const& id);
    Momentum PtMin(Id id, Angle cone_size);
    Momentum PtMax(Id id, Angle cone_size);
    Momentum Pt(Id id, Angle cone_size);
    Momentum min_ = at_rest;
    Momentum max_ = at_rest;
    float Smearing() const;
    double SmearingMin() const;
    double SmearingMax() const;
};

}
