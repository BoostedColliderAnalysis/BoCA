/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/TwoBody.hh"

namespace boca
{

namespace branch
{

class Multi : public TwoBody
{

public:

    Multi();

    float delta_ht;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        delta_ht = multiplet.DeltaHt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(Multi, 1)

};

}

}
