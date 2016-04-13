/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include "physics/Particles.hh"
#include "generic/Vector.hh"
#include "multiplets/Jet.hh"

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
    void Set(const boca::Momentum& min, boca::Momentum const& max);
    Momentum Min() const;
    Momentum Max() const;

    template <typename Multiplet_>
    bool BelowUpperBound(Multiplet_ const& multiplet) const {
        return multiplet.Pt() < max_;
    }

    bool BelowUpperBound(Jet const& jet) const;
    template <typename Multiplet_>
    bool AboveLowerBound(Multiplet_ const& multiplet) const {
        return multiplet.Pt() > min_;
    }

    bool AboveLowerBound(Jet const& jet) const;
    template <typename Multiplet_>
    bool InsideRange(Multiplet_ const& multiplet) const {
        return AboveLowerBound(multiplet) && BelowUpperBound(multiplet);
    }

    template <typename Multiplet_>
    std::vector<Multiplet_> SofterThanMax(std::vector<Multiplet_> const& multiplet) const {
        return RemoveIfHard(multiplet, max_);
    }

    template <typename Multiplet_>
    std::vector<Multiplet_> HarderThanMin(std::vector<Multiplet_> const& multiplet) const {
        return RemoveIfSoft(multiplet, min_);
    }

    template <typename Multiplet_>
    std::vector<Multiplet_> InsidePtWindow(std::vector<Multiplet_> const& multiplet) const {
        return RemoveIfHard(RemoveIfSoft(multiplet, min_), max_);
    }

private:

    Momentum PtMin(Id id);
    Momentum PtMax(Id id);
    Momentum PtMin(SubJet const& id);
    Momentum PtMax(SubJet const& id);
    Momentum PtMin(boca::Id id, const boca::Angle& cone_size);
    Momentum PtMax(boca::Id id, const boca::Angle& cone_size);
    Momentum Pt(boca::Id id, const boca::Angle& cone_size);
    Momentum min_ = AtRest();
    Momentum max_ = AtRest();

};

}
