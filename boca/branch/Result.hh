/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Base.hh"
#include "boca/Observables.hh"

namespace boca
{

namespace branch
{

class Result : public Base
{
public:
  
    Result();

    float tag;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        tag = static_cast<int>(multiplet.Tag());
    }

    virtual Observables Variables();

    virtual Observables Spectators();

private:

    ClassDef(Result, 1)

};

}

}
