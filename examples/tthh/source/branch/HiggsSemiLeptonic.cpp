/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "tthh/branch/HiggsSemiLeptonic.hh"
#include "boca/OBSERVABLE_MACROS.hh"
#include "boca/latex/String.hh"

namespace tthh
{

namespace branch
{

HiggsSemiLeptonic::HiggsSemiLeptonic()
{}

boca::Observables HiggsSemiLeptonic::Variables()
{
    auto substructure = boca::Settings::SubStructure() ?
                        OBSERVABLE(pull_1, boca::latex::String("#theta_{1}")) +
                        OBSERVABLE(pull_2, boca::latex::String("#theta_{2}"))
                        /*+ OBSERVABLE(dipolarity, latex::String("D"))*/
                        : boca::Observables {};
    auto var = Particle::Variables() +
               OBSERVABLE(ht, boca::latex::String("H_{T}") + " [GeV]") +
               OBSERVABLE(delta_pt, boca::latex::String("\\delta_ P_{T}") + " [GeV]") +
               OBSERVABLE(delta_m, boca::latex::String("\\delta_ m") + " [GeV]") +
               OBSERVABLE(delta_rap, boca::latex::String("\\delta_ \\eta")) +
               OBSERVABLE(delta_phi, boca::latex::String("\\delta_ \\phi")) +
               OBSERVABLE(delta_r, boca::latex::String("\\delta_ R")) +
               OBSERVABLE(rho, boca::latex::String("\\rho")) +
               OBSERVABLE(bdt_1, "BDT_{1}") +
//            OBSERVABLE(bdt_2, "BDT_{2}") +
               substructure;
    return var + BottomBase::Variables();
}

boca::Observables HiggsSemiLeptonic::Spectators()
{
    return TwoBody::Spectators() + BottomBase::Spectators();
}

}

}
