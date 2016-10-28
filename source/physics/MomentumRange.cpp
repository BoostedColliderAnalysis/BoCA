/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "boca/math/Math.hh"

#include "boca/physics/MomentumRange.hh"
#include "boca/Settings.hh"

namespace boca
{

namespace
{

double Smearing()
{
    return 0.3;
}

double SmearingMin()
{
    return 1. - Smearing();
}

double SmearingMax()
{
    return 1. + Smearing();
}

}

SubJet::SubJet(boca::Id id)
{
    id_ = id;
}

Id SubJet::Id() const
{
    return id_;
}

MomentumRange::MomentumRange(Id max)
{
    Set(at_rest, PtMax(max));
}

MomentumRange::MomentumRange(Id min, Id max)
{
    Set(PtMin(min), PtMax(max));
}

MomentumRange::MomentumRange(Id min, SubJet const& max)
{
    Set(PtMin(min), PtMax(max));
}

MomentumRange::MomentumRange(SubJet const& min, SubJet const& max)
{
    Set(PtMin(min), PtMax(max));
}

MomentumRange::MomentumRange(SubJet const& min)
{
    Set(PtMin(min), std::numeric_limits<double>::max() * GeV);
}

void MomentumRange::Set(Momentum const& min, Momentum const& max)
{
    min_ = min;
    max_ = max;
}

Momentum MomentumRange::Min() const
{
    return min_;
}

Momentum MomentumRange::Max() const
{
    return max_;
}

Momentum MomentumRange::PtMin(Id id)
{
    return PtMin(id, Settings::JetConeSize());
}

Momentum MomentumRange::PtMax(Id id)
{
    return PtMax(id, Settings::JetConeSize());
}

Momentum MomentumRange::PtMin(SubJet const& id)
{
    return PtMin(id.Id(), Settings::MinCellResolution());
}

Momentum MomentumRange::PtMax(SubJet const& id)
{
    return PtMax(id.Id(), Settings::MinCellResolution());
}

Momentum MomentumRange::Pt(Id id, Angle const& cone_size)
{
    return MassOf(id) * (2_rad / cone_size);
}

Momentum MomentumRange::PtMin(Id id, Angle const& cone_size)
{
    return Pt(id, cone_size) * SmearingMin();
}

Momentum MomentumRange::PtMax(Id id, Angle const& cone_size)
{
    return Pt(id, cone_size) * SmearingMax();
}

}
