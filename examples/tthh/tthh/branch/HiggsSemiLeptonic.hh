/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/TwoBody.hh"
#include "standardmodel/branch/BottomBase.hh"

namespace tthh
{

namespace branch
{

/**
 *
 * @brief %Higgs tagger tree branch
 *
 */
class HiggsSemiLeptonic : public boca::branch::TwoBody, public standardmodel::branch::BottomBase
{

public:

    HiggsSemiLeptonic();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        BottomBase::Fill(multiplet);
    }

    boca::Observables Variables();

    boca::Observables Spectators();

private:

    ClassDef(HiggsSemiLeptonic, 1)

};

}

}
