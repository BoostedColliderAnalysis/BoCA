/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Triplet.hh"

namespace boca
{

/**
 * @ingroup Multiplets
 * @brief A %Sextet consisting of two Triplet%s
 *
 */
class Sextet : public TwoBody<Triplet, Triplet>
{

public:

    using TwoBody<Triplet, Triplet>::TwoBody;

    Triplet const& Triplet1() const;

    Triplet const& Triplet2() const;

    Triplet & Triplet1();

    Triplet & Triplet2();

};

}
