/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/physics/Prefixes.hh"
#include "boca/branch/Bdt.hh"

namespace boca
{

namespace branch
{

/**
 * @brief %Particle tree branch
 *
 */
class Particle : public Bdt
{

public:

    Particle();

    float mass;
    float pt;
    float rap;
    float phi;
    float charge;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        mass = multiplet.Mass() / GeV;
        pt = multiplet.Pt() / GeV;
        rap = multiplet.Rap() / rad;
        phi = multiplet.Phi() / rad;
        charge = multiplet.Charge();
    }

    Observables Variables();

    Observables Spectators();

private:

    ClassDef(Particle, 1)

};

}

}
