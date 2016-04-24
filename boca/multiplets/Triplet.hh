/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Doublet.hh"

namespace boca
{

class Triplet : public TwoBody<boca::Doublet, boca::Singlet>
{

public:

    using TwoBody<boca::Doublet, boca::Singlet>::TwoBody;

    boca::Doublet const& Doublet() const;

    boca::Doublet& Doublet();

    boca::Singlet const& Singlet() const;

private:

};

}
