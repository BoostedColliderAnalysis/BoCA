/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Particle.hh"

namespace boca
{

namespace branch
{

class TwoBody : public Particle
{

public:

    TwoBody();

    float ht;
    float delta_pt;
    float delta_m;
    float delta_rap;
    float delta_phi;
    float delta_r;
    float rho;
    float bdt_1;
    float bdt_2;
    float pull_1;
    float pull_2;
    float dipolarity;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Particle::Fill(multiplet);
        ht = multiplet.Ht() / GeV;
        delta_pt = multiplet.DeltaPt() / GeV;
        delta_m = multiplet.DeltaM() / GeV;
        delta_rap = multiplet.DeltaRap() / rad;
        delta_phi = multiplet.DeltaPhi() / rad;
        delta_r = multiplet.DeltaR() / rad;
        rho = multiplet.Rho();
        bdt_1 = multiplet.Multiplet1().Bdt();
        bdt_2 = multiplet.Multiplet2().Bdt();
        pull_1 = multiplet.Pull12() / rad;
        pull_2 = multiplet.Pull21() / rad;
        dipolarity = multiplet.Dipolarity();
    }

    Observables Variables();

    Observables Spectators();

private:

    ClassDef(TwoBody, 1)

};

}

}
