/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/generic/Types.hh"
#include "boca/identification/Member.hh"
#include "boca/identification/Id.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Member::Member()
{
    id_ = static_cast<int>(boca::Id::none);
}

Member::Member(int id)
{
    id_ = id;
}

Member::Member(int id, int position)
{
    id_ = id;
    position_ = position;
}
Member::Member(LorentzVector<boca::Momentum> const& momentum, int id, int position)
{
    id_ = id;
    position_ = position;
    momentum_ = momentum;
}
Member::Member(TLorentzVector const& momentum, int id, int position)
{
    id_ = id;
    position_ = position;
    momentum_ = momentum;
}
LorentzVector< Momentum > Member::Momentum() const
{
    return momentum_;
}

int Member::Position() const
{
    return position_;
}

int Member::Id() const
{
    return id_;
}

std::string Member::Name() const
{
    return boca::Name(Id());
}

void Member::Set(int id, int position)
{
    id_ = id;
    position_ = position;
}

int Member::EmptyPosition()
{
    return -1;
}

bool Member::operator==(Member const& member) const
{
    CHECK(Position() != EmptyPosition(), Position());
    return Position() == member.Position();
}

}
