/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Result.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace boca
{

namespace branch
{

Result::Result()
{
    tag = static_cast<int>(InitialValue());
}

Observables Result::Variables()
{
    return {};
}

Observables Result::Spectators()
{
    return OBSERVABLE(tag);
}

}

}
