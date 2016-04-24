/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/physics/Family.hh"
#include "boca/generic/DEBUG.hh"
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

Family::Family()
{}

Family::Family(boca::Member const& member, Relative relative)
{
    SetMember(member, relative);
}

void Family::SetMember(boca::Member const& member, Relative relative)
{
    CHECK(!Has(relative), "Family member overwritten");
    members_.emplace(relative, member);
}

boca::Member Family::Member(Relative relative) const
{
    return Has(relative) ? members_.at(relative) : boca::Member();
}

bool Family::Has(Relative relative) const
{
    return members_.find(relative) != members_.end();
}

}
