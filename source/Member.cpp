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
// Member::Member(Id id)
// {
//     id_ = to_int(id);
// }
//
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
LorentzVector Member::momentum() const
{
    return momentum_;
}

int Member::position() const
{
    return position_;
}

int Member::id() const
{
    return id_;
}

}
