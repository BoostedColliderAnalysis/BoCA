/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/TwoBody.hh"
#include "standardmodel/branch/BottomBase.hh"

namespace standardmodel
{

namespace branch {

/**
 *
 * @brief Top leptonic tagger tree branch
 *
 */
class TopLeptonic : public boca::branch::TwoBody, public BottomBase
{
public:
    TopLeptonic();
    float BottomPt;
    float LeptonPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        BottomBase::Fill(multiplet);
        BottomPt = multiplet.Singlet().Pt() / GeV;
        LeptonPt = multiplet.Doublet().Pt() / GeV; // FIXME what is with the case of W
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(TopLeptonic, 1)
};

}

}
