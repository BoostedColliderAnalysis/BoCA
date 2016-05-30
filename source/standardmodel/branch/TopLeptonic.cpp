/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/TopLeptonic.hh"
#include "boca/branch/Base.hh"
#include "boca/OBSERVABLE.hh"

namespace boca
{

namespace standardmodel
{

namespace branch {

TopLeptonic::TopLeptonic()
{
    BottomPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables TopLeptonic::Variables()
{
    return BottomBase::Variables() + Particle::Variables() + OBSERVABLE(ht) + OBSERVABLE(delta_pt) + OBSERVABLE(delta_m) + OBSERVABLE(delta_rap) + OBSERVABLE(delta_phi) + OBSERVABLE(delta_r) + OBSERVABLE(rho) + OBSERVABLE(bdt_2) + OBSERVABLE(BottomPt) + OBSERVABLE(LeptonPt) + OBSERVABLE(pull_1, latex::String("#theta_{1}")) + OBSERVABLE(pull_2, latex::String("#theta")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/ + OBSERVABLE(bdt_1);
}

Observables TopLeptonic::Spectators()
{
    return TwoBody::Spectators() + BottomBase::Spectators();
}

}

}

}
