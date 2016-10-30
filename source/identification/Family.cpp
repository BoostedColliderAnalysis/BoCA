/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/algorithm/find_if.hpp>

#include "boca/identification/Family.hh"
#include "boca/generic/DEBUG_MACROS.hh"
#include "boca/generic/Types.hh"

namespace boca
{

std::string Name(Relative relative)
{
    switch (relative) {
    case Relative::none : return "None";
    case Relative::particle : return "Particle";
    case Relative::mother : return "Mother";
    case Relative::step_mother : return "StepMother";
    case Relative::grand_mother : return "GrandMother";
    case Relative::great_grand_mother : return "GreatGrandMother";
        DEFAULT(to_int(relative), "");
    }
}

Relative Mother(Relative relative)
{
    switch (relative) {
    case Relative::particle : return Relative::mother;
    case Relative::mother : return Relative::grand_mother;
    case Relative::grand_mother : return Relative::great_grand_mother;
    default : return Relative::none;
    }
}

Relative StepMother(Relative relative)
{
    return relative == Relative::particle ? Relative::step_mother : Relative::none;
}

std::vector< boca::Relative, std::allocator< boca::Relative > > Relatives()
{
    return {Relative::particle, Relative::mother, Relative::step_mother, Relative::grand_mother, Relative::great_grand_mother};
}


Family::Family()
{}

Family::Family(boca::Member const& member, Relative relative)
{
    SetMember(member, relative);
}

void Family::SetMember(boca::Member const& member, Relative relative)
{
//     CHECK(!Has(relative), "Family member overwritten");
    members_.emplace_back(std::make_pair(relative, member));
}

boca::Member Family::Member(Relative relative) const
{
    auto mem = boost::range::find_if(members_, [&](std::pair<Relative, boca::Member> const& pair) {
        return pair.first == relative;
    });
    if (mem == members_.end()) return {};
    else return (*mem).second;
//     return Has(relative) ? members_.at(relative) : boca::Member();
}

boost::optional<boca::Member> Family::Member(Id id) const
{
    for (auto const member :  members_) if (std::abs(member.second.Id()) == to_int(id)) return member.second;
    return boost::none;
}

// bool Family::Has(Relative relative) const
// {
//     return members_.find(relative) != members_.end();
// }

}
