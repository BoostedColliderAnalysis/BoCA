/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/TwoBody.hh"
#include "standardmodel/branch/BottomBase.hh"

namespace standardmodel
{

namespace branch
{

/**
 *
 * @brief W hadronic tagger tree branch
 *
 */
class WHadronic : public boca::branch::TwoBody, public BottomBase
{

public:

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        BottomBase::Fill(multiplet);
    }

    Observables Variables();

    Observables Spectators();

private:

    ClassDef(WHadronic, 1)

};
}

}
