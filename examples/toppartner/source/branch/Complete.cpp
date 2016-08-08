/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/Complete.hh"

namespace toppartner
{

namespace branch
{

Complete::Complete()
{
}

boca::Observables Complete::Variables()
{
    return SignatureSingleHadronicBranch::Variables() + GlobalBase::Variables();
}

boca::Observables Complete::Spectators()
{
    return SignatureSingleHadronicBranch::Spectators() + GlobalBase::Spectators();
}

}

}
