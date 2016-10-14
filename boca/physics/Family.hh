/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/optional.hpp>
#include "boca/physics/Member.hh"
#include "boca/physics/Id.hh"

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

std::vector<Relative> Relatives();

class Family
{

public:

    Family();

    Family(boca::Member const &member, Relative relative);

    void SetMember(boca::Member const &member, Relative relative);

    boca::Member Member(Relative relative) const;

    boost::optional<boca::Member> Member(Id id) const;

private:

//     bool Has(Relative relative) const;

    std::vector<std::pair<Relative, boca::Member>> members_;

};

}
