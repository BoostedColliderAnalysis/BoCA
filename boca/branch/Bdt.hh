/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Result.hh"

namespace boca
{

namespace branch
{

class Bdt : public Result
{

public:
  
    Bdt();

    float bdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Result::Fill(multiplet);
        bdt = multiplet.Bdt();
    }

    virtual Observables Variables();

    virtual Observables Spectators();

private:

    ClassDef(Bdt, 1)

};

}

}
