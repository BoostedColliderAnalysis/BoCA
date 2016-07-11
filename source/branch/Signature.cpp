/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Signature.hh"

namespace boca
{

namespace branch
{

Signature::Signature()
{
}

Observables Signature::Variables()
{
    return ThreeBody::Variables() + EventShapesBase::Variables();
}

Observables Signature::Spectators()
{
    return ThreeBody::Spectators() + EventShapesBase::Spectators();
}

}

}
