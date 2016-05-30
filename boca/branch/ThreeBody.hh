/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Particle.hh"

namespace boca
{

namespace branch
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class ThreeBody : public Particle
{

public:

    ThreeBody();

    float ht;
    float bdt_1;
    float bdt_2;
    float bdt_3;
    float mass_12;
    float mass_23;
    float mass_13;
    float pt_12;
    float pt_23;
    float pt_13;
    float delta_pt_12;
    float delta_pt_23;
    float delta_pt_13;
    float ht_12;
    float ht_23;
    float ht_13;
    float rho_12;
    float rho_23;
    float rho_13;
    float delta_rap_12;
    float delta_rap_23;
    float delta_rap_13;
    float delta_phi_12;
    float delta_phi_23;
    float delta_phi_13;
    float delta_r_12;
    float delta_r_23;
    float delta_r_13;
    float delta_m_12;
    float delta_m_23;
    float delta_m_13;
    float delta_ht_12;
    float delta_ht_23;
    float delta_ht_13;
    float pull_12;
    float pull_21;
    float pull_23;
    float pull_13;
    float pull_32;
    float pull_31;
    float dipolarity_23;
    float dipolarity_13;
    float sphericity;
    float aplanarity;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Particle::Fill(multiplet);
        ht = multiplet.Ht() / GeV;
        bdt_1 = multiplet.Multiplet1().Bdt();
        bdt_2 = multiplet.Multiplet2().Bdt();
        bdt_3 = multiplet.Multiplet3().Bdt();
        mass_12 = multiplet.Multiplet12().Mass() / GeV;
        mass_23 = multiplet.Multiplet23().Mass() / GeV;
        mass_13 = multiplet.Multiplet13().Mass() / GeV;
        pt_12 = multiplet.Multiplet12().Pt() / GeV;
        pt_23 = multiplet.Multiplet23().Pt() / GeV;
        pt_13 = multiplet.Multiplet13().Pt() / GeV;
        delta_pt_12 = multiplet.Multiplet12().DeltaPt() / GeV;
        delta_pt_23 = multiplet.Multiplet23().DeltaPt() / GeV;
        delta_pt_13 = multiplet.Multiplet13().DeltaPt() / GeV;
        ht_12 = multiplet.Multiplet12().Ht() / GeV;
        ht_23 = multiplet.Multiplet23().Ht() / GeV;
        ht_13 = multiplet.Multiplet13().Ht() / GeV;
        rho_12 = multiplet.Multiplet12().Rho();
        rho_23 = multiplet.Multiplet23().Rho();
        rho_13 = multiplet.Multiplet13().Rho();
        delta_rap_12 = multiplet.Multiplet12().DeltaRap() / rad;
        delta_rap_23 = multiplet.Multiplet23().DeltaRap() / rad;
        delta_rap_13 = multiplet.Multiplet13().DeltaRap() / rad;
        delta_phi_12 = multiplet.Multiplet12().DeltaPhi() / rad;
        delta_phi_23 = multiplet.Multiplet23().DeltaPhi() / rad;
        delta_phi_13 = multiplet.Multiplet13().DeltaPhi() / rad;
        delta_r_12 = multiplet.Multiplet12().DeltaR() / rad;
        delta_r_23 = multiplet.Multiplet23().DeltaR() / rad;
        delta_r_13 = multiplet.Multiplet13().DeltaR() / rad;
        delta_m_12 = multiplet.Multiplet12().DeltaM() / GeV;
        delta_m_23 = multiplet.Multiplet23().DeltaM() / GeV;
        delta_m_13 = multiplet.Multiplet13().DeltaM() / GeV;
        delta_ht_12 = multiplet.Multiplet12().DeltaHt() / GeV;
        delta_ht_23 = multiplet.Multiplet23().DeltaHt() / GeV;
        delta_ht_13 = multiplet.Multiplet13().DeltaHt() / GeV;
        pull_12 = multiplet.Multiplet12().Pull12() / rad;
        pull_21 = multiplet.Multiplet12().Pull21() / rad;
        pull_23 = multiplet.Multiplet23().Pull12() / rad;
        pull_32 = multiplet.Multiplet23().Pull21() / rad;
        pull_13 = multiplet.Multiplet13().Pull12() / rad;
        pull_31 = multiplet.Multiplet13().Pull21() / rad;
        dipolarity_23 = multiplet.Multiplet23().Dipolarity();
        dipolarity_13 = multiplet.Multiplet13().Dipolarity();
        aplanarity = multiplet.EventShapes().Aplanarity();
        sphericity = multiplet.EventShapes().Sphericity();
    }

    Observables Variables();
    
    Observables Spectators();

private:

    ClassDef(ThreeBody, 1)

};

}

}
