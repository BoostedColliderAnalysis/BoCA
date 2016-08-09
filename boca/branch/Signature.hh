/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/EventShapesBase.hh"
#include "boca/branch/ThreeBody.hh"

namespace boca
{

namespace branch {

class Signature : public ThreeBody, public EventShapesBase
{

public:

    Signature();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
        EventShapesBase::Fill(multiplet);
    }

    Observables Variables();

    Observables Spectators();

private:

    ClassDef(Signature, 1)

};

}

}
