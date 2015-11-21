/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Member.hh"
#include "Types.hh"

namespace boca
{

Member::Member(int id)
{
    id_ = id;
}

Member::Member(int id, int position)
{
    id_ = id;
    position_ = position;
}
Member::Member(LorentzVector const& momentum, int id, int position)
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
LorentzVector Member::Momentum() const
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

void Member::Set(int id, int position)
{
    id_ = id;
    position_ = position;
}

}
