/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "MomentumRange.hh"

#include "DetectorGeometry.hh"
#include "Math.hh"
#include "Vector.hh"

namespace boca
{
SubJet::SubJet(boca::Id id)
{
    id_ = id;
}
Id SubJet::Id() const
{
    return id_;
}
MomentumRange::MomentumRange(){}
MomentumRange::MomentumRange(Momentum min, Momentum max)
{
    Set(min, max);
}
MomentumRange::MomentumRange(Id max)
{
    Set(at_rest, PtMax(max));
}
MomentumRange::MomentumRange(Id min, Id max)
{
    Set(PtMin(min), PtMax(max));
}
MomentumRange::MomentumRange(Id min, const SubJet& max)
{
    Set(PtMin(min), PtMax(max));
}
MomentumRange::MomentumRange(const SubJet& min, const SubJet& max)
{
    Set(PtMin(min), PtMax(max));
}
MomentumRange::MomentumRange(const SubJet& min)
{
    Set(PtMin(min), double(LargeNumber()) * GeV);
}
void MomentumRange::Set(Momentum min, Momentum max)
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
    return PtMin(id, DetectorGeometry::JetConeSize());
}
Momentum MomentumRange::PtMax(Id id)
{
    return PtMax(id, DetectorGeometry::JetConeSize());
}
Momentum MomentumRange::PtMin(const SubJet& id)
{
    return PtMin(id.Id(), DetectorGeometry::MinCellResolution());
}
Momentum MomentumRange::PtMax(const SubJet& id)
{
    return PtMax(id.Id(), DetectorGeometry::MinCellResolution());
}
bool MomentumRange::UpperBound(const fastjet::PseudoJet& jet) const
{
    return jet.pt() * GeV < max_;
}
bool MomentumRange::LowerBound(const fastjet::PseudoJet& jet) const
{
    return jet.pt() * GeV > min_;
}
bool MomentumRange::Bounds(const fastjet::PseudoJet& jet) const
{
    return LowerBound(jet) && UpperBound(jet);
}
Momentum MomentumRange::Pt(Id id, float cone_size)
{
    return MassOf(id) * (2. / cone_size);
}
Momentum MomentumRange::PtMin(Id id, float cone_size)
{
    return 0.8 * Pt(id, cone_size);
}
Momentum MomentumRange::PtMax(Id id, float cone_size)
{
    return 1.2 * Pt(id, cone_size);
}
Jets MomentumRange::Soft(const Jets& jets) const
{
    return RemoveIfHard(jets, max_);
}
Jets MomentumRange::Hard(const Jets& jets) const
{
    return RemoveIfSoft(jets, min_);
}
}
