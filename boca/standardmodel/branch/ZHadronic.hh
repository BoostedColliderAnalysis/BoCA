/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/TwoBody.hh"
#include "boca/standardmodel/branch/BottomBase.hh"

namespace boca
{

namespace standardmodel
{

namespace branch{

/**
 *
 * @brief Z hadronic tagger tree branch
 *
 */
class ZHadronic : public boca::branch::TwoBody, public BottomBase
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

    ClassDef(ZHadronic, 1)

};

}

}

}
