/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Multi.hh"
#include "standardmodel/branch/BottomBase.hh"
#include "standardmodel/branch/LeptonVeto.hh"

namespace standardmodel
{

namespace branch {

/**
 *
 * @brief Top hadronic tagger tree branch
 *
 */
class TopHadronic : public boca::branch::Multi, public BottomBase, public LeptonVeto
{
public:

    TopHadronic();

    float bottom_mass;
    float w_mass;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        BottomBase::Fill(multiplet);
        LeptonVeto::Fill(multiplet);
        bottom_mass = multiplet.Singlet().Mass() / GeV;
        w_mass = multiplet.Doublet().Mass() / GeV;
    }

    Observables Variables();

    Observables Spectators();

private:

    ClassDef(TopHadronic, 1)

};

}

}
