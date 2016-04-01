/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <map>
#include "physics/Member.hh"

namespace boca
{

enum class Relative
{
    none,
    particle,
    mother,
    step_mother,
    grand_mother,
    great_grand_mother
};

std::string Name(Relative relative);

Relative Mother(Relative relative);

Relative StepMother(Relative relative);


class Family
{

public:

    Family();

    Family(boca::Member const& member, Relative relative);

    void SetMember(boca::Member const& member, Relative relative);

    boca::Member Member(Relative relative) const;

private:

    bool Has(Relative relative) const;

    std::map<Relative, boca::Member> members_;

};

}
