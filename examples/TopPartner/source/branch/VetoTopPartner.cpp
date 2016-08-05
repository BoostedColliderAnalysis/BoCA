/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/VetoTopPartner.hh"

namespace toppartner
{

namespace branch
{

boca::Observables VetoTopPartnerBranch::Variables()
{
    return Multi::Variables() + EventShapesBase::Variables();
}

boca::Observables VetoTopPartnerBranch::Spectators()
{
    return Multi::Spectators() + EventShapesBase::Spectators();
}

}

}
