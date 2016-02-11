/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include "physics/Particles.hh"
#include "Vector.hh"

namespace boca
{

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

    bool BelowUpperBound(Jet const& jet) const;
    template <typename Multiplet>
    bool AboveLowerBound(Multiplet const& multiplet) const {
        return multiplet.Pt() > min_;
    }

    bool AboveLowerBound(Jet const& jet) const;
    template <typename Multiplet>
    bool InsideRange(Multiplet const& multiplet) const {
        return AboveLowerBound(multiplet) && BelowUpperBound(multiplet);
    }

    template <typename Multiplet>
    std::vector<Multiplet> SofterThanMax(std::vector<Multiplet> const& multiplet) const {
        return RemoveIfHard(multiplet, max_);
    }

    template <typename Multiplet>
    std::vector<Multiplet> HarderThanMin(std::vector<Multiplet> const& multiplet) const {
        return RemoveIfSoft(multiplet, min_);
    }

    template <typename Multiplet>
    std::vector<Multiplet> InsidePtWindow(std::vector<Multiplet> const& multiplet) const {
        return RemoveIfHard(RemoveIfSoft(multiplet, min_), max_);
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

};

}
