/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "toppartner/branch/SignatureEffective.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"

namespace toppartner
{

namespace branch
{

SignatureEffectiveBranch::SignatureEffectiveBranch()
{
}

boca::Observables SignatureEffectiveBranch::Variables()
{
    return ThreeBody::Variables() + EventShapesBase::Variables();
}

boca::Observables SignatureEffectiveBranch::Spectators()
{
    return ThreeBody::Spectators() + EventShapesBase::Spectators();
}

}

}
