/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/TwoBody.hh"
#include "boca/standardmodel/branch/BottomBase.hh"
#include "boca/standardmodel/branch/LeptonVeto.hh"

namespace boca
{

namespace standardmodel
{

namespace branch
{

/**
 *
 * @brief %Higgs tagger tree branch
 *
 */
class Higgs : public boca::branch::TwoBody, public BottomBase, public LeptonVeto
{

public:

    Higgs();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        BottomBase::Fill(multiplet);
        LeptonVeto::Fill(multiplet);
    }

    Observables Variables();

    Observables Spectators();

private:

    ClassDef(Higgs, 1)

};

}

}

}
