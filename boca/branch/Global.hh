/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Bdt.hh"
#include "boca/branch/GlobalBase.hh"

namespace boca
{

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class Global : public Bdt, public GlobalBase
{

public:

    Global();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet);
    }

    Observables Variables();

    Observables Spectators();

private:

    ClassDef(Global, 1)

};

}

}
