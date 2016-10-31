/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/optional.hpp>

#include "boca/identification/Id.hh"
#include "boca/identification/Member.hh"

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

/**
 * @brief Stream the name of a family relative
 *
 */
std::ostream& operator<<(std::ostream & stream, Relative relative);

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

    friend std::ostream& operator<<(std::ostream& stream, Family const& family);

private:

struct Pair{
    Relative relative;
    boca::Member member;
};

    std::vector<Pair> members_;

};

}
