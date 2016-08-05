/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/branch/Complete.hh"

namespace toppartner
{

namespace branch
{

CompleteBranch::CompleteBranch()
{
}

boca::Observables CompleteBranch::Variables()
{
    return SignatureSingleHadronicBranch::Variables() + GlobalBase::Variables();
}

boca::Observables CompleteBranch::Spectators()
{
    return SignatureSingleHadronicBranch::Spectators() + GlobalBase::Spectators();
}

}

}
